#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "..\TrieConcordance.h"
#include "..\map.h"
#include <QMessageBox>
#include <QRegularExpression>
#include "../WordNetSynonyms.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), wordMap(nullptr)
{
    ui->setupUi(this);
    connect(ui->analyzeButton, &QPushButton::clicked, this, &MainWindow::on_analyzeButton_clicked);
    connect(ui->suggestButton, &QPushButton::clicked, this, &MainWindow::on_suggestButton_clicked);
} //This syntax is what connects QT buttons and the ones that user is able to press with the functionalities below

MainWindow::~MainWindow()
{
    delete ui;
    delete wordMap;
}


void MainWindow::on_analyzeButton_clicked()
{
    if(wordMap){
        delete wordMap;
        wordMap = nullptr;
    }
    //WHen the user clicks analyze button several times, remove the old data so that you can provide frequency for new text
    //we equal wordMap to nullptr so that we dont accidentally use a deleted pointer, helps avoid bug issues.

    wordMap = new Map(); //allocates a fresh hash-map-like structure to count word frequencies
    trie = TrieConcordance(); //this resets the trie to an empty structure
    QString text = ui->inputTextEdit->toPlainText().trimmed();
        //inputtextedit is a QTTextEdit widget, and the function toPlaintext() gets the full text inside
        //the purpose of .trimmed() is that it removes trailing or leading whitespace
        //QString is the string class in QT
    if (text.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter some text first.");
        return;
    }
    //this is a warning message to the user if there is no text inputted
    QStringList words = text.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);
    //slices text where separators match
    //this QStringList is QT's dynamic list class, and this splits the text ingoring punctuation
    //into words using a regular expression, \\W+ is one or more non-word characters (non-letters, non digits, non underscore)
    //for (non-letters, non digits, non underscore), it removes them because the act as separators
    //the split tells splitemptyparts not to include empty strings in the result
 //   If you have consecutive separators (e.g., ", ,"), you won't get "" entries.

    //Examples:

    //state-of-the-art -> ["state", "of", "the", "art"]
    //
    for (int i = 0; i < words.size(); ++i) {
        QString w = words[i].toLower();
       wordMap->put_word(w.toStdString());
        //the loop extracts every word and tolower() standardizes everything to lowercase
        //converts QString to std::string using toStdString().
        //finally it inserts it into our map, the backend frequency map

        QString next = (i + 1 < words.size()) ? words[i + 1].toLower() : "";
        trie.insert(w.toStdString(), next.toStdString());
        //the two lines above handles building the bigram (next-word) data.
        // if there's a next word, use it, and otherwise (last word), next = "".
    }

    vector<pair<string, int>> allWords = wordMap->sort_by_frequency();

   // extracts all the words and frequencies from the map, sorted from least to most frequent
    //sort_by_frequency performance merge sort
    if (allWords.empty()) {
       QMessageBox::information(this, "Info", "No words found.");
       return;
   }
   //if the list is empty, then return a message saying that there no words

   mostFrequentWord = QString::fromStdString(allWords.back().first);
   //returns the last element which is the most frequet because the list is sorted ascending
   //.first is the word in (string, int)
   ui->frequentWordLabel->setText(mostFrequentWord);
   //updates a label on the UI to show the result

   //If all words have the same frequncy, the last word in the sorted list is most frequent
   //the "most frequrent" is the last word in the hash table traversal

}
void MainWindow::on_suggestButton_clicked()
{
    if (mostFrequentWord.isEmpty()) {
        QMessageBox::warning(this, "Error", "Analyze text first.");
        return;
    }

    // make the most frequent word into string for WordNet
    std::string key = mostFrequentWord.toStdString();

    // calling the WordNet synonym function
    std::vector<std::string> synonyms = getSynonyms(key);

    QString formatted;

    if (synonyms.empty()) {
        formatted = QString("No synonyms found in WordNet for \"%1\".")
                        .arg(mostFrequentWord);
    } else {
        formatted += "Top Synonyms for \"" + mostFrequentWord + "\":\n\n";
        for (const auto &s : synonyms) {
            formatted += "• " + QString::fromStdString(s) + "\n";
        }
    }


    ui->suggestionOutput->setPlainText(formatted);
}



