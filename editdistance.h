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

const char DEFAULT_MATCH_TEXT = 'm';
const char DEFAULT_DELETE_TEXT = 'd';
const char DEFAULT_INSERT_TEXT = 'i';
const char DEFAULT_REPLACE_TEXT = 's';

class EditDistance
{
public:
    EditDistance(std::string, std::string);
    virtual ~EditDistance();

    virtual void initialize();
    virtual void retrace(int row, int column);
    virtual void traceback(int row, int column);
    virtual bool validTraceback(int r1, int c1, int r2, int c2);
    virtual int calculate(int row, int column);
    virtual int optimal(int, int, int);

    void setCaseSensitive(bool);

    std::string getSource();
    std::string getTarget();

    int getRows();
    int getColumns();
    int getMaxCost();
    void setOperationCosts(int match, int sub, int ins, int del);
    void setOperationText(char match, char sub, char ins, char del);
    int getInvalidCost();
    int getCost(int, int);
    bool getTraceback(int, int);
    void setCost(int, int, int);
    void setTraceback(int, int, bool);
    void resetTraceback();
    void setOptimalMin();
    void setOptimalMax();

    std::string pseudoConversion();
    std::string pseudoSource();
    std::string pseudoTarget();

protected:
    bool valid(int, int);
    bool same(char, char);

    std::string pConversion;
    std::string pTarget;
    std::string pSource;

    char matchText;
    char insertText;
    char deleteText;
    char replaceText;

    int matchCost;
    int deleteCost;
    int insertCost;
    int replaceCost;
    int invalidCost;

private:
    std::string source;
    std::string target;

    bool caseSensitive;
    bool maxOptimal;

    int** cost;
    bool** inTraceback;
};

#endif // EditDistance_H
