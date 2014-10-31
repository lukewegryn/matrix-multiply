# include "QStreamThreaded.h"

QTextStream qout(stdout, QIODevice::WriteOnly);
QTextStream qerr(stderr, QIODevice::WriteOnly);
QTextStream qin (stdin , QIODevice::ReadOnly );

pthread_mutex_t mutex_qout = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_qerr = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_qin  = PTHREAD_MUTEX_INITIALIZER;
