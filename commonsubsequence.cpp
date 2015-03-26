#include "commonsubsequence.h"

CommonSubsequence::CommonSubsequence(QString source, QString target, QWidget* parent) : DPMatrix(source, target, parent)
{
    this->setup();
    this->reset();
}

void CommonSubsequence::setup()
{
    for(int i = 0; i < this->getRows() - 1; i++) this->set(i, 0, 0);
    for(int j = 0; j < this->getColumns() - 1; j++) this->set(0, j, 0);
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
    if(row == 0 && column == 0);
    else if(row == 0) this->traceback(0, column-1);
    else if(column == 0) this->traceback(row-1, 0);
    else {
        if(this->getSource().at(row-1).toLower() == this->getTarget().at(column-1).toLower())
        {
            this->rs[row-1] = (this->getSource().at(row-1));
            this->cs[column-1] = (this->getTarget().at(column-1));
            this->lcs.push_front(this->getSource().at(row-1));
            this->traceback(row-1, column-1);

        }
        else
        {
            int low = this->max(this->at(row, column-1),this->at(row-1, column));
            if(this->at(row, column-1) == low) this->traceback(row, column-1);
            else {
                this->traceback(row-1, column);
            }
        }
    }
    this->set(row, column, true);
}

int CommonSubsequence::calculate(int row, int column)
{
    if(this->at(row, column) >= 0);
    else if(this->getSource().at(row-1).toLower() == this->getTarget().at(column-1).toLower())
        this->set(row, column, this->calculate(row-1, column-1) + 1);
    else
        this->set(row, column, this->max(this->calculate(row-1, column), this->calculate(row, column-1)));
    return(this->at(row, column));
}

QString CommonSubsequence::getToolTipText(int row, int column, int value)
{
    QString text = QString::fromLatin1("<p><span style=\"font-size: 16pt; font-family: %1\">").arg(QFont("Courier New", 16).family());
    text += "<table>";
    text += "<tr><td>LCS: </td><td>" + lcs + "</td></tr>";
    text += "<tr><td>Length: </td><td>" + QString::number(value) + "</td></tr>";
    text += "<tr><td>From: </td><td><strong>" + this->getSource().left(row) + "</strong></td></tr>";
    text += "<tr><td></td><td>" + rs + "</td></tr>";
    text += "<tr><td></td><td>" + cs + "</td></tr>";
    text += "<tr><td>To: </td><td><strong>" + this->getTarget().left(column) + "</strong></td></tr>";
    text += "</table>";
    text += "</span></p>";
    this->reset();
    return text;
}

CommonSubsequence::~CommonSubsequence()
{

}

