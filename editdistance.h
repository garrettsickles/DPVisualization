#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

const int DEFAULT_MATCH_COST = 0;
const int DEFAULT_DELETE_COST = 1;
const int DEFAULT_INSERT_COST = 1;
const int DEFAULT_REPLACE_COST = 1;

class EditDistance
{
public:
    EditDistance(std::string, std::string);
    ~EditDistance();

    virtual void initialize();
    virtual void traceback(int row, int column);
    virtual int calculate(int row, int column);
    //virtual QString getToolTipText(int, int);

    void setCaseSensitive(bool);

    std::string getSource();
    std::string getTarget();

    int getRows();
    int getColumns();
    int getMaxCost();
    int getInvalidCost();
    int getCost(int, int);
    bool getTraceback(int, int);

protected:
    //virtual void manualTraceback(int row, int column);
    //virtual void autoTraceback(int row, int column);

    void setCost(int, int, int);
    void setTraceback(int, int, bool);
    bool valid(int, int);
    bool same(char, char);

private:
    double matchCost;
    double deleteCost;
    double insertCost;
    double replaceCost;

    std::string source;
    std::string target;
    std::string conversion;
    std::string pTarget;
    std::string pSource;

    bool caseSensitive;
    int invalidCost;

    int** cost;
    bool** inTraceback;
};

#endif // EditDistance_H
