#ifndef SMARTGATEWAY_H
#define SMARTGATEWAY_H

#include <QWidget>
#include<QLabel>
#include<QDateTime>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include<QJsonArray>
#include<QProcess>
#include <QThread>
#include "slidepage/slidepage.h"
#include "app/app.h"
#include "app2/app2.h"
#include "album/album.h"
#include "weather/weatherinfo.h"
#include "messageBoard/messageboard.h"

#define QUERY_IP_URL "http://ip.ws.126.net/ipquery"
#define QUERY_WEATHER_URL "http://wthrcdn.etouch.cn/weather_mini?city="

class SmartGateway : public QWidget
{
    Q_OBJECT


public:
    SmartGateway(QWidget *parent = 0);
    ~SmartGateway();
    QNetworkAccessManager *netWorkManager;
    QTextCodec *textCodec;
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonParseError jsonError;
    void layoutInit();
    /************************时钟界面************************************/
    /*   时钟定时器   */
    QTimer *clock_timer;

    /* 保存当前时间  */
    QDateTime currentDateTime;

    /*   显示时间标签   */
    QLabel *time_QLabel;

    /*   显示日期标签   */
    QLabel *date_QLabel;

    /*   显示上下午标签   */
    QLabel *ampm_QLabel;

    /*   显示时间日期分隔线标签   */
    QLabel *line_QLabel;

    /************************天气界面************************************/
    bool eventFilter(QObject *obj, QEvent *e);
    QLabel *weather_cityName_QLabel;

    QLabel *weather_temperature_QLabel;

    QLabel *weather_image_QLabel;

    QLabel *weather_imageName_QLabel;

    void getCityName();

    /***********************留言板界面**************************************/
    QLabel * messageBoard_Title;
    QLabel *messageBoard_content;
    QThread *subThread;
    MessageBoard *messageBoard;
    /************************滑动app界面******************************************/
    /*滑动主窗口*/
    QWidget *appWidget;

    /* 滑动背景　*/
    QWidget *bgWidget;

    SlidePage *mySlidePage;

    /* 重设大小 */
    void resizeEvent(QResizeEvent *event);

    /*  application pages  */
    App *appPageOne;
    App2 *appPageTwo;
public slots:

};

#endif // SMARTGATEWAY_H
