#ifndef MUSIC_H
#define MUSIC_H
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QStringList>
#include <QUrl>
#include <QProcess>
#include "tools/filetools.h"
class Music : public QWidget
{
    Q_OBJECT
public:
    explicit Music(QWidget *parent = 0);
    void layoutInit();
    QWidget *mainWidget;
    QPushButton *playMusicPushButton;
    QPushButton *lastMusicPushButton;
    QPushButton *nextMusicPushButton;
    QPushButton *exitPushButton;
    QPushButton *volumePushButton;//音量按钮
    QListWidget *songListWidget;
    QStringList fileList;
    QProcess *myProcess;
    int musicCount;//音乐数量
    QString cmd;//播放器命令
    QListWidgetItem *currentMusic;//当前播放的音乐
signals:

public slots:
};

#endif // MUSIC_H
