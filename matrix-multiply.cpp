#include "argumentlist.h"
#include <QFile>
#include <QTextStream>
#include "QStream.h"
#include <QList>
#include <QVarLengthArray>
#include <QPair>
#include <pthread.h>

struct matrix {
    QList<QList<double> > matrix;
    QPair<int, int> dim; //m rows, n columns;
    QString fileName;
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

void* readData(void *arg)
{
	QRegExp rx("(\\s|\\s+|\\t)");
	struct matrix *myMatrix = (struct matrix*)arg;
	QFile file(myMatrix->fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		qout << "You did not enter a valid file." << endl;
		exit(0);
	}

	QTextStream stream(&file);
	while(!stream.atEnd()){
		QString line = stream.readLine();
		QStringList tempList  = line.split(rx);
		QList<double> column;
		for(int i = 0; i < tempList.size(); i++)
		{
			column.append(tempList[i].toDouble());
		}

		myMatrix->matrix.append(column);
		myMatrix->dim.second = tempList.size();
		(myMatrix->dim.first)++;
	}

}


int main(int argc, char* argv[])
{
	QStringList fileList; //a list of the two matrices
	fileList = argumentParse(argc, argv);

	matrix matrix1;
	matrix matrix2;
	matrix1.fileName = fileList[0];
	matrix2.fileName = fileList[1];

	qout << matrix1.fileName << endl;

	struct matrix *matrix1ptr = &matrix1;
	struct matrix *matrix2ptr = &matrix2;
	pthread_t thread_tid[2];
	pthread_create(&thread_tid[0], NULL, readData, (void*) matrix1ptr);
	pthread_create(&thread_tid[1], NULL, readData, (void*) matrix2ptr);
	pthread_join(thread_tid[0],NULL);
	pthread_join(thread_tid[1], NULL);

	

	for(int i = 0; i < matrix1.dim.first; i++)
	{
		for(int j = 0; j < matrix1.dim.second; j++)
		{
			qout << matrix1.matrix[i][j]<< "\t";
		}
		qout << endl;
	}

	qout << endl;

	for(int i = 0; i < matrix2.dim.first; i++)
	{
		for(int j = 0; j < matrix2.dim.second; j++)
		{
			qout << matrix2.matrix[i][j]<< "\t";
		}
		qout << endl;
	}

	qout << matrix1.dim.first << "x" << matrix1.dim.second << endl;

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
