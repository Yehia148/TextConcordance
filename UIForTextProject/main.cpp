#include "mainwindow.h"
#include "..\TrieConcordance.h"
//#include "..\map.h"
#include <QApplication>
using namespace std;
int main(int argc, char *argv[])
{
    TrieConcordance test1;
    //Map test2;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
