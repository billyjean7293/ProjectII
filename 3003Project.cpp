#include "scical.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SciCal w;
    w.show();
    return a.exec();
}
