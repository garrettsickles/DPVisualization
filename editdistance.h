#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include <QWidget>
#include <QString>
#include <iostream>
#include "dpmatrix.h"
#include "mainwindow.h"

const int DELETE_COST = 1;
const int INSERT_COST = 1;
const int REPLACE_COST = 1;

class EditDistance : public DPMatrix
{
public:
    EditDistance(QString, QString, QWidget* parent);
    ~EditDistance();

    void setup();
    void traceback(int row, int column);
    int calculate(int row, int column);
private:

};

#endif // EditDistance_H
