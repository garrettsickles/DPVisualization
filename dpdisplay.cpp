#include "dpdisplay.h"

DPDisplay::DPDisplay(EditDistance* ed, QWidget* parent) : DisplayGrid(ed->getRows()+1, ed->getColumns()+1, parent)
{
    this->ed = ed;
    this->updateDisplay();
}


DPDisplay::~DPDisplay()
{
    if(this->ed != NULL) delete this->ed;
}

QString DPDisplay::getToolTipText(int row, int column)
{
    QString text = QString::fromLatin1("<p><span style=\"font-size: 36pt; font-family: %1\">").arg(QFont("Courier New", 36).family());
    text += "<table>";
    text += "<tr><td>Cost: </td><td>" + QString::number(this->ed->getCost(row, column)) + "</td></tr>";
    text += "<tr><td>From: </td><td><strong>" + QString::fromStdString(this->ed->pseudoSource()) + "</strong></td></tr>";
    text += "<tr><td></td><td>" + QString::fromStdString(this->ed->pseudoConversion()) + "</td></tr>";
    text += "<tr><td>To: </td><td><strong>" + QString::fromStdString(this->ed->pseudoTarget()) + "</strong></td></tr>";
    text += "</table>";
    text += "</span></p>";
    return text;
}

void DPDisplay::updateDisplay()
{
    QColor c;
    for(int i = 0; i < ed->getRows(); i++) {
        for(int j = 0; j < ed->getColumns(); j++) {
            this->highlight(i+1, j+1, this->ed->getTraceback(i, j));
            if(this->ed->getCost(i, j) == this->ed->getInvalidCost()) this->set(i+1, j+1, QString(" "));
            else {
                this->set(i+1, j+1, QString::number(this->ed->getCost(i, j)));
                c.setHsv(120.0*(1.0-((double)(this->ed->getCost(i, j)/((double)this->ed->getMaxCost())))), 255, 255, 125);
                if(this->ed->getTraceback(i, j)) c.setAlpha(255);
                this->setCellColor(i+1, j+1, c);
            }
        }
    }
    this->repaint();
}

void DPDisplay::setManualTraceback(bool b)
{
    this->manualTarceback = b;
}

EditDistance* DPDisplay::get()
{
    return this->ed;
}

void DPDisplay::mouseReleaseEvent(QMouseEvent* event)
{
    QPoint position = mapFromGlobal(event->globalPos());
    int row = (position.y() / this->getCellHeight()) - 1;
    int column = (position.x() / this->getCellWidth()) - 1;

    this->ed->calculate(row, column);
    if(this->manualTarceback) {
        if(this->ed->validTraceback(this->previousRow, this->previousColumn, row, column)) {
            this->ed->setTraceback(row, column, true);
        }
        else {
            this->ed->resetTraceback();
            this->ed->setTraceback(row, column, true);
        }
    } else  {
        this->ed->resetTraceback();
        this->ed->traceback(row, column);
    }
    this->previousRow = row;
    this->previousColumn = column;
    this->updateDisplay();
    if(this->ed->getTraceback(row, column)) {
        QMessageBox msg;
        msg.setText(this->getToolTipText(row, column));
        msg.setButtonText(1, "Continue");
        msg.exec();
    }
}
