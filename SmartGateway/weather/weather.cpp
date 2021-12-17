#include "weather.h"
#include <QDebug>
Weather::Weather()
{

}

void Weather::run()
{
    qDebug() << "当前线程对象的地址: " << QThread::currentThread();
    while(1)
    {
        netWorkManager = new QNetworkAccessManager(this);
        netWorkManager->get(QNetworkRequest(QUrl(QUERY_IP_URL)));//根据网络获取地级市
        connect(netWorkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished_getCity(QNetworkReply*)));
        QThread::sleep(5000);
        qDebug() << "拉取天气次数："<<count++ ;
    }

}

void Weather::replyFinished_getCity(QNetworkReply* reply)
{
    textCodec = QTextCodec::codecForName("gbk");
    cityName = textCodec->toUnicode(reply->readAll());
    //最后要释放reply对象
    qDebug()<<cityName;
    /*  判断获取的字符串是否为空　*/
    if(cityName.isEmpty()||cityName.isNull())
    {
        //weather_cityName_QLabel->setText("未知");
        //weather_temperature_QLabel->setText("未知");
        //weather_image_QLabel->setStyleSheet("border-image:/weather/image/refresh.png");
        //weather_imageName_QLabel->setText("请求失败");
        emit updateWeather("未知","未知","border-image:/weather/image/refresh.png","未知");
        return;
    }
    int startIndex = cityName.indexOf(":")+2;
    int endIndex = cityName.lastIndexOf(",")-2;
    cityName = cityName.mid(startIndex,endIndex-startIndex);//获取到城市名
    //weather_cityName_QLabel->setText(cityName);//显示当前网络归属地城市的名称
    reply->deleteLater();


    /**************使用城市名，获取该地区天气**************************/
    netWorkManager = new QNetworkAccessManager(this);
    netWorkManager->get(QNetworkRequest(QUrl(QUERY_WEATHER_URL+cityName)));
    connect(netWorkManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished_getWeather(QNetworkReply*)));
}


void Weather::replyFinished_getWeather(QNetworkReply* reply)
{
    QTextCodec*textCodec = QTextCodec::codecForName("utf8");
    //使用utf8编码，这样才可以显示中文
    QString weatherInfo = textCodec->toUnicode(reply->readAll());
    qDebug()<<weatherInfo;
    reply->deleteLater();   //最后要释放reply对象

    /*     解析天气的json数据        */
    jsonDocument = QJsonDocument::fromJson(weatherInfo.toUtf8(),&jsonError);
    if(jsonError.error==QJsonParseError::NoError)
    {
        if(jsonDocument.isNull()||jsonDocument.isEmpty())
        {
            //weather_cityName_QLabel->setText("未知");
            //weather_temperature_QLabel->setText("未知");
            //weather_image_QLabel->setStyleSheet("border-image:url("":/weather/image/refresh.png"")");
            //weather_imageName_QLabel->setText("点击刷新");
            emit updateWeather("未知","未知","border-image:/weather/image/refresh.png","未知");
        }else {
            if(jsonDocument.isObject())
            {
                jsonObject = jsonDocument.object();
                jsonObject = jsonObject.value("data").toObject();

                weather_data = jsonObject.value("wendu").toString()+"℃";
                //weather_temperature_QLabel->setText(weather_data);

                QJsonArray forecast_data = jsonObject.value("forecast").toArray();
                QJsonObject obj = forecast_data.at(0).toObject();
                weatherInfo = obj.value("type").toString();
                //weather_imageName_QLabel->setText(weatherInfo);
                qDebug()<<weatherInfo<<endl;
                if(weatherInfo=="大雨") imagePath = QString("border-image:url("":/weather/image/heavyrain.png"")");
                if(weatherInfo=="小雨") imagePath = QString("border-image:url("":/weather/image/lightrain.png"")");
                if(weatherInfo=="多云") imagePath = QString("border-image:url("":/weather/image/cloudy.png"")");
                if(weatherInfo=="阵雨") imagePath = QString("border-image:url("":/weather/image/shower.png"")");
                if(weatherInfo=="中雨") imagePath = QString("border-image:url("":/weather/image/middlerain.png"")");
                if(weatherInfo=="晴") imagePath = QString("border-image:url("":/weather/image/sunny.png"")");
                if(weatherInfo=="雷阵雨") imagePath = QString("border-image:url("":/weather/image/thundershower.png"")");
                emit updateWeather(cityName,weather_data,imagePath,weatherInfo);
            }
        }

    }
}
