#include "displaygrid.h"

DisplayGrid::DisplayGrid(int rows, int columns, QWidget *parent) : QWidget(parent)
{
    this->rows = rows;
    this->columns = columns;
    this->cellWidth = DEFAULT_CELL_SIZE;
    this->cellHeight = DEFAULT_CELL_SIZE;
    this->values = new QString*[this->rows];
    this->cellColors = new QColor*[this->rows];
    this->highlights = new bool*[this->rows];
    for(int i = 0; i < this->rows; i++) {
        this->values[i] = new QString[this->columns];
        this->cellColors[i] = new QColor[this->columns];
        this->highlights[i] = new bool[this->columns];
    }
    this->setGeometry(0, 0, (this->columns+1)*this->cellWidth, (this->rows+1)*this->cellHeight);
    this->setMouseTracking(true);
    this->reset();
}

DisplayGrid::~DisplayGrid()
{
    for(int i = 0; i < this->rows; i++) {
        delete[] this->values[i];
        delete[] this->cellColors[i];
        delete[] this->highlights[i];
    }
    delete[] this->values;
    delete[] this->cellColors;
    delete[] this->highlights;
}

void DisplayGrid::setCellSize(int width, int height)
{
    this->cellWidth = width;
    this->cellHeight = height;
    this->setGeometry(0, 0, this->columns*this->cellWidth, this->rows*this->cellHeight);
}

void DisplayGrid::setCellColor(int row, int column, QColor c)
{
    this->cellColors[row][column] = c;
}

void DisplayGrid::highlightCell(int row, int column, bool b)
{
    if(this->isValidCell(row, column)) this->highlights[row][column] = b;
    else;
}

bool DisplayGrid::isCellHighlighted(int row, int column)
{
    if(this->isValidCell(row, column)) return this->highlights[row][column];
    else return false;
}

void DisplayGrid::setCellText(int row, int column, QString t)
{
    if(this->isValidCell(row, column)) this->values[row][column] = t;
    else this->values = NULL;
}

QString DisplayGrid::getCellText(int row, int column)
{
    if(this->isValidCell(row, column)) return this->values[row][column];
    else return INVALID_TOKEN;
}

int DisplayGrid::getRows()
{
    return this->rows;
}

int DisplayGrid::getColumns()
{
    return this->columns;
}


void DisplayGrid::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint position = mapFromGlobal(event->globalPos());
    int row = (position.y() / this->cellHeight) - 1;
    int column = (position.x() / this->cellWidth) - 1;

    if(row >= 0 && column >= 0 && row < this->rows - 1 && column < this->columns - 1) this->repaint();
}

void DisplayGrid::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QString text;
    QPoint pos;
    painter.fillRect(0, 0, this->columns*this->cellWidth, this->rows*this->cellHeight, QBrush(this->backgroundColor));

    painter.setPen(QPen(this->gridColor));
    for (int row = 0; row < rows; row++)
        for (int column = 0; column < columns; column++)
            painter.drawRect(column*this->cellWidth, row*this->cellHeight, this->cellWidth, this->cellHeight);

    this->penFont.setPixelSize(this->cellHeight*0.6);
    painter.setFont(this->penFont);
    QFontMetrics fontMetrics(painter.font());
    painter.setPen(QPen(this->penColor));
    for (int row = 0; row < this->rows; row++) {
        for (int column = 0; column < this->columns; column++) {
            text = this->getCellText(row, column);
            pos.setX(column*this->cellWidth);
            pos.setY(row*this->cellHeight);
            painter.fillRect(pos.x() + 1, pos.y() + 1, this->cellWidth - 1, this->cellHeight - 1, this->cellColors[row][column]);
            painter.setPen(QPen(this->penColor));
            painter.drawText(pos.x() + (this->cellWidth / 2) - fontMetrics.width(text)/2, pos.y() + fontMetrics.ascent() + 4, text);
        }
    }

    painter.setPen(QPen(this->highlightColor, 3));
    for (int row = 0; row < this->rows; row++)
        for (int column = 0; column < this->columns; column++)
            if(this->isCellHighlighted(row, column))
                painter.drawRect(column*this->cellWidth, row*this->cellHeight, this->cellWidth, this->cellHeight);
}

int DisplayGrid::getCellWidth()
{
    return this->cellWidth;
}

int DisplayGrid::getCellHeight()
{
    return this->cellHeight;
}

bool DisplayGrid::isValidCell(int row, int column)
{
    if(row >= 0 && row < this->rows && column >= 0 && column < this->columns) return true;
    else return false;
}

bool DisplayGrid::isEmpty(int row, int column)
{
    if(this->isValidCell(row, column))
        return this->values[row][column] == INVALID_TOKEN;
    else return true;
}

void DisplayGrid::reset()
{
    this->backgroundColor = QColor(Qt::white);
    this->gridColor = QColor(Qt::gray);
    this->penColor = QColor(Qt::black);
    this->highlightColor = QColor(Qt::blue);
    this->penFont = QFont("Courier", 12);

    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->columns; j++) {
            this->values[i][j] = INVALID_TOKEN;
            this->cellColors[i][j] = this->backgroundColor;
            this->highlights[i][j] = false;
        }
    }
}
