#include <iostream>
#include <fstream>
#include <QtCore>
#include <QtGlobal>
#include <QApplication>
#include <QDebug>
#include <QStringList>
#include "table.h"


int main(int argc,char *argv[])
{
	QApplication app(argc, argv);
	

	qputenv("MYCRYPTOCONVERT", "/home/cmpe250student/Desktop/project3/input.txt");
	QString inputFile = qgetenv("MYCRYPTOCONVERT");
	qDebug() << inputFile;
	//string inputFile = "input.txt";

	std::ifstream infile;
	infile.open(inputFile.toStdString());

	QStringList arr;

	QString s;
	std::string line;
	while(getline(infile,line)){
		arr.append(QString::fromStdString(line));
	}
	qDebug() << s;
	
	table *my = new table(arr);
	//std::string base_url = "https://api.coingecko.com/api/v3/simple/price?ids=";

	//my.getResponse(arr);
	my->show(); 

	return app.exec();
}