#include "argumentlist.h"
#include <QFile>
#include <QTextStream>
#include "QStream.h"
#include <QList>
#include <QVarLengthArray>
#include <QPair>
#include <pthread.h>

struct matrix {
    QTextStream matrixStream;
    QList<QList<double> > matrix;


};

QStringList argumentParse(int argc, char *argv[])
{
	ArgumentList al(argc, argv);
	al.takeFirst();
	QStringList argumentList;
	int i = 0;
	if(al.isEmpty())
	{
		qout << "You need to supply two valid files." << endl;
		exit(0);
	}
	else
	{
		while(!al.isEmpty())
		{
			argumentList.append(al.takeFirst());
		}	
	}
	return argumentList;
}

void *readData(void *List)
{
	while(!matrixStream1.atEnd()){
		QString line = matrixStream1.readLine();
		QStringList tempList  = line.split(rx);
		QList<double> column;
		for(int i = 0; i < tempList.size(); i++)
		{
			column.append(tempList[i].toDouble());
		}
		matrix1.append(column);
		mDim_1.second = tempList.size();
		mDim_1.first++;
	}
}


int main(int argc, char* argv[])
{
	QStringList fileList; //a list of the two matrices
	fileList = argumentParse(argc, argv);

	QFile file1(fileList[0]);
	QFile file2(fileList[1]);

	if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qout << "You did not enter a valid file." << endl;
		exit(0);
	}
	if(!file2.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qout << "You did not enter a valid file." << endl;
		exit(0);
	}


	QList<QList<double> > matrix1;
	QList<QList<double> > matrix2;
	QPair<int, int> mDim_1; //m rows, n columns
	QPair<int, int> mDim_2; //m rows, n columns
	mDim_1.first = 0;
	mDim_1.second = 0;
	mDim_2.first = 0;
	mDim_2.second = 0;

	QTextStream matrixStream1(&file1);
	QTextStream matrixStream2(&file2);

	QRegExp rx("(\\s|\\t)");

	

	for(int i = 0; i < mDim_1.first; i++)
	{
		for(int j = 0; j < mDim_1.second; j++)
		{
			qout << matrix1[i][j]<< "\t";
		}
		qout << endl;
	}

	qout << mDim_1.first << "x" << mDim_1.second << endl;

	//QVarLengthArray<



}

/*while(!matrixStream1.atEnd()){
		QString line = matrixStream1.readLine();
		QStringList tempList  = line.split(rx);
		QList<double> column;
		for(int i = 0; i < tempList.size(); i++)
		{
			column.append(tempList[i].toDouble());
		}
		matrix1.append(column);
		mDim_1.second = tempList.size();
		mDim_1.first++;
	}*/
