/** @file scicall.h
 *  @brief main.pp file
           
 *
 *  main.pp file to execute program. 
    Includes scical header file
    
 *
 *  @author Billy Jean Baptiste
 
 *  @bug No known bugs.
 */



#include "scical.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SciCal w;
    w.show();
    return a.exec();
}
