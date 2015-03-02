#ifndef DPMATRIX_H
#define DPMATRIX_H

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

class DPMatrix : public QWidget
{
    Q_OBJECT

public:
    DPMatrix(QWidget *parent = 0);
    ~DPMatrix();

    void setup(QString, QString);

signals:

public slots:

protected:
    void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
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

    std::vector<std::vector<std::vector<std::pair<int,int> > > > traceback;

    void setSource(QString);
    void setTarget(QString);

    int getCost(int,int);
    int min(int, int);
    void delay(int);
    void drawTraceback(int, int, QPainter *qp);
};

#endif // DPMATRIX_H
