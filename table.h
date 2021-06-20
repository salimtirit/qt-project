#ifndef table_H
#define table_H

#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QLabel>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QMap>
#include <QStringList>

class  table: public QLabel {
	Q_OBJECT

private:
	QLabel *label;
	QString url;
	QMap<QString,QString> symbolMap;
	QMap<QString,QString> nameMap;
	QNetworkAccessManager *manager;
	QStringList arr;
	

public:
	table(QStringList arr,QWidget *parent = 0);
	QTableWidget *tableWidget;
	 	
public slots:
	void replyFinished(QNetworkReply * reply) ; 
	void dataReceived(QNetworkReply * reply);
	void getResponse(QStringList arr);
};

#endif
