#include <QtGui>
#include "table.h"
#include <QJsonObject>
#include <QDebug>
#include <QHeaderView>
#include <QSpacerItem>
#include <QWidget>

table::table(QStringList arr,QWidget *parent) : QLabel(parent)
{

//Table creation
     this->tableWidget = new QTableWidget();

     //QTableWidget::setHorizontalHeaderItem()
//Until here

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
     QString data = (QString) reply->readAll();
     QJsonDocument jsonResponse = QJsonDocument::fromJson(data.toUtf8());
     QJsonObject json_obj = jsonResponse.object();
     QStringList keys = json_obj.keys();

     tableWidget->setRowCount(keys.size());
     tableWidget->setColumnCount(3);


     QStringList Hheaders;
     Hheaders.append("USD");
     Hheaders.append("EUR");
     Hheaders.append("GBP");
     tableWidget->setHorizontalHeaderLabels(Hheaders);
     QStringList Vheaders;
     for (int i = 0; i < keys.size(); i++){
          QString a = keys.at(i);
          QString first = a.replace(0,1,a[0].toUpper());
          Vheaders.append(first);

          QTableWidgetItem *item0 = new QTableWidgetItem(QString::number(json_obj[keys.at(i)].toObject()["usd"].toDouble()));

          tableWidget->setItem(i,0,item0);

          QTableWidgetItem *item1 = new QTableWidgetItem(QString::number(json_obj[keys.at(i)].toObject()["eur"].toDouble()));

          tableWidget->setItem(i,1,item1);

          QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(json_obj[keys.at(i)].toObject()["gbp"].toDouble()));

          tableWidget->setItem(i,2,item2);
     }

     tableWidget->setVerticalHeaderLabels(Vheaders);

     tableWidget->resize(380 , keys.size()*35);
}
