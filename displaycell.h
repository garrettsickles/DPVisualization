#ifndef DISPLAYCELL_H
#define DISPLAYCELL_H

#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QPoint>
#include <QRect>

class DisplayCell
{
public:
    DisplayCell(QString, QColor, QColor);
    ~DisplayCell();

    void setPainter(QPainter);
    void draw();

    void setValue(QString);
    QString getValue();

    void setBounds(QRect);
    QRect getBounds();


private:
    QString value;
    QRect bound;
    QColor background;
    QColor outline;
};

#endif // DISPLAYCELL_H
