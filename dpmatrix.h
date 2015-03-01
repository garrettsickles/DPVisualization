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

    void setup(QString, QString);
    void initializeBaseCase();

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
};

#endif // DPMATRIX_H
