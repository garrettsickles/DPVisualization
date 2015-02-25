#ifndef DPMATRIX_H
#define DPMATRIX_H

#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>
#include <QFont>
#include <QSize>
#include "mainwindow.h"

#define INIT_STRING "Elephants"

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

    void setSource(QString);
    void setTarget(QString);
    void initializeBaseCase();

signals:

public slots:

protected:
    void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

private:
    int squareSize;
    int rows;
    int columns;
    QString source;
    QString target;
};

#endif // DPMATRIX_H
