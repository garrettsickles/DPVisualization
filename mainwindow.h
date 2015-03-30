#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QInputDialog>
#include <QWidget>
#include <QMainWindow>
#include "editdistance.h"
#include "commonsubsequence.h"
#include "displaygrid.h"
#include "dpdisplay.h"

#define INIT_SOURCE "Elephant"
#define INIT_TARGET "Anaconda"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DPDisplay *dm;

    QString source;
    QString target;

    void initialize();
    void clear();

private slots:
    void update();
    void transpose();
    void reset();
    void zoom();
};

#endif // MAINWINDOW_H
