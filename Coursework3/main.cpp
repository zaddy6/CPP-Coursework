#include "uiform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    uiform wind;
    wind.show();
    return a.exec();
}
