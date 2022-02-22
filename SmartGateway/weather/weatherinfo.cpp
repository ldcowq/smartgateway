#include "weatherinfo.h"
#include <QThread>
#include <QEventLoop>
WeatherInfo::WeatherInfo(QObject *parent) : QObject(parent)
{

}

void WeatherInfo::getWeatherInfo()
{
    weatherTimer = new QTimer(this);
    connect(weatherTimer,&QTimer::timeout,this,[=]{
        netWorkManager = new QNetworkAccessManager(this);
        netWorkManager->get(QNetworkRequest(QUrl(QUERY_IP_URL)));//根据网络获取地级市
        connect(netWorkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished_getCity(QNetworkReply*)));
    });
    weatherTimer->start(5000);
}

void WeatherInfo::replyFinished_getCity(QNetworkReply* reply)
{
    textCodec = QTextCodec::codecForName("gbk");
    cityName = textCodec->toUnicode(reply->readAll());
//    if(cityName.isEmpty()||cityName.isNull())
//    {
//        emit updateWeather("null","null","border-image:/weather/image/refresh.png","null");
//        return;
//    }
    int startIndex = cityName.indexOf(":")+2;
    int endIndex = cityName.lastIndexOf(",")-2;
    cityName = cityName.mid(startIndex,endIndex-startIndex);//get cityname
    reply->deleteLater();//release reply object
    cityName = "广州";

    /**************使用城市名，获取该地区天气**************************/
    netWorkManager = new QNetworkAccessManager(this);
    netWorkManager->get(QNetworkRequest(QUrl(QUERY_WEATHER_URL+cityName)));
    connect(netWorkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished_getWeather(QNetworkReply*)));
}


void WeatherInfo::replyFinished_getWeather(QNetworkReply* reply)
{
    QTextCodec*textCodec = QTextCodec::codecForName("utf8");
    //使用utf8编码，这样才可以显示中文
    QString weatherInfo = textCodec->toUnicode(reply->readAll());
    qDebug()<<weatherInfo;
    reply->deleteLater();//最后要释放reply对象

    /*     解析天气的json数据        */
    jsonDocument = QJsonDocument::fromJson(weatherInfo.toUtf8(),&jsonError);
    if(jsonError.error==QJsonParseError::NoError)
    {
        if(jsonDocument.isNull()||jsonDocument.isEmpty())
        {
            emit updateWeather("null","null","border-image:/weather/image/refresh.png","null");
        }else {
            if(jsonDocument.isObject())
            {
                jsonObject = jsonDocument.object();
                jsonObject = jsonObject.value("data").toObject();

                weather_data = jsonObject.value("wendu").toString()+"℃";
                QJsonArray forecast_data = jsonObject.value("forecast").toArray();
                QJsonObject obj = forecast_data.at(0).toObject();
                weatherInfo = obj.value("type").toString();
                //qDebug()<<weatherInfo<<endl;
                if(weatherInfo=="大雨") imagePath = QString("border-image:url("":/weather/image/heavyrain.png"")");
                if(weatherInfo=="小雨") imagePath = QString("border-image:url("":/weather/image/lightrain.png"")");
                if(weatherInfo=="多云") imagePath = QString("border-image:url("":/weather/image/cloudy.png"")");
                if(weatherInfo=="阵雨") imagePath = QString("border-image:url("":/weather/image/shower.png"")");
                if(weatherInfo=="中雨") imagePath = QString("border-image:url("":/weather/image/middlerain.png"")");
                if(weatherInfo=="晴") imagePath = QString("border-image:url("":/weather/image/sunny.png"")");
                if(weatherInfo=="雷阵雨") imagePath = QString("border-image:url("":/weather/image/thundershower.png"")");
                emit updateWeather(cityName,weather_data,imagePath,weatherInfo);//emit signal to mainThread
            }
        }

    }
}
