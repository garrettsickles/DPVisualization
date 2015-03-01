#include "dpmatrix.h"
#include "ui_mainwindow.h"

DPMatrix::DPMatrix(QWidget *parent) : QWidget(parent)
{
    squareSize = 30;
    this->setup(INIT_STRING, INIT_STRING);
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
    QColor degree;
    painter.fillRect(0, 0, columns * squareSize , rows * squareSize, QBrush(Qt::white));

    painter.setPen(QPen(Qt::gray));
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            painter.drawRect(column*squareSize, row*squareSize, squareSize, squareSize);
        }
    }

    painter.setFont(QFont("Courier", 12));
    QFontMetrics fontMetrics(painter.font());
    painter.setPen(QPen(Qt::black));
    int i = 0;
    for (int row = 2; row < this->rows; row++) {
        i = row - 2;
        painter.drawText((squareSize / 2) - fontMetrics.width(source.at(i))/2,
                         row*squareSize + 4 + fontMetrics.ascent(),
                         QString(source.at(i)));
    }

    int j = 0;
    for (int column = 2; column < this->columns; column++) {
        j = column - 2;
        painter.drawText(column*squareSize + (squareSize / 2) - fontMetrics.width(target.at(j))/2,
                         4 + fontMetrics.ascent(),
                         QString(target.at(j)));
    }

    for (int row = 1; row < this->rows; ++row) {
        for (int column = 1; column < this->columns; ++column) {
            if(this->matrix[row - 1][column - 1] >= 0) {
                painter.setClipRect(column*squareSize, row*squareSize, squareSize, squareSize);
                degree.setHsv((120.0 * (1 - ((float)(this->matrix[row - 1][column - 1])) / (float)(this->maxLength))), 255, 255, 255);
                painter.fillRect(column*squareSize + 1, row*squareSize + 1, squareSize - 1, squareSize - 1, degree);
                painter.drawText(column*squareSize + (squareSize / 2) - fontMetrics.width(QString::number(this->matrix[row - 1][column - 1]))/2,
                        row*squareSize + 4 + fontMetrics.ascent(),
                        QString::number(this->matrix[row - 1][column - 1]));
            }
        }
    }
}

void DPMatrix::setup(QString source, QString target) {
    setSource(source);
    setTarget(target);

    if(source.length() > target.length()) this->maxLength = source.length();
    else this->maxLength = target.length();

    this->matrix = new int*[this->source.length() + 1];
    for(int i = 0; i < this->source.length() + 1; i++) this->matrix[i] = new int[this->target.length() + 1];

    for(int i = 0; i < this->rows - 1; i++) this->matrix[i][0] = i;
    for(int j = 0; j < this->columns - 1; j++) this->matrix[0][j] = j;

    for(int i = 1; i < this->rows - 1; i++)
        for(int j = 1; j < this->columns - 1; j++)
            this->matrix[i][j] = -1;

    this->repaint();
}

void DPMatrix::setSource(QString source) {
    this->source = source;
    this->rows = source.length() + 2;
}

void DPMatrix::setTarget(QString target) {
    this->target = target;
    this->columns = target.length() + 2;
}

DPMatrix::~DPMatrix()
{
    for(int i = 0; i < this->rows - 1; i++)
        delete [] this->matrix[i];
    delete [] this->matrix;
}

