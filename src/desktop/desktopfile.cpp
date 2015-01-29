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
    m_exec = desktopFile.value("Desktop Entry/Icon").toString();
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
                for (int i = 0; i < sizesList.length(); i++) {
                    QString noscalable = envList[i] + "/icons/hicolor/" + sizesList[i] + "/apps/" + tempIcon;
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
