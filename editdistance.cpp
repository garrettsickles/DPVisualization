#include "editdistance.h"
#include "ui_mainwindow.h"

EditDistance::EditDistance(QString s, QString t, QWidget *parent) : DPMatrix(s, t, parent)
{
    this->setup();
}

void EditDistance::setup()
{
    for(int i = 0; i < this->getRows() - 1; i++) this->set(i, 0, i);
    for(int j = 0; j < this->getColumns() - 1; j++) this->set(0, j, j);
}

void EditDistance::traceback(int row, int column) {
    if(row == 0 && column == 0);
    else {
        if(row == 0) this->traceback(0, column-1);
        else if(column == 0) this->traceback(row-1, 0);
        else {
            int low = this->min(this->at(row-1, column-1),this->min(this->at(row, column-1),this->at(row-1, column)));
            if(this->at(row-1, column-1) == low) this->traceback(row-1, column-1);
            else if(this->at(row, column-1) == low) this->traceback(row, column-1);
            else if(this->at(row-1, column) == low) this->traceback(row-1, column);
        }
    }
    this->set(row, column, true);
}

int EditDistance::calculate(int row, int column) {
    if(this->at(row, column) >= 0);
    else {
        int del = calculate(row-1, column) + DELETE_COST;
        int ins = calculate(row, column-1) + INSERT_COST;
        int sub = calculate(row - 1, column - 1) + (this->getSource().at(row-1).toLower() != this->getTarget().at(column-1).toLower())*REPLACE_COST;
        this->set(row, column, this->min(sub, min(del, ins)));
    }
     return this->at(row, column);
}

EditDistance::~EditDistance()
{

}

