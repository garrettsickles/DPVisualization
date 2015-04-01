#ifndef DISPLAYGRID_H
#define DISPLAYGRID_H

#include <QWidget>
#include <QString>
#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <QPoint>
#include <QMessageBox>
#include <QFont>
#include <QSize>
#include <QTime>
#include <QToolTip>
#include <QCoreApplication>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QPaintEvent;
QT_END_NAMESPACE

const int DEFAULT_CELL_SIZE = 30;
const QString INVALID_TOKEN = QString(" ");

class DisplayGrid : public QWidget
{
    Q_OBJECT
public:
    DisplayGrid(int, int, QWidget *parent);
    ~DisplayGrid();

    void setCellSize(int, int);
    void setInvalidToken(QString);

    void highlight(int, int, bool);
    bool isHighlighted(int, int);

    void set(int, int, QString);
    QString get(int, int);

    void setCellColor(int, int, QColor);

    int getRows();
    int getColumns();

protected:
    void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

    int getCellWidth();
    int getCellHeight();
    void reset();

    bool isValidCell(int, int);
    bool isEmpty(int, int);

private:

    int rows;
    int columns;

    int cellWidth;
    int cellHeight;

    QString** values;
    QColor** cellColors;
    bool** highlights;

    QString invalidToken;

    QColor backgroundColor;
    QColor gridColor;
    QColor penColor;
    QColor highlightColor;

    QFont penFont;
signals:

public slots:
};

#endif // DISPLAYGRID_H
