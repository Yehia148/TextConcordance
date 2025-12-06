#include "GhostTextEdit.h"
#include <QPainter>
#include <QTextCursor>

void GhostTextEdit::paintEvent(QPaintEvent* e)
{
    QTextEdit::paintEvent(e);

    if (ghostText.isEmpty())
        return;

    QTextCursor c = textCursor();
    QRect cr = cursorRect(c);

    QPainter p(viewport());
    p.setPen(QColor(160, 160, 160)); // light grey

    QFontMetrics fm(font());
    int y = cr.bottom();                // baseline
    int x = cr.left();

    p.drawText(x, y, ghostText);
}
