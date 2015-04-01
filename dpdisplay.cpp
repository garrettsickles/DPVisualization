#include "dpdisplay.h"

DPDisplay::DPDisplay(EditDistance* ed, QWidget* parent) : DisplayGrid(ed->getRows()+1, ed->getColumns()+1, parent)
{
    this->ed = ed;
    this->updateDisplay();
}


DPDisplay::~DPDisplay()
{
    if(this->ed != NULL) delete this->ed;
}

void DPDisplay::updateDisplay()
{
    QColor c;
    for(int i = 0; i < ed->getRows(); i++) {
        for(int j = 0; j < ed->getColumns(); j++) {
            this->highlight(i+1, j+1, this->ed->getTraceback(i, j));
            if(this->ed->getCost(i, j) == this->ed->getInvalidCost()) this->set(i+1, j+1, QString(" "));
            else {
                this->set(i+1, j+1, QString::number(this->ed->getCost(i, j)));
                c.setHsv(120.0*(1.0-((double)(this->ed->getCost(i, j)/((double)this->ed->getMaxCost())))), 255, 255, 125);
                if(this->ed->getTraceback(i, j)) c.setAlpha(255);
                this->setCellColor(i+1, j+1, c);
            }
        }
    }
    this->repaint();
}

EditDistance* DPDisplay::get()
{
    return this->ed;
}

void DPDisplay::setManualTraceback(bool b)
{
    this->manualTarceback = b;
}

void DPDisplay::setup()
{

}

void DPDisplay::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint position = mapFromGlobal(event->globalPos());
    int row = (position.y() / this->getCellHeight()) - 1;
    int column = (position.x() / this->getCellWidth()) - 1;

    this->ed->calculate(row, column);
    if(this->manualTarceback) {
        if(this->ed->validTracebackPair(this->previousRow, this->previousColumn, row, column))
            this->ed->setTraceback(row, column, true);
        else {
            this->ed->resetTraceback();
            this->ed->setTraceback(row, column, true);
        }
    } else {
        this->ed->resetTraceback();
        this->ed->traceback(row, column);
    }
    this->previousRow = row;
    this->previousColumn = column;
    this->updateDisplay();
}
