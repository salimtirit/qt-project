#include <QtGui>
#include "table.h"
#include <QRegExp>
#include <QJsonObject>
#include <QDebug>

table::table(QWidget *parent) : QLabel(parent)
{
     label = new QLabel("Connecting");
     QHBoxLayout *layout = new QHBoxLayout;

     layout->addWidget(label);
     setLayout(layout);


     manager = new QNetworkAccessManager(this) ; 
     manager->get(QNetworkRequest(QUrl("https://api.coingecko.com/api/v3/coins/list")));
     connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(dataReceived(QNetworkReply *)));
     // Initiate retrieval of  the data from the web page.
     // When completed, slot replyFinished will be called.
     
     //string url = "https://api.coingecko.com/api/v3/simple/price?ids=btc,litecoin&vs_currencies=usd,eur,gbp";
     //string url2 = "https://api.coingecko.com/api/v3/coins/list";
}
void table::dataReceived(QNetworkReply *reply){
     QString data = (QString) reply->readAll();
     QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
     QJsonArray json_array = jsonResponse.array();

     foreach (const QJsonValue &value, json_array) {
          QJsonObject json_obj = value.toObject();
          this->symbolMap.insert(json_obj["symbol"].toString(),json_obj["id"].toString());
          this->nameMap.insert(json_obj["name"].toString(),json_obj["id"].toString());
     }

     QStringList arr;
     arr.append("eth");
     arr.append("xrp");
     arr.append("Cardano");
     arr.append("Litecoin");
     getResponse(arr);
}

void table::getResponse(QStringList arr){
     manager = new QNetworkAccessManager(this) ;
     connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
     url = "https://api.coingecko.com/api/v3/simple/price?ids=";
     QString add = "";
     for (int i = 0; i < arr.size();i++){
          QString x = arr[i];
          qDebug() << x;
          qDebug() << symbolMap.isEmpty();
          if(this->symbolMap.contains(x)){
               if(add=="")
                    add = symbolMap[x];
               else
                    add = add + "," + symbolMap[x];
          }else if(this->nameMap.contains(x)){
               if(add=="")
                    add = nameMap[x];
               else
                    add = add + "," + nameMap[x];
          }else{
               qDebug() << "problem occured retriving list of currencies";
          }
     }
     url = url + add + "&vs_currencies=usd,eur,gbp";
     qDebug() << url;
     manager->get(QNetworkRequest(QUrl(url)));
}


void table::replyFinished(QNetworkReply *reply){
     //we may use json here
     QString str ;

     QString data = (QString) reply->readAll();
     QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
     QJsonArray json_array = jsonResponse.array();
     // read the data fetched from the web site
     //QMap<QString,QString[3]> result;
     
     for (int i = 0; i < 2; ++i)
     {
          qDebug() << json_array.at(i).toString();
     }
     str = this->url;
     //QString key =  
     //QJsonValue value =  QJsonObject::take(const QString &key);
     // use pattern matching to extract the rate 
/**     QRegExp rx("\"last\": \"(\\d+\\.\\d+)\"");

     if ( rx.indexIn(data, pos) != -1 ) {
       str = QString("BTC/USD:  ") + rx.cap(1);    // rate found 
     }
     else {
       str = QString("Error") ; 
     }
**/


     // set the text of the label 
     label->setText(str) ;
}
