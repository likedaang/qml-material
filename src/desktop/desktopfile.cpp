/*
 * QML Desktop - Set of tools written in C++ for QML
 *
 * Copyright (C) 2014 Bogdan Cuza <bogdan.cuza@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "desktopfile.h"

DesktopFile::DesktopFile(QString location, QObject *parent) : QObject(parent) {
    if (location == "" && m_location != "") {
        processLocation(m_location);
    } else if (location != "") {
        m_location = location;
        emit locationChanged();
        processLocation(location);
    }
}

QString DesktopFile::locationFromFile(QString desktopName){
    bool globalRet = QFile::exists("/usr/share/applications/" + desktopName);
    bool anotherGlobalRet = QFile::exists("/usr/local/share/applications/" + desktopName);
    bool localRet = QFile::exists("~/.local/share/applications/" + desktopName);
    if (!globalRet && !anotherGlobalRet && !localRet)
        return "";
    return globalRet ? "/usr/share/applications/" + desktopName : (anotherGlobalRet ? "/usr/local/share/applications/" + desktopName : "~/.local/share/applications/" + desktopName);
}

QString DesktopFile::getEnvVar(int pid){
    QFile envFile(QString("/proc/%1/environ").arg(pid));
    if(!envFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";
    QTextStream in(&envFile);
    QString content = in.readAll();
    QRegExp rx("DESKTOP_FILE=(.+)");
    int pos = rx.indexIn(content);
    if (pos == -1)
        return "";
    return rx.cap(1);
}

void DesktopFile::setLocation(QString location){
    m_location = location;
    emit locationChanged();
    processLocation(m_location);
}

void DesktopFile::launch() {
    QString tempString = m_exec;
    tempString.replace("%f", "", Qt::CaseInsensitive);
    tempString.replace("%u", "", Qt::CaseInsensitive);
    QProcess::startDetached(tempString);
}

void DesktopFile::processLocation(const QString &location) {
    QSettings desktopFile(location, QSettings::IniFormat);
    desktopFile.setIniCodec("UTF-8");
    desktopFile.beginGroup("Desktop Entry");
    QLocale locale;
    QString fullLocale = locale.name();
    QString onlyLocale = fullLocale;
    onlyLocale.truncate(2);
    m_name = desktopFile.value("Name").toString();
    m_localizedName = desktopFile.value(QString("Name[%1]").arg(fullLocale)).isNull() ? desktopFile.value(QString("Name[%1]").arg(onlyLocale)) : desktopFile.value(QString("Name[%1]").arg(fullLocale));
    m_exec = desktopFile.value("Exec").toString();
    m_comment = desktopFile.value("Comment");
    m_localizedComment = desktopFile.value(QString("Comment[%1]").arg(fullLocale)).isNull() ? desktopFile.value(QString("Comment[%1]").arg(onlyLocale)) : desktopFile.value(QString("Comment[%1]").arg(fullLocale));
    QString tempIcon = desktopFile.value("Icon").toString();
    m_darkColor = desktopFile.value("X-Papyros-DarkColor");
    QStringList envList;
    if (qEnvironmentVariableIsEmpty("XDG_DATA_DIRS")) {
	   envList <<  "/usr/local/share/" << "/usr/share/";
    } else {
        envList = QVariant(qgetenv("XDG_DATA_DIRS")).toString().split(":");
    }
    bool absoluteRet = QFile::exists(tempIcon);
    if (!absoluteRet) {
        if (tempIcon.endsWith(".png", Qt::CaseInsensitive) ||
            tempIcon.endsWith(".svg", Qt::CaseInsensitive) ||
            tempIcon.endsWith(".xpm", Qt::CaseInsensitive))
        {
            tempIcon.truncate(tempIcon.length() - 4);
        }
        //we're only looking in hicolor and highcontrast, *for now*, other themes will not be that hard to add later on
        for (int i = 0; i < envList.length(); i++){
            QString iconTemplate = envList[i] + "icons/%1/%2/apps/%3";
            QString firstScalable = iconTemplate.arg("hicolor").arg("scalable").arg(tempIcon) + ".svg";
            QString secondScalable = iconTemplate.arg("HighContrast").arg("scalable").arg(tempIcon) + ".svg";
            m_icon = QFile::exists(firstScalable) ? firstScalable : (QFile::exists(firstScalable + "z") ? firstScalable + "z" : (QFile::exists(secondScalable) ? secondScalable : (QFile::exists(secondScalable + "z") ? secondScalable + "z" : "")));
            if (m_icon != "") {
                break;
            }
            QStringList sizesList;
            sizesList << "512x512" << "256x256" << "128x128";
            for (int j = 0; j < sizesList.length(); j++) {
               QString firstNotScalable = iconTemplate.arg("hicolor").arg(sizesList[j]).arg(tempIcon) + ".png";
               QString secondNotScalable = iconTemplate.arg("HighContrast").arg(sizesList[j]).arg(tempIcon) + ".png";
               m_icon = QFile::exists(firstNotScalable) ? firstNotScalable : (QFile::exists(secondNotScalable) ? secondScalable : "");
               if (m_icon != "") {
                    break;
               }
            }
            if (m_icon != "") {
                break;
            }
            QString pixmap = envList[i] + "pixmaps/" + tempIcon;
            m_icon = QFile::exists(pixmap + ".png") ? pixmap + ".png" : (QFile::exists(pixmap + ".xpm") ? pixmap + ".xpm" : "");
            if (m_icon != "") {
                break;
            }
        }
    }
    else {
        m_icon = tempIcon;
    }
}
