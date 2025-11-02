#include "mainwindow.h"
#include "..\TrieConcordance.h"
#include "..\ConcordanceTree.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    TrieConcordance test1;
    ConcordanceTree test2;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
