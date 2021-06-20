#ifndef table_H
#define table_H

#include <QtGui>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QLabel>
#include <QHBoxLayout>
#include <QMap>
#include <QStringList>

class  table: public QLabel {
	Q_OBJECT

private:
	QLabel *label;
	QString url;
	QMap<QString,QString> symbolMap;
	QMap<QString,QString> nameMap;
	QNetworkAccessManager *manager ;

public:
	table(QWidget *parent = 0);
	 	
public slots:
	void replyFinished(QNetworkReply * reply) ; 
	void dataReceived(QNetworkReply * reply);
	void getResponse(QStringList arr);
};

#endif