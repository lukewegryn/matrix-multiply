# ifndef QSTREAMTHREADED_H
# define QSTREAMTHREADED_H

# include <QTextStream>
# include <pthread.h>

# define OTSTREAM(x, y) do {					\
	if(pthread_mutex_lock(&mutex_##x) != 0){	\
		exit(1);								\
	}											\
	x << y;										\
	if(pthread_mutex_unlock(&mutex_##x) != 0){	\
		exit(1);								\
	}											\
} while(0)

# define ITSTREAM(x, y) do {					\
	if(pthread_mutex_lock(&mutex_##x) != 0){	\
		exit(1);								\
	}											\
	x >> y;										\
	if(pthread_mutex_unlock(&mutex_##x) != 0){	\
		exit(1);								\
	}											\
} while(0)

# define QERR(y) OTSTREAM(qerr, y)
# define QOUT(y) OTSTREAM(qout, y)
# define  QIN(y) ITSTREAM(qin , y)

extern QTextStream qout;
extern QTextStream qerr;
extern QTextStream qin;

extern pthread_mutex_t mutex_qout;
extern pthread_mutex_t mutex_qerr;
extern pthread_mutex_t mutex_qin;

# endif // QSTREAMTHREADED_H
