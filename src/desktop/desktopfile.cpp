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

void DesktopFile::processLocation(const QString &location) {
    QSettings desktopFile(location, QSettings::IniFormat);
    m_name = desktopFile.value("Desktop Entry/Name").toString();
    m_exec = desktopFile.value("Desktop Entry/Exec").toString();
    QString tempIcon = desktopFile.value("Desktop Entry/Icon").toString();
    m_darkColor = desktopFile.value("Desktop Entry/X-Papyros-DarkColor");
    QStringList envList = QVariant(qgetenv("XDG_DATA_DIRS")).toString().split(":");
    bool absoluteRet = QFile::exists(tempIcon);
    if (!absoluteRet) {
        //we're only looking in hicolor and highcontrast, *for now*, other themes will not be that hard too add later on
        for (int i = 0; i < envList.length(); i++){
            QString scalable = envList[i] + "/icons/hicolor/scalable/apps/" + tempIcon;
            QString highContrastScalable = envList[i] + "/icons/HighContrast/scalable/apps/" + tempIcon;
            QString highContrastScalableExtra = envList[i] + "/icons/HighContrast/scalable/apps-extra/" + tempIcon;
            m_icon = QFile::exists(scalable) ? scalable : (QFile::exists(scalable + ".svg") ? scalable + ".svg" : (QFile::exists(scalable + ".svgz") ? scalable + ".svgz" : ""));
            m_icon = m_icon == "" ? (QFile::exists(highContrastScalable) ? highContrastScalable : (QFile::exists(highContrastScalable + ".svg") ? highContrastScalable + ".svg" : (QFile::exists(highContrastScalable + ".svgz") ? highContrastScalable + ".svgz" : ""))) : m_icon;
            m_icon = m_icon == "" ? (QFile::exists(highContrastScalableExtra) ? highContrastScalableExtra : (QFile::exists(highContrastScalableExtra + ".svg") ? highContrastScalableExtra + ".svg" : (QFile::exists(highContrastScalableExtra + ".svgz") ? highContrastScalableExtra + ".svgz" : ""))) : m_icon;
            if (m_icon != ""){
                break;
            } else {
                QStringList sizesList;
                sizesList << "512x512" << "256x256" << "128x128";
                for (int j = 0; j < sizesList.length(); j++) {
                    QString noscalable = envList[i] + "/icons/hicolor/" + sizesList[j] + "/apps/" + tempIcon;
                    if (QFile::exists(noscalable)) {
                        m_icon = noscalable;
                        break;
                    } else if (QFile::exists(noscalable + ".png")) {
                        m_icon = noscalable + ".png";
                        break;
                    }
                }
                if (m_icon != "") {
                    break;
                } else {
                    QString highContrast = envList[i] + "/icons/HighContrast/256x256/apps/" + tempIcon;
                    m_icon = QFile::exists(highContrast) ? highContrast : (QFile::exists(highContrast + ".png") ? highContrast + ".png" : "");
                    if (m_icon != "") {
                        break;
                    } else {
                        QString pixmap = envList[i] + "/pixmaps/" + tempIcon;
                        m_icon = QFile::exists(pixmap) ? pixmap : (QFile::exists(pixmap + ".png") ? pixmap + ".png" : (QFile::exists(pixmap + ".xpm") ? pixmap + ".xpm" : ""));
                        if (m_icon != "") {
                            break;
                        }
                    }
                }
            }
        }
    }
    else {
        m_icon = tempIcon;
    }
}
