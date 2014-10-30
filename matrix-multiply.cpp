#include "argumentlist.h"
#include <QFile>
#include <QTextStream>
#include "QStream.h"
#include <QList>
#include <QVector>
#include <QPair>
#include <pthread.h>

struct matrix {
    QList<QList<double> > matrix;
    QPair<int, int> dim; //m rows, n columns;
    QString fileName;
};

//global variables
	QList<QList<double> > outputArray;
	matrix matrix1;
	matrix matrix2;

QStringList argumentParse(int argc, char *argv[]);

void* readData(void *arg);

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

	for(int i = 0; i < outputMatrix.first*outputMatrix.second; i++)
	{
		
	}
	for(int i = 0; i < matrix1.dim.first; i++)
	{
		QList<double> list;
		outputArray.append(list);
		for(int j = 0; j < matrix2.dim.second; j++)
			outputArray[i].append(0.0);
	}
	for (int row = 0; row < outputMatrix.first; row++) {
        for (int col = 0; col < outputMatrix.second; col++) {
            // Multiply the row of A by the column of B to get the row, column of product.
            for (int inner = 0; inner < matrix1.dim.second; inner++) {
                outputArray[row][col] += matrix1.matrix[row][inner] * matrix2.matrix[inner][col];
            }
            qout << outputArray[row][col] << "\t";
        }
        qout << endl;
    }

	qout << matrix1.dim.first << "x" << matrix1.dim.second << endl;


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
