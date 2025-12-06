#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "..\TrieConcordance.h"
#include "..\map.h"
#include "GhostTextEdit.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:  

    void on_suggestButton_clicked();

    void on_analyzeButton_clicked();

    void onInputTextChanged();

private:
    Ui::MainWindow *ui;
  Map*wordMap;
    TrieConcordance trie;
    QString mostFrequentWord;
    const int frequency = 5;
    QString currentSuggestion;

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};
#endif // MAINWINDOW_H
