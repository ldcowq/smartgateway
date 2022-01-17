#ifndef MUSIC_H
#define MUSIC_H
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QStringList>
#include <QUrl>
#include <QProcess>
#include <QLabel>
#include <QTimer>
#include "tools/filetools.h"
#include "video/customslider.h"
class Music : public QWidget
{
    Q_OBJECT
public:
    explicit Music(QWidget *parent = 0);
    ~Music();
    void layoutInit();
    void playMusic(QString file);
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
    bool playFlag = false;
    CustomSlider *processBarSlider;
    QTimer *processBarTimer;
    int current_pos = 0;
    QLabel *musicName;

signals:

public slots:
};

#endif // MUSIC_H
