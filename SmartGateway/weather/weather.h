#ifndef WEATHER_H
#define WEATHER_H

#include <QThread>
#include <QNetworkAccessManager>
#include <QTextCodec>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include<QJsonArray>
#define QUERY_IP_URL "http://ip.ws.126.net/ipquery"
#define QUERY_WEATHER_URL "http://wthrcdn.etouch.cn/weather_mini?city="

class Weather : public QThread
{
    Q_OBJECT

public:
    Weather();
    QNetworkAccessManager *netWorkManager;
    QTextCodec *textCodec;
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonParseError jsonError;
    QString cityName;
    QString imagePath;
    QString weather_data;
    int  count;
protected:
    void run();

signals:
    void updateWeather(QString cityName,QString cityTemperture,QString weatherStatus,QString weatherImagePath);
public slots:
    void replyFinished_getCity(QNetworkReply *reply);
    void replyFinished_getWeather(QNetworkReply *reply);
};

#endif // WEATHER_H