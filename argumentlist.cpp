#include <QCoreApplication>
#include <QDebug>
#include "argumentlist.h"

/** Obtain the command line arguments from the currently
    running QApplication */
ArgumentList::ArgumentList() {
   if (qApp != NULL)  /* A global pointer to the current QApplication. */
      *this = qApp->arguments();
}


void ArgumentList::argsToStringlist(int argc, char * argv []) {
   for (int i=0; i < argc; ++i) {
      *this += argv[i];
   }
}

bool ArgumentList::getSwitch (QString option) {
   QMutableStringListIterator itr(*this);
   while (itr.hasNext()) {
     if (option == itr.next()) {
        itr.remove();
        return true;
     }
   }
    return false;
}


QString ArgumentList::getSwitchArgContains(QString option, QString defaultValue)
{
  if (isEmpty())
      return defaultValue;
   QMutableStringListIterator itr(*this);
   while (itr.hasNext()) {
      if (itr.next().contains(option)) {
         if (itr.hasNext()) {
            QString retval = itr.value();//itr.next();
            itr.remove();
            return retval;
          }
        }
   }
   return defaultValue;
}

QString ArgumentList::getFlagContains(QString option, QString defaultValue)
{
   if (isEmpty())
      return defaultValue;
   QMutableStringListIterator itr(*this);
   while (itr.hasNext()) {
      if (itr.next().contains(option)) {
            QString retval = itr.value();
            //itr.next();
            itr.remove();
            return retval;
          }
        }
      return defaultValue;
}

QString ArgumentList::getSwitchArg(QString option, QString defaultValue) {
   if (isEmpty())
      return defaultValue;
   QMutableStringListIterator itr(*this);
   while (itr.hasNext()) {
      if (option == itr.next()) {
         itr.remove();
         if (itr.hasNext()) {
            QString retval = itr.next();
            itr.remove();
            return retval;
         }
         else {
            qDebug() << "Missing Argument for " << option;
            return QString();
         }
      }
   }
   return defaultValue;
}

