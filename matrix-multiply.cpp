#include "argumentlist.h"
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QVector>
#include <QPair>
#include <pthread.h>
#include <QStreamThreaded.h>
#include <QValidator>

struct matrix {
    QList<QList<double> > matrix;
    QPair<int, int> dim; //m rows, n columns;
    QString fileName;
    bool isDecimal;
    bool isInt;
};

//global variables, make sure not to use these anywhere else
	QList<QList<double> > outputArray;
	matrix matrix1;
	matrix matrix2;

QStringList argumentParse(int argc, char *argv[]);

void* readData(void *arg);
void* multiplyMatrix(void *arg);
bool isValidFloat(QString value);

int main(int argc, char* argv[])
{
	QStringList fileList; //a list of the two matrices
	fileList = argumentParse(argc, argv);

	QPair<int, int> outputMatrix;

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

	outputMatrix.first = matrix1.dim.first;
	outputMatrix.second = matrix2.dim.second;

	pthread_t matrixThread[outputMatrix.first*outputMatrix.second];
	//pthread_attr_t attr;

	//pthread_attr_init(&attr);
	//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for(int i = 0; i < matrix1.dim.first; i++)
	{
		QList<double> list;
		outputArray.append(list);
		for(int j = 0; j < matrix2.dim.second; j++)
			outputArray[i].append(0.0);
	}

	for(int i = 0; i < outputMatrix.first*outputMatrix.second; i++)
	{
		int rc = pthread_create(&matrixThread[i], NULL, multiplyMatrix, (void*)i);
		if(rc){
			qout << "Unable to create thread" << rc << endl;
			exit(-1);
		}
	}

	for(int i = 0; i < outputMatrix.first*outputMatrix.second; i++)
	{
		pthread_join(matrixThread[i], NULL);
	}


    for(int i = 0; i < outputArray.size(); i++)
    {
    	for(int j = 0; j < outputArray[i].size(); j++)
    	{
    		qout << outputArray[i][j] << "\t";
    	}
    	qout << endl;
    }
pthread_exit(NULL);

}

void* readData(void *arg)
{
	QString myString = "1.0001";
	if(isValidFloat(myString))
	{
		QOUT("Valid");
	}
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

void* multiplyMatrix(void *arg){
	long position = (long)arg;
	int width = matrix2.dim.second;
	int column = position%(width); //output column index, matrix 2 column
	int row = position/(width); //output row index, matrix 1 row
	outputArray[row][column] = 0;
	for(int i = 0; i < matrix1.dim.second; i++)
	{
		outputArray[row][column] += matrix1.matrix[row][i]*matrix2.matrix[i][column];
	}

}

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

bool isValidFloat(QString value)
{
	bool isValid = false;
	QDoubleValidator *doubleValidate = new QDoubleValidator();
	doubleValidate->setDecimals(4);
	doubleValidate->setNotation(QDoubleValidator::StandardNotation);

	int r = 0;
	int isFloat = doubleValidate->validate(value, r);
	if(isFloat == 2)
	{
		if(value.contains("."))
		{
			QStringList s = value.split('.');
			if(s[1].size() == 4)
				{
					isValid = true;
				}
		}
	}

	return isValid;
}

bool isValidInt(int value)
{
	
}
