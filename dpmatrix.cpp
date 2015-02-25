#include "dpmatrix.h"
#include "ui_mainwindow.h"

DPMatrix::DPMatrix(QWidget *parent) : QWidget(parent)
{
    squareSize = 30;
    source = INIT_STRING;
    target = INIT_STRING;
    rows = target.length() + 1;
    columns = source.length() + 1;
    setGeometry(0, 0, squareSize * columns, squareSize * rows);
    setMouseTracking(true);
}

void DPMatrix::mouseMoveEvent(QMouseEvent *event)
{

}

void DPMatrix::mousePressEvent(QMouseEvent *event)
{

}

void DPMatrix::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(0, 0, columns * squareSize , rows * squareSize, QBrush(Qt::white));

    painter.setPen(QPen(Qt::gray));
    for (int row = 0; row < rows; ++row)
        for (int column = 0; column < columns; ++column)
            painter.drawRect(column*squareSize, row*squareSize, squareSize, squareSize);

    /*
    QFontMetrics fontMetrics(displayFont);
    painter.setPen(QPen(Qt::black));
    for (int row = beginRow; row <= endRow; ++row) {

        for (int column = beginColumn; column <= endColumn; ++column) {

            int key = row*columns + column;
            painter.setClipRect(column*squareSize, row*squareSize, squareSize, squareSize);

            if (key == lastKey)
                painter.fillRect(column*squareSize + 1, row*squareSize + 1, squareSize, squareSize, QBrush(Qt::red));

            painter.drawText(column*squareSize + (squareSize / 2) - fontMetrics.width(QChar(key))/2,
                             row*squareSize + 4 + fontMetrics.ascent(),
                             QString(QChar(key)));
        }
    }
    */
}

DPMatrix::~DPMatrix()
{

}

