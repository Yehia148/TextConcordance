#include "mainwindow.h"
#include ".\ui_mainwindow.h"
#include "..\TrieConcordance.h"
#include "..\ConcordanceTree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ConcordanceTree test1;
    TrieConcordance test2;
    test2.showWordInfo("string");

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
