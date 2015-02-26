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

#ifndef DESKTOPSCROBBLER
#define DESKTOPSCROBBLER

#include <QQuickItem>
#include <QFileSystemWatcher>
#include <QDir>
#include "../qquicklist/qquicklist.h"
#include "desktopfile.h"

class DesktopScrobbler : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(QObjectListModel* desktopFiles READ desktopFiles NOTIFY desktopFilesChanged)

public:
    DesktopScrobbler(QQuickItem *parent = 0);
    QObjectListModel* desktopFiles(){
        return desktopList.getModel();
    }
    Q_INVOKABLE int getIndexByName(QString name); //localized also works
    static bool cmp(const DesktopFile *a, const DesktopFile *b);

private:
    QFileSystemWatcher *fileWatcher;
    QFileSystemWatcher *dirWatcher;
    QQuickList<DesktopFile> desktopList;
private slots:
    void processFileModification(const QString &path);
    void processDirChange(const QString &path);

signals:
    void desktopFilesChanged(QObjectListModel*);
};

#endif // DESKTOPSCROBBLER
