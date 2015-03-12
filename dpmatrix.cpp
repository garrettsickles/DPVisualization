#include "dpmatrix.h"

DPMatrix::DPMatrix(QString source, QString target, QWidget *parent) : QWidget(parent)
{
    this->initialize(source, target);
}

DPMatrix::~DPMatrix()
{

}

void DPMatrix::initialize(QString source, QString target)
{
    this->squareSize = DEFAULT_SQUARE_SIZE;
    this->setMouseTracking(true);
    this->source = source;
    this->rows = source.length() + 2;
    this->target = target;
    this->columns = target.length() + 2;
    for(int i = 0; i < this->rows - 1; i++) {
        for(int j = 0; j < this->columns - 1; j++) {
            this->matrix[i][j] = -1;
            this->highlight[i][j] = false;
        }
    }
    this->setGeometry(0, 0, this->squareSize * this->columns, this->squareSize * this->rows);
}

int DPMatrix::maxLength()
{
    return (this->source.length() > this->target.length()) ? this->source.length() : this->target.length();
}

int DPMatrix::getRows()
{
    return this->rows;
}

int DPMatrix::getColumns()
{
    return this->columns;
}

bool DPMatrix::valid(int row, int column)
{
    if(row < 0 || row > this->rows || column < 0 || column > this->columns) return false;
    else return true;
}

int DPMatrix::at(int row, int column)
{
    if(valid(row, column)) return this->matrix[row][column];
}

void DPMatrix::set(int row, int column, int value)
{
    if(valid(row, column))this->matrix[row][column] = value;
}

void DPMatrix::set(int row, int column, bool value)
{
    if(valid(row, column))this->highlight[row][column] = value;
}

QString DPMatrix::getSource()
{
    return this->source;
}

QString DPMatrix::getTarget()
{
    return this->target;
}

QString DPMatrix::getToolTipText(int row, int column, int value)
{
    QString text = QString::fromLatin1("<p><span style=\"font-size: 16pt; font-family: %1\">").arg(QFont("Courier New", 16).family());
    text += "<table>";
    text += "<tr><td>Cost: </td><td>" + QString::number(value) + "</td></tr>";
    text += "<tr><td>From: </td><td><strong>" + this->source.left(row) + "</strong></td></tr>";
    text += "<tr><td>To: </td><td><strong>" + this->target.left(column) + "</strong></td></tr>";
    text += "</table>";
    text += "</span></p>";
    return text;
}

void DPMatrix::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint position = mapFromGlobal(event->globalPos());
    int row = (position.y() / this->squareSize) - 1;
    int column = (position.x() / this->squareSize) - 1;

    if(row >= 0 && column >= 0 && row < this->rows - 1 && column < this->columns - 1) {
        int value = this->calculate(row, column);
        for (int r = 0; r < this->rows-1; ++r)
            for (int c = 0; c < this->columns-1; ++c)
                this->highlight[r][c] = false;
        this->traceback(row, column);
        QToolTip::showText(event->globalPos(), getToolTipText(row, column, value), this);
        this->repaint();
    }
}

void DPMatrix::paintEvent(QPaintEvent *event)
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
                degree.setHsv((120.0 * (1 - ((float)(this->matrix[row - 1][column - 1])) / (float)(this->maxLength()))), 255, 255, 255);
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
            if(this->highlight[row][column])
                painter.drawRect((column+1)*squareSize, (row+1)*squareSize, squareSize, squareSize);
}

int DPMatrix::min(int a, int b)
{
    return(b < a ? b : a);
}

int DPMatrix::max(int a, int b)
{
    return(b > a ? b : a);
}

void DPMatrix::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
