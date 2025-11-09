#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "..\TrieConcordance.h"
//#include "..\map.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->analyzeButton, &QPushButton::clicked, this, &MainWindow::on_analyzeButton_clicked);
    connect(ui->suggestButton, &QPushButton::clicked, this, &MainWindow::on_suggestButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_analyzeButton_clicked()
{
    QString text = ui->inputTextEdit->toPlainText().trimmed();
    //wordMap = Map();
    trie = TrieConcordance();

    if (text.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter some text first.");
        return;
    }

}
void MainWindow::on_suggestButton_clicked()
{
    if (mostFrequentWord.isEmpty()) {
        QMessageBox::warning(this, "Error", "Analyze text first.");
        return;
    }

    QString text = ui->inputTextEdit->toPlainText();
    string key = mostFrequentWord.toStdString();

}

