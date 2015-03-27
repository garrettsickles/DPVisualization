#include "editdistance.h"
#include "ui_mainwindow.h"

EditDistance::EditDistance(QString source, QString target, QWidget *parent) : DPMatrix(source, target, parent)
{
    this->setup();
    this->reset();
}

void EditDistance::setup()
{
    for(int i = 0; i < this->getRows() - 1; i++) this->set(i, 0, i);
    for(int j = 0; j < this->getColumns() - 1; j++) this->set(0, j, j);
}

void EditDistance::reset()
{
    this->con.clear();
    this->rs.clear();
    this->cs.clear();

}

void EditDistance::traceback(int row, int column) {
    if(row == 0 && column == 0);
    else {
        if(row == 0) {
            this->con.push_front("i");
            this->cs.push_front(this->getTarget().at(column-1));
            this->rs.push_front("-");
            this->traceback(0, column-1);
        }
        else if(column == 0) {
            this->con.push_front("d");
            this->rs.push_front(this->getSource().at(row-1));
            this->cs.push_front("-");
            this->traceback(row-1, 0);
        }
        else {
            int low = this->min(this->at(row-1, column-1),this->min(this->at(row, column-1),this->at(row-1, column)));
            if(this->at(row-1, column-1) == low) {
                if(this->at(row, column) == this->at(row-1, column-1)) this->con.push_front("m");
                else this->con.push_front("s");
                this->cs.push_front(this->getTarget().at(column-1));
                this->rs.push_front(this->getSource().at(row-1));
                this->traceback(row-1, column-1);
            }
            else if(this->at(row, column-1) == low) {
                this->con.push_front("i");
                this->cs.push_front(this->getTarget().at(column-1));
                this->rs.push_front("-");
                this->traceback(row, column-1);
            }
            else if(this->at(row-1, column) == low) {
                this->con.push_front("d");
                this->rs.push_front(this->getSource().at(row-1));
                this->cs.push_front("-");
                this->traceback(row-1, column);
            }
        }
    }
    this->set(row, column, true);
}

int EditDistance::calculate(int row, int column) {
    if(this->at(row, column) >= 0);
    else {
        int del = calculate(row-1, column) + DELETE_COST;
        int ins = calculate(row, column-1) + INSERT_COST;
        int sub = calculate(row - 1, column - 1) + !(this->same(this->getSource().at(row-1), this->getTarget().at(column-1)))*REPLACE_COST;
        this->set(row, column, this->min(sub, min(del, ins)));
    }
     return this->at(row, column);
}

QString EditDistance::getToolTipText(int row, int column, int value)
{
    QString text = QString::fromLatin1("<p><span style=\"font-size: 16pt; font-family: %1\">").arg(QFont("Courier New", 16).family());
    text += "<table>";
    text += "<tr><td>Cost: </td><td>" + QString::number(value) + "</td></tr>";
    text += "<tr><td>From: </td><td><strong>" + rs + "</strong></td></tr>";
    text += "<tr><td></td><td>" + this->con + "</td></tr>";
    text += "<tr><td>To: </td><td><strong>" + cs + "</strong></td></tr>";
    text += "</table>";
    text += "</span></p>";
    this->reset();
    return text;
}

EditDistance::~EditDistance()
{

}

