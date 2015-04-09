#include "commonsubsequence.h"

CommonSubsequence::CommonSubsequence(std::string source, std::string target)
    : EditDistance(source, target)
{
    this->initialize();
}

void CommonSubsequence::initialize()
{
    this->deleteCost = 0;
    this->insertCost = 0;
    this->matchCost = 1;
    this->invalidCost = -1;

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

/*
QString CommonSubsequence::getToolTipText(int row, int column)
{
    QString text = QString::fromLatin1("<p><span style=\"font-size: 16pt; font-family: %1\">").arg(QFont("Courier New", 16).family());
    text += "<table>";
    text += "<tr><td>LCS: </td><td>" + lcs + "</td></tr>";
    text += "<tr><td>Length: </td><td>" + QString::number(this->getCost(row, column)) + "</td></tr>";
    text += "<tr><td>From: </td><td><strong>" + QString::fromStdString(this->getSource().substr(0, row)) + "</strong></td></tr>";
    text += "<tr><td></td><td>" + rs + "</td></tr>";
    text += "<tr><td></td><td>" + cs + "</td></tr>";
    text += "<tr><td>To: </td><td><strong>" + QString::fromStdString(this->getTarget().substr(0, column)) + "</strong></td></tr>";
    text += "</table>";
    text += "</span></p>";
    this->reset();
    return text;
}
*/
CommonSubsequence::~CommonSubsequence()
{

}

