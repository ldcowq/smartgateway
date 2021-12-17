#ifndef WEATHERINFO_H
#define WEATHERINFO_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QNetworkAccessManager>
#include <QTextCodec>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include<QJsonArray>
#include <QTimer>
#define QUERY_IP_URL "http://ip.ws.126.net/ipquery"
#define QUERY_WEATHER_URL "http://wthrcdn.etouch.cn/weather_mini?city="
class WeatherInfo : public QObject
{
    Q_OBJECT
public:
    explicit WeatherInfo(QObject *parent = nullptr);
    QNetworkAccessManager *netWorkManager;
    QTextCodec *textCodec;
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QJsonParseError jsonError;
    QString cityName;
    QString imagePath;
    QString weather_data;
    int  count;
    QTimer *weatherTimer;
signals:
    void updateWeather(QString cityName,QString cityTemperture,QString weatherStatus,QString weatherImagePath);
public slots:
    void replyFinished_getCity(QNetworkReply *reply);
    void replyFinished_getWeather(QNetworkReply *reply);
    void getWeatherInfo(void);
};

#endif // WEATHERINFO_H
