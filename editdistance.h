#ifndef EDITDISTANCE_H
#define EDITDISTANCE_H

#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QPoint>
#include <QFont>
#include <QSize>
#include <QTime>
#include <QToolTip>
#include <QCoreApplication>
#include <iostream>
#include "mainwindow.h"

const int DELETE_COST = 1;
const int INSERT_COST = 1;
const int REPLACE_COST = 1;

const int INIT_SQUARESIZE = 30;
const int MAX_LENGTH = 50;

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QPaintEvent;
QT_END_NAMESPACE

class EditDistance : public QWidget
{
    Q_OBJECT

public:
    EditDistance(QWidget *parent = 0);
    EditDistance(QString, QString, QWidget *parent = 0);
    ~EditDistance();

private:
    int squareSize;
    int maxLength;
    int rows;
    int columns;
    int matrix[MAX_LENGTH][MAX_LENGTH];
    bool traceback[MAX_LENGTH][MAX_LENGTH];
    QString source;
    QString target;

    void initialize(QString, QString);
    void setSource(QString);
    void setTarget(QString);

    int getCost(int,int);
    void calcTraceback(int,int);

    int min(int, int);
    void delay(int);

protected:
    void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
};

#endif // EditDistance_H
