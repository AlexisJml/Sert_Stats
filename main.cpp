#include "ihm_sert.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ihm_sert w;
    w.showMaximized();
    w.show();
    return a.exec();
}
