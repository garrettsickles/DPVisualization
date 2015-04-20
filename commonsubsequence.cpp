#include "commonsubsequence.h"

CommonSubsequence::CommonSubsequence(std::string source, std::string target)
    : EditDistance(source, target)
{
    this->initialize();
}

void CommonSubsequence::initialize()
{
    this->setOperationCosts(1, 0, 0, 0);
    this->setOperationText('-', 'm', '-', '-');

    EditDistance::setCost(0, 0, 0);
    for(int i = 1; i < this->getRows(); i++) EditDistance::setCost(i, 0, 0);
    for(int j = 1; j < this->getColumns(); j++) EditDistance::setCost(0, j, 0);
    for(int i = 1; i < this->getRows(); i++)
        for(int j = 1; j < this->getColumns(); j++)
            EditDistance::setCost(i, j, this->invalidCost);

    EditDistance::resetTraceback();
}

void CommonSubsequence::retrace(int row, int column)
{
    int r = row;
    int c = column;
    row = 0;
    column = 0;
    this->pConversion.clear();
    this->pSource.clear();
    this->pTarget.clear();

    if(this->getTraceback(row, column)) {
        while(row != r || column != c) {
            if(this->getTraceback(row+1, column)) {
                this->pConversion.push_back(this->deleteText);
                this->pSource.push_back(this->getSource().at(row));
                this->pTarget.push_back('-');
                row += 1;
            } else if(this->getTraceback(row, column+1)) {
                this->pConversion.push_back(this->insertText);
                this->pSource.push_back('-');
                this->pTarget.push_back(this->getTarget().at(column));
                column += 1;
            } else if(this->getTraceback(row+1, column+1)) {
                this->getCost(row, column) == this->getCost(row+1, column+1) ? this->pConversion.push_back(this->matchText) : this->pConversion.push_back(this->replaceText);
                this->pSource.push_back(this->getSource().at(row));
                this->pTarget.push_back(this->getTarget().at(column));
                row += 1;
                column += 1;
            } else {
                this->pConversion.clear();
                this->pSource.clear();
                this->pTarget.clear();
                break;
            }
        }
    }
}

void CommonSubsequence::traceback(int row, int column)
{
    if(row == 0 && column == 0);
    else {
        int low = this->optimal(this->getCost(row-1, column-1), this->getCost(row, column-1), this->getCost(row-1, column));
        if(this->getCost(row-1, column-1) == low) {
            this->traceback(row-1, column-1);
            this->getCost(row, column) == this->getCost(row-1, column-1) ? this->pConversion.push_back(this->matchText) : this->pConversion.push_back(this->replaceText);
            this->pSource.push_back(this->getSource().at(row-1));
            this->pTarget.push_back(this->getTarget().at(column-1));
        }
        else if(this->getCost(row, column-1) == low) {
            this->traceback(row, column-1);
            this->pConversion.push_back(this->insertText);
            this->pSource.push_back('-');
            this->pTarget.push_back(this->getTarget().at(column-1));
        }

        else if(this->getCost(row-1, column) == low) {
            this->traceback(row-1, column);
            this->pConversion.push_back(this->deleteText);
            this->pSource.push_back(this->getSource().at(row-1));
            this->pTarget.push_back('-');
        }
    }
    this->setTraceback(row, column, true);
}

bool CommonSubsequence::validTraceback(int r1, int c1, int r2, int c2)
{
    if((r1-r2 == 1 && c1-c2 == 1) || (r1-r2 == 0 && c1-c2 == 1) ||(r1-r2 == 1 && c1-c2 == 0)) {
        int low = this->optimal(this->getCost(r1-1, c1-1), this->getCost(r1, c1-1), this->getCost(r1-1, c1));
        if(this->getCost(r1-1,c1) == this->getCost(r1,c1) && r1-1 == r2 && c1 == c2) return false;
        if(this->getCost(r1,c1-1) == this->getCost(r1,c1) && r1 == r2 && c1-1 == c2) return false;
        else return this->getCost(r2, c2) == low;
    }
    else return false;
}

/*
void CommonSubsequence::traceback(int row, int column)
{
    EditDistance::traceback(row, column);
}

bool CommonSubsequence::validTraceback(int r1, int c1, int r2, int c2)
{
    return EditDistance::validTraceback(r1, c1, r2, c2);
}
*/
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

