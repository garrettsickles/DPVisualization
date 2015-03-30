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
            if(this->ed->getCost(i, j) == this->ed->getInvalidCost()) this->set(i+1, j+1, QString(" "));
            else {
                this->set(i+1, j+1, QString::number(this->ed->getCost(i, j)));
                c.setHsv(120.0 * (1-((double)this->ed->getCost(i, j))/(((double)this->ed->getMaxCost()))), 255, 255, 255);
                this->setCellColor(i+1, j+1, c);
            }
        }
    }
}

EditDistance* DPDisplay::get()
{
    return this->ed;
}

void DPDisplay::setup()
{

}

void DPDisplay::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint position = mapFromGlobal(event->globalPos());
    int row = (position.y() / this->getCellHeight()) - 1;
    int column = (position.x() / this->getCellWidth()) - 1;


}
