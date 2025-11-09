#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "..\TrieConcordance.h"
#include "..\ConcordanceTree.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    TrieConcordance frequency;

}

