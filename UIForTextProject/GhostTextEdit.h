
#ifndef TEXTCONCORDANCE_GHOSTTEXTEDIT_H
#define TEXTCONCORDANCE_GHOSTTEXTEDIT_H

#include <QTextEdit>
#include <QString>

class GhostTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit GhostTextEdit(QWidget* parent = nullptr)
        : QTextEdit(parent) {}

    void setGhostText(const QString& text) { ghostText = text; update(); }

protected:
    void paintEvent(QPaintEvent* e) override;

private:
    QString ghostText;
};

#endif // GHOSTTEXTEDIT_H