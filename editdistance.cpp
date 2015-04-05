#include "editdistance.h"

EditDistance::EditDistance(std::string source, std::string target)
{
    this->source = source;
    this->target = target;
    this->deleteCost = DEFAULT_DELETE_COST;
    this->insertCost = DEFAULT_INSERT_COST;
    this->replaceCost = DEFAULT_REPLACE_COST;
    this->matchCost = DEFAULT_MATCH_COST;
    this->caseSensitive = false;
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
    this->cost[0][0] = 0;
    for(int i = 1; i < this->getRows(); i++) this->cost[i][0] = this->cost[i-1][0] + this->deleteCost;
    for(int j = 1; j < this->getColumns(); j++) this->cost[0][j] = this->cost[0][j-1] + this->insertCost;
    for(int i = 1; i < this->getRows(); i++)
        for(int j = 1; j < this->getColumns(); j++)
            this->cost[i][j] = this->invalidCost;

    this->resetTraceback();
}

void EditDistance::setCost(int row, int column, int cost)
{
    if(this->valid(row, column)) this->cost[row][column] = cost;
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

void EditDistance::setOperationCosts(int match, int sub, int ins, int del)
{
    this->matchCost = match;
    this->replaceCost = sub;
    this->insertCost = ins;
    this->deleteCost = del;
}

void EditDistance::setTraceback(int row, int column, bool b)
{
    if(this->valid(row, column)) this->inTraceback[row][column] = b;
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

    this->pConversion.clear();
    this->pSource.clear();
    this->pTarget.clear();
}

void EditDistance::traceback(int row, int column)
{
    if(row == 0 && column == 0);
    else {
        int low = std::min(this->getCost(row-1, column-1),std::min(this->getCost(row, column-1),this->getCost(row-1, column)));
        if(this->getCost(row-1, column-1) == low) {
            this->traceback(row-1, column-1);
            this->getCost(row, column) == this->getCost(row-1, column-1) ? this->pConversion.push_back('m') : this->pConversion.push_back('s');
            this->pSource.push_back(this->getSource().at(row-1));
            this->pTarget.push_back(this->getTarget().at(column-1));
        }
        else if(this->getCost(row, column-1) == low) {
            this->traceback(row, column-1);
            this->pConversion.push_back('i');
            this->pSource.push_back('-');
            this->pTarget.push_back(this->getTarget().at(column-1));
        }

        else if(this->getCost(row-1, column) == low) {
            this->traceback(row-1, column);
            this->pConversion.push_back('d');
            this->pSource.push_back(this->getSource().at(row-1));
            this->pTarget.push_back('-');
        }
    }
    this->setTraceback(row, column, true);
}

bool EditDistance::validTraceback(int r1, int c1, int r2, int c2)
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
    return(row >= 0 && row < this->getRows() && column >= 0 && column < this->getColumns());
}

std::string EditDistance::pseudoConversion()
{
    return this->pConversion;
}

std::string EditDistance::pseudoSource()
{
    return this->pSource;
}

std::string EditDistance::pseudoTarget()
{
    return this->pTarget;
}
