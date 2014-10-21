#include "argumentlist.h"
#include <QFile>
#include <QTextStream>
#include "QStream.h"
#include <QList>

bool argumentParse(int argc, char *argv[], QTextStream &matrix1, QTextStream &matrix2)
{
	bool isSuccess = true;
	ArgumentList al(argc, argv);
	al.takeFirst();
	int i = 0;
	while(!al.isEmpty())
	{
		QString fileName = al.takeFirst();
		QFile data(fileName);
		if(!data.open(QFile::ReadOnly | QIODevice::Text))
		{
			isSuccess = false;
			break;
		}
		else
		{
			matrix[i] = QTextStream(&data);
		}
		i++;
	}

	return isSuccess;
}
int main(int argc, char* argv[])
{
	QList<QTextStream*> matrix; //a list of the two matrices
	qout << argumentParse(argc, argv, matrix) << endl;

}