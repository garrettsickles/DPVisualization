#include "commonsubsequence.h"

CommonSubsequence::CommonSubsequence(std::string source, std::string target)
    : EditDistance(source, target)
{
    this->initialize();
}

void CommonSubsequence::initialize()
{
    this->setOperationCosts(1, 0, 0, 0, -1);
    this->setOperationText('-', 'm', '-', '-');

    EditDistance::setCost(0, 0, 0);
    for(int i = 1; i < this->getRows(); i++) EditDistance::setCost(i, 0, 0);
    for(int j = 1; j < this->getColumns(); j++) EditDistance::setCost(0, j, 0);
    for(int i = 1; i < this->getRows(); i++)
        for(int j = 1; j < this->getColumns(); j++)
            EditDistance::setCost(i, j, this->invalidCost);

    EditDistance::resetTraceback();
}


void CommonSubsequence::traceback(int row, int column)
{
    EditDistance::traceback(row, column);
}

bool CommonSubsequence::validTraceback(int r1, int c1, int r2, int c2)
{
    return EditDistance::validTraceback(r1, c1, r2, c2);
}

int CommonSubsequence::calculate(int row, int column)
{
    if(this->getCost(row, column) != this->invalidCost);
    else {
        int del = calculate(row-1, column) + this->deleteCost;
        int ins = calculate(row, column-1) + this->insertCost;
        int sub = calculate(row - 1, column - 1) + (this->same(this->getSource().at(row-1), this->getTarget().at(column-1)))*this->matchCost;
        this->setCost(row, column, this->optimal(sub, del, ins));
    }
    return this->getCost(row, column);
}


int CommonSubsequence::optimal(int a, int b, int c)
{
    return std::max(a, std::max(b, c));
}

int CommonSubsequence::getMaxCost()
{
    return std::min(this->getSource().length(), this->getTarget().length());
}

CommonSubsequence::~CommonSubsequence()
{

}

