#include "commonsubsequence.h"

CommonSubsequence::CommonSubsequence(std::string source, std::string target)
    : EditDistance(source, target)
{
    this->setOperationCosts(0, 0, 1, 1);
}

void CommonSubsequence::initialize()
{
    EditDistance::initialize();
}


void CommonSubsequence::traceback(int row, int column)
{

}

bool CommonSubsequence::validTraceback(int r1, int c1, int r2, int c2)
{
    EditDistance::validTraceback(r1, c1, r2, c2);
}

int CommonSubsequence::calculate(int row, int column)
{
    EditDistance::calculate(row, column);
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

