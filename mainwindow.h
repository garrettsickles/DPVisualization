#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "editdistance.h"

namespace Ui {
class MainWindow;
}

class EditDistance;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    EditDistance *dp;
    QString source;
    QString target;

    void initialize();

private slots:
    void update();
};

#endif // MAINWINDOW_H
