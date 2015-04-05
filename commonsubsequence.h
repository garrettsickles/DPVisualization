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

    virtual void initialize();
    virtual void traceback(int row, int column);
    virtual bool validTraceback(int r1, int c1, int r2, int c2);
    virtual int calculate(int row, int column);

private:
};

#endif // COMMONSUBSEQUENCE_H
