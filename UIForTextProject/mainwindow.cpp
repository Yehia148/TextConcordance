#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "..\TrieConcordance.h"
//#include "..\map.h"
#include <QMessageBox>
#include <QRegularExpression>
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
    //wordMap = Map();
    trie = TrieConcordance();
    QString text = ui->inputTextEdit->toPlainText().trimmed();


    if (text.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter some text first.");
        return;
    }
    QStringList words = text.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);


    for (int i = 0; i < words.size(); ++i) {
        QString w = words[i].toLower();
       // wordMap.put_word(w.toStdString());

        QString next = (i + 1 < words.size()) ? words[i + 1].toLower() : "";
        trie.insert(w.toStdString(), next.toStdString());
    }

    //vector<pair<string, int>> allWords = wordMap.sort_by_frequency();
    //if (allWords.empty()) {
   //     QMessageBox::information(this, "Info", "No words found.");
   //     return;
  //  }

   // mostFrequentWord = QString::fromStdString(allWords.back().first);
   // ui->frequentWordLabel->setText(mostFrequentWord);

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

