#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QInputDialog>
#include <QLabel>
#include <QVBoxLayout>

class OptionDialog : public QDialog
{
    Q_OBJECT
public:
    optiondialog(QWidget *parent = 0);
    ~optiondialog();
};

#endif // OPTIONDIALOG_H
