#ifndef COMMONSUBSEQUENCE_H
#define COMMONSUBSEQUENCE_H

#include <QString>
#include <iostream>
#include "editdistance.h"

class CommonSubsequence : public EditDistance
{
public:
    CommonSubsequence(std::string, std::string);
    ~CommonSubsequence();

    void initialize();
    void traceback(int row, int column);
    int calculate(int row, int column);

    QString getToolTipText(int, int);

protected:
    void autoTraceback(int row, int column);
    void manualTraceback(int row, int column);
private:
    QString rs;
    QString cs;
    QString lcs;

    void reset();
};

#endif // COMMONSUBSEQUENCE_H
