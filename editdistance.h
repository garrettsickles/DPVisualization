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
#include <vector>
#include <iostream>
#include "mainwindow.h"

#define INIT_STRING "Elephants"

const int DELETE_COST = 1;
const int INSERT_COST = 1;
const int REPLACE_COST = 1;

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

    void setup(QString, QString);

signals:

public slots:

protected:
    void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

private:
    int squareSize;
    int maxLength;
    int rows;
    int columns;
    int **matrix;
    bool doTraceback;
    int tbr;
    int tbc;
    QString source;
    QString target;

    void setSource(QString);
    void setTarget(QString);

    int getCost(int,int);
    int min(int, int);
    void delay(int);
    void drawTraceback(int, int, QPainter *qp);
};

#endif // EditDistance_H
