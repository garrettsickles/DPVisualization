#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "dpmatrix.h"

namespace Ui {
class MainWindow;
}

class DPMatrix;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DPMatrix *dp;

    void resetSource();
    void resetTarget();
    void toggleRun(bool);
    void toggleReset(bool);
    void updateSource();
    void updateTarget();

private slots:
    void runAlgorithm();
    void resetAlgorithm();
};

#endif // MAINWINDOW_H
