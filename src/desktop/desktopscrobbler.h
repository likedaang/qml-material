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

private:
    QFileSystemWatcher fileWatcher;
    QFileSystemWatcher *dirWatcher;
    QQuickList<DesktopFile> desktopList;
private slots:
    //I wonder if QQuickList handles this stuff automagically, needs testing
    void processFileModification(const QString &path);
    void processDirChange(const QString &path);

signals:
    void desktopFilesChanged(QObjectListModel*);
};

#endif // DESKTOPSCROBBLER
