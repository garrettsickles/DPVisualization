#include "editdistance.h"
#include "ui_mainwindow.h"

EditDistance::EditDistance(QWidget *parent) : QWidget(parent)
{
    squareSize = 30;
    doTraceback = false;
    this->setup(INIT_STRING, INIT_STRING);
    setGeometry(0, 0, squareSize * columns, squareSize * rows);
    setMouseTracking(true);
}

void EditDistance::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint position = mapFromGlobal(event->globalPos());
    int row = (position.y() / squareSize) - 1;
    int column = (position.x() / squareSize) - 1;

    if(row >= 0 && column >= 0 && row < this->rows - 1 && column < this->columns - 1 && this->isEnabled()) {
        this->getCost(row, column);
        int cost = this->matrix[row][column];

        if(cost >= 0) {
            QString text = QString::fromLatin1("<p><span style=\"font-size: 16pt; font-family: %1\">").arg(QFont("Courier New", 16).family()) + "<table><tr><td>Cost: </td><td>"
                    + QString::number(cost) + "</td></tr><tr><td>From: </td><td><strong>" + this->source.left(row) + "</strong></td></tr><tr><td>To: </td><td><strong>" + this->target.left(column) + "</strong></td></tr></table></span></p>";
            QToolTip::showText(event->globalPos(), text, this);
            this->doTraceback = true;
            tbr = row;
            tbc = column;
            this->repaint();
        }
        else {
            this->doTraceback = false;
        }
    }
    else {
        this->doTraceback = false;
    }
}

void EditDistance::paintEvent(QPaintEvent *event)
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
                if(doTraceback) {
                    painter.setPen(QPen(Qt::blue, 3));
                    this->drawTraceback(tbr, tbc, &painter);
                }
                painter.setPen(QPen(Qt::black));
                painter.drawText(column*squareSize + (squareSize / 2) - fontMetrics.width(QString::number(this->matrix[row - 1][column - 1]))/2,
                        row*squareSize + 4 + fontMetrics.ascent(),
                        QString::number(this->matrix[row - 1][column - 1]));
            }
        }
    }
}

void EditDistance::setup(QString source, QString target) {
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
}

void EditDistance::drawTraceback(int row, int column, QPainter *qp) {
    if(row == 0 && column == 0);
    else {
        if(!this->isEnabled()) return; // Prevent recursion if the reset button has been hit
        if(row == 0) this->drawTraceback(0, column-1, qp);
        else if(column == 0) this->drawTraceback(row-1, 0, qp);
        else {
            int low = min(this->matrix[row-1][column-1],min(this->matrix[row][column-1],this->matrix[row-1][column]));
            if(this->matrix[row-1][column-1] == low) this->drawTraceback(row-1, column-1,qp);
            if(this->matrix[row][column-1] == low) this->drawTraceback(row, column-1,qp);
            if(this->matrix[row-1][column] == low) this->drawTraceback(row-1, column,qp);
        }
    }
    qp->drawRect((column+1)*squareSize, (row+1)*squareSize, squareSize, squareSize);
}

int EditDistance::getCost(int row, int column) {
    if(this->matrix[row][column] >= 0) return this->matrix[row][column];
    else {
        int del = getCost(row-1, column) + DELETE_COST;
        int ins = getCost(row, column-1) + INSERT_COST;
        int sub = getCost(row - 1, column - 1) + (source.at(row-1) != target.at(column-1))*REPLACE_COST;
        if(!this->isEnabled()) return -1; // Prevent recursion if the reset button has been hit
        else {
            this->matrix[row][column] = min(sub, min(del, ins));
            //this->delay(250);
            return(this->matrix[row][column]);
        }
    }
}


void EditDistance::setSource(QString source) {
    this->source = source;
    this->rows = source.length() + 2;
}

void EditDistance::setTarget(QString target) {
    this->target = target;
    this->columns = target.length() + 2;
}



int EditDistance::min(int a, int b) {
    return b < a ? b : a;
}

void EditDistance::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

EditDistance::~EditDistance()
{
    for(int i = 0; i < this->rows - 1; i++)
        delete [] this->matrix[i];
    delete [] this->matrix;
}

