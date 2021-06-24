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
	
	//qputenv("MYCRYPTOCONVERT", "/home/cmpe250student/Desktop/project3/input.txt"); for running the code
	QString inputFile = qgetenv("MYCRYPTOCONVERT");

	std::ifstream infile;
	infile.open(inputFile.toStdString());

	QStringList arr;
	QString s;

	std::string line;
	while(getline(infile,line)){   //constructing an array from given input crypto currencies
		arr.append(QString::fromStdString(line));
	}
	
	table *my = new table(arr);  //creating a table object
	my->tableWidget->show();  //showing the object

	return app.exec();
}
