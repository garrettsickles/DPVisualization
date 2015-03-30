#include "commonsubsequence.h"

CommonSubsequence::CommonSubsequence(std::string source, std::string target)
    : EditDistance(source, target)
{
    this->initialize();
    this->reset();
}

void CommonSubsequence::initialize()
{
    for(int i = 0; i < this->getRows() - 1; i++) this->setCost(i, 0, 0);
    for(int j = 0; j < this->getColumns() - 1; j++) this->setCost(0, j, 0);
}

void CommonSubsequence::reset()
{
    lcs.clear();
    rs.clear();
    cs.clear();
    for(int i = 0; i < this->getSource().length(); i++) rs.push_back("-");
    for(int i = 0; i < this->getTarget().length(); i++) cs.push_back("-");
}

void CommonSubsequence::traceback(int row, int column)
{

}

void CommonSubsequence::manualTraceback(int row, int column)
{

}

void CommonSubsequence::autoTraceback(int row, int column)
{
    if(row == 0 && column == 0);
    else if(row == 0) this->traceback(0, column-1);
    else if(column == 0) this->traceback(row-1, 0);
    else {
        if(this->same(this->getSource().at(row-1), this->getTarget().at(column-1)))
        {
            this->rs[row-1] = (this->getSource().at(row-1));
            this->cs[column-1] = (this->getTarget().at(column-1));
            this->lcs.push_front(this->getSource().at(row-1));
            this->traceback(row-1, column-1);

        }
        else
        {
            int low = std::max(this->getCost(row, column-1),this->getCost(row-1, column));
            if(this->getCost(row, column-1) == low) this->traceback(row, column-1);
            else {
                this->traceback(row-1, column);
            }
        }
    }
    this->setTraceback(row, column, true);
}

int CommonSubsequence::calculate(int row, int column)
{
    if(this->getCost(row, column) >= 0);
    else if(this->same(this->getSource().at(row-1), this->getTarget().at(column-1)))
        this->setCost(row, column, this->calculate(row-1, column-1) + 1);
    else
        this->setCost(row, column, std::max(this->calculate(row-1, column), this->calculate(row, column-1)));
    return(this->getCost(row, column));
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

