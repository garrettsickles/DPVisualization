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
#include <QCoreApplication>
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
    QString source;
    QString target;

    void setSource(QString);
    void setTarget(QString);

    int getCost(int,int);
    int min(int, int);
    void delay(int);
};

#endif // DPMATRIX_H
