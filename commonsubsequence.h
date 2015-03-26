#ifndef COMMONSUBSEQUENCE_H
#define COMMONSUBSEQUENCE_H

#include <QWidget>
#include <QString>
#include <iostream>
#include "dpmatrix.h"
#include "mainwindow.h"

class CommonSubsequence : public DPMatrix
{
public:
    CommonSubsequence(QString, QString, QWidget* parent);
    ~CommonSubsequence();

    void setup();
    void traceback(int row, int column);
    int calculate(int row, int column);

    QString getToolTipText(int, int, int);
private:
    QString rs;
    QString cs;
    QString lcs;

    void reset();
};

#endif // COMMONSUBSEQUENCE_H
