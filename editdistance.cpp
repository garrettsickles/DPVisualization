#include "editdistance.h"
#include "ui_mainwindow.h"

EditDistance::EditDistance(QWidget *parent) : QWidget(parent)
{
    this->initialize(INIT_SOURCE, INIT_TARGET);
}

EditDistance::EditDistance(QString s, QString t, QWidget *parent) : QWidget(parent)
{
    this->initialize(s, t);
}

void EditDistance::initialize(QString source, QString target)
{
    squareSize = INIT_SQUARESIZE;
    setGeometry(0, 0, squareSize * columns, squareSize * rows);
    setMouseTracking(true);
    this->source = source;
    this->rows = source.length() + 2;
    this->target = target;
    this->columns = target.length() + 2;
    this->maxLength = (source.length() > target.length()) ? source.length() : target.length();
    for(int i = 0; i < this->rows - 1; i++) {
        for(int j = 0; j < this->columns - 1; j++) {
            this->matrix[i][j] = ((i == 0) ? j : ((j == 0) ? i : -1));
            this->traceback[i][j] = false;
        }
    }
}

void EditDistance::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint position = mapFromGlobal(event->globalPos());
    int row = (position.y() / squareSize) - 1;
    int column = (position.x() / squareSize) - 1;

    if(row >= 0 && column >= 0 && row < this->rows - 1 && column < this->columns - 1) {
        int cost = this->getCost(row, column);
        QString text = QString::fromLatin1("<p><span style=\"font-size: 16pt; font-family: %1\">").arg(QFont("Courier New", 16).family());
        text += "<table>";
        text += "<tr><td>Cost: </td><td>" + QString::number(cost) + "</td></tr>";
        text += "<tr><td>From: </td><td><strong>" + this->source.left(row) + "</strong></td></tr>";
        text += "<tr><td>To: </td><td><strong>" + this->target.left(column) + "</strong></td></tr>";
        text += "</table>";
        text += "</span></p>";
        QToolTip::showText(event->globalPos(), text, this);
        for (int r = 0; r < this->rows-1; ++r)
            for (int c = 0; c < this->columns-1; ++c)
                this->traceback[r][c] = false;
        this->calcTraceback(row, column);
        this->repaint();
    }
}

void EditDistance::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor degree;
    painter.fillRect(0, 0, columns * squareSize , rows * squareSize, QBrush(Qt::white));

    painter.setPen(QPen(Qt::gray));
    for (int row = 0; row < rows; row++)
        for (int column = 0; column < columns; column++)
            painter.drawRect(column*squareSize, row*squareSize, squareSize, squareSize);

    painter.setFont(QFont("Courier", 12));
    QFontMetrics fontMetrics(painter.font());
    painter.setPen(QPen(Qt::black));

    for (int row = 2; row < this->rows; row++) {
        painter.drawText((squareSize / 2) - fontMetrics.width(source.at(row-2))/2,
                         row*squareSize + 4 + fontMetrics.ascent(),
                         QString(source.at(row-2)));
    }

    for (int column = 2; column < this->columns; column++) {
        painter.drawText(column*squareSize + (squareSize / 2) - fontMetrics.width(target.at(column-2))/2,
                         4 + fontMetrics.ascent(),
                         QString(target.at(column-2)));
    }

    for (int row = 1; row < this->rows; ++row) {
        for (int column = 1; column < this->columns; ++column) {
            if(this->matrix[row - 1][column - 1] >= 0) {
                //painter.setClipRect(column*squareSize, row*squareSize, squareSize, squareSize);
                degree.setHsv((120.0 * (1 - ((float)(this->matrix[row - 1][column - 1])) / (float)(this->maxLength))), 255, 255, 255);
                painter.fillRect(column*squareSize + 1, row*squareSize + 1, squareSize - 1, squareSize - 1, degree);
                painter.setPen(QPen(Qt::black));
                painter.drawText(column*squareSize + (squareSize / 2) - fontMetrics.width(QString::number(this->matrix[row - 1][column - 1]))/2,
                        row*squareSize + 4 + fontMetrics.ascent(),
                        QString::number(this->matrix[row - 1][column - 1]));
            }
        }
    }
    painter.setPen(QPen(Qt::blue, 3));
    for (int row = 0; row < this->rows-1; ++row)
        for (int column = 0; column < this->columns-1; ++column)
            if(this->traceback[row][column])
                painter.drawRect((column+1)*squareSize, (row+1)*squareSize, squareSize, squareSize);
}

void EditDistance::calcTraceback(int row, int column) {
    if(row == 0 && column == 0);
    else {
        if(row == 0) this->calcTraceback(0, column-1);
        else if(column == 0) this->calcTraceback(row-1, 0);
        else {
            int low = min(this->matrix[row-1][column-1],min(this->matrix[row][column-1],this->matrix[row-1][column]));
            if(this->matrix[row-1][column-1] == low) this->calcTraceback(row-1, column-1);
            if(this->matrix[row][column-1] == low) this->calcTraceback(row, column-1);
            if(this->matrix[row-1][column] == low) this->calcTraceback(row-1, column);
        }
    }
    this->traceback[row][column] = true;
}

int EditDistance::getCost(int row, int column) {
    if(this->matrix[row][column] >= 0) return this->matrix[row][column];
    else {
        int del = getCost(row-1, column) + DELETE_COST;
        int ins = getCost(row, column-1) + INSERT_COST;
        int sub = getCost(row - 1, column - 1) + (source.at(row-1) != target.at(column-1))*REPLACE_COST;
        this->matrix[row][column] = this->min(sub, min(del, ins));
        return(this->matrix[row][column]);
    }
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

}

