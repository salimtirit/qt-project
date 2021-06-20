#include <QtGui>
#include "table.h"
#include <QRegExp>
#include <QJsonObject>
#include <QDebug>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QWidget>

table::table(QStringList arr,QWidget *parent) : QLabel(parent)
{
     label = new QLabel("Connecting");
     QHBoxLayout *layout = new QHBoxLayout;

//Table creation

     this->tableWidget = new QTableWidget();

   
//Until here

     layout->addWidget(label);
     setLayout(layout);

     this->arr = arr;

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

     getResponse(this->arr);
}

void table::getResponse(QStringList arr){
     manager = new QNetworkAccessManager(this) ;
     connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
     url = "https://api.coingecko.com/api/v3/simple/price?ids=";
     QString add = "";
     for (int i = 0; i < arr.size();i++){
          QString x = arr[i];
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
     manager->get(QNetworkRequest(QUrl(url)));
}


void table::replyFinished(QNetworkReply *reply){
     //we may use json here
     QString str ;

     QString data = (QString) reply->readAll();
     QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
     QJsonObject json_obj = jsonResponse.object();
     QStringList keys = json_obj.keys();
     // read the data fetched from the web site
     //QMap<QString,QString[3]> result;

     str = this->url;
     for(int i = 0; i< keys.size();i++){
          qDebug() << keys.at(i);
          qDebug() << json_obj[keys.at(i)].toObject()["usd"].toDouble();
          qDebug() << json_obj[keys.at(i)].toObject()["eur"].toDouble();
          qDebug() << json_obj[keys.at(i)].toObject()["gbp"].toDouble();
     }
     


     tableWidget->setRowCount(arr.size());
     tableWidget->setColumnCount(3);

     for (int i = 0; i < this->arr.size(); ++i){
          for (int j = 0; j < 3; ++j){ 

               QTableWidgetItem *item = new QTableWidgetItem(); 
               tableWidget->setItem(i,j,item);
          }
     }
     
 
     tableWidget->show();



     // set the text of the label 
     label->setText(str) ;
}
