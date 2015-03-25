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

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QPaintEvent;
QT_END_NAMESPACE

const int DEFAULT_SQUARE_SIZE = 30;
const int DEFAULT_MAX_LENGTH = 50;

class DPMatrix : public QWidget
{
    Q_OBJECT
public:
    explicit DPMatrix(QString source, QString target, QWidget *parent = 0);
    ~DPMatrix();

    virtual void setup() = 0;
    virtual void traceback(int row, int column) = 0;
    virtual int calculate(int row, int column) = 0;

    virtual QString getToolTipText(int, int, int);

    int at(int row, int column);
    void set(int row, int column, int value);
    void set(int row, int column, bool value);

signals:

public slots:

protected:
    void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
    int maxLength();
    int getRows();
    int getColumns();
    QString getSource();
    QString getTarget();
    bool valid(int row, int column);
    int min(int, int);
    int max(int, int);

private:
    // User Customizable Options
    int squareSize;

    // Noncustomizable Options
    int rows;
    int columns;

    int matrix[DEFAULT_MAX_LENGTH][DEFAULT_MAX_LENGTH];
    bool highlight[DEFAULT_MAX_LENGTH][DEFAULT_MAX_LENGTH];
    QString source, target;
    void initialize(QString source, QString target);
    void delay(int millisecondsToWait);
};

#endif // DPMATRIX_H
