#include "editdistance.h"

EditDistance::EditDistance(std::string source, std::string target)
{
    this->source = source;
    this->target = target;
    this->deleteCost = DEFAULT_DELETE_COST;
    this->insertCost = DEFAULT_INSERT_COST;
    this->replaceCost = DEFAULT_REPLACE_COST;
    this->matchCost = DEFAULT_MATCH_COST;
    this->invalidCost = this->getRows() + this->getColumns();
    this->cost = new int*[this->getRows()];
    this->inTraceback = new bool*[this->getRows()];
    for(int i = 0; i < this->getRows(); i++) {
        this->cost[i] = new int[this->getColumns()];
        this->inTraceback[i] = new bool[this->getColumns()];
    }

    this->initialize();
}

EditDistance::~EditDistance()
{
    for(int i = 0; i < this->getRows(); i++) {
        delete[] this->cost[i];
        delete[] this->inTraceback[i];
    }
    delete[] this->cost;
    delete[] this->inTraceback;
}

void EditDistance::setCaseSensitive(bool b)
{
    this->caseSensitive = b;
}

std::string EditDistance::getSource()
{
    return this->source;
}

std::string EditDistance::getTarget()
{
    return this->target;
}

int EditDistance::getRows()
{
    return this->source.length() + 1;
}

int EditDistance::getColumns()
{
    return this->target.length() + 1;
}

void EditDistance::initialize()
{
    for(int i = 0; i < this->getRows(); i++) this->cost[i][0] = i;
    for(int j = 0; j < this->getColumns(); j++) this->cost[0][j] = j;
    for(int i = 1; i < this->getRows(); i++)
        for(int j = 1; j < this->getColumns(); j++)
            this->cost[i][j] = this->invalidCost;

    this->resetTraceback();
}

void EditDistance::setCost(int row, int column, int cost)
{
    if(this->valid(row, column)) this->cost[row][column] = cost;
    else;
}

int EditDistance::getCost(int row, int column)
{
    if(this->valid(row, column)) return this->cost[row][column];
    else return this->invalidCost;
}

int EditDistance::getInvalidCost()
{
    return this->invalidCost;
}

int EditDistance::getMaxCost()
{
    return std::max(this->source.length(), this->target.length());
}

void EditDistance::setTraceback(int row, int column, bool b)
{
    if(this->valid(row, column)) this->inTraceback[row][column] = b;
    else;
}

bool EditDistance::getTraceback(int row, int column)
{
    if(this->valid(row, column)) return this->inTraceback[row][column];
    else return false;
}

void EditDistance::resetTraceback()
{
    for(int i = 0; i < this->getRows(); i++)
        for(int j = 0; j < this->getColumns(); j++)
            this->inTraceback[i][j] = false;
}

/*
if(manual) {
    this->max = this->at(row,column);
    if(((row == lr-1 && column == lc-1) || (row == lr && column == lc-1) || (row == lr-1 && lc == column))) {
        if(this->at(row, column) == this->min(this->at(lr-1, lc-1),this->min(this->at(lr, lc-1),this->at(lr-1, lc))) || (row == 0 && column == 0));
        else this->reset();
    }
}*/

void EditDistance::traceback(int row, int column)
{
    if(row == 0 && column == 0);
    else {
        int low = std::min(this->getCost(row-1, column-1),std::min(this->getCost(row, column-1),this->getCost(row-1, column)));
        if(this->getCost(row-1, column-1) == low) {
            //if(this->getCost(row, column) == this->getCost(row-1, column-1));
            this->traceback(row-1, column-1);
        }
        else if(this->getCost(row, column-1) == low) {
            this->traceback(row, column-1);
        }
        else if(this->getCost(row-1, column) == low) {
            this->traceback(row-1, column);
        }
    }
    this->setTraceback(row, column, true);
}

bool EditDistance::validTracebackPair(int r1, int c1, int r2, int c2)
{
    if((r1-r2 == 1 && c1-c2 == 1) || (r1-r2 == 0 && c1-c2 == 1) ||(r1-r2 == 1 && c1-c2 == 0)) {
        int low = std::min(this->getCost(r1-1, c1-1),std::min(this->getCost(r1, c1-1),this->getCost(r1-1, c1)));
        if(this->getCost(r1-1,c1) == this->getCost(r1,c1) && r1-1 == r2 && c1 == c2) return false;
        if(this->getCost(r1,c1-1) == this->getCost(r1,c1) && r1 == r2 && c1-1 == c2) return false;
        else return this->getCost(r2, c2) == low;
    }
    else return false;
}

int EditDistance::calculate(int row, int column) {
    if(this->getCost(row, column) != this->invalidCost);
    else {
        int del = calculate(row-1, column) + this->deleteCost;
        int ins = calculate(row, column-1) + this->insertCost;
        int sub = calculate(row - 1, column - 1) + !(this->same(this->source.at(row-1), this->target.at(column-1)))*this->replaceCost;
        this->setCost(row, column, std::min(sub, std::min(del, ins)));
    }
    return this->getCost(row, column);
}

bool EditDistance::same(char a, char b)
{
    if(this->caseSensitive) return a == b;
    else return tolower(a) == tolower(b);
}

bool EditDistance::valid(int row, int column)
{
    if(row >= 0 && row < this->getRows() && column >= 0 && column < this->getColumns()) return true;
    else return false;
}

/*
QString EditDistance::getToolTipText(int row, int column)
{
    QString text = QString::fromLatin1("<p><span style=\"font-size: 16pt; font-family: %1\">").arg(QFont("Courier New", 16).family());
    text += "<table>";
    text += "<tr><td>Cost: </td><td>" + QString::number(this->at(row, column)) + "</td></tr>";
    text += "<tr><td>From: </td><td><strong>" + rs + "</strong></td></tr>";
    text += "<tr><td></td><td>" + this->con + "</td></tr>";
    text += "<tr><td>To: </td><td><strong>" + cs + "</strong></td></tr>";
    text += "</table>";
    text += "</span></p>";
    return text;
}
*/
