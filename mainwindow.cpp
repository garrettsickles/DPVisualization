#include "editdistance.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->initialize();
    this->update();
}

void MainWindow::initialize()
{
    this->dp = NULL;
    ui->setupUi(this);
    ui->targetInput->setText(INIT_STRING);
    ui->sourceInput->setText(INIT_STRING);
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(update()));
}

void MainWindow::update()
{
    this->source = ui->sourceInput->text();
    this->target = ui->targetInput->text();
    if(dp != NULL) delete dp;
    dp = new EditDistance(this->source, this->target, this);
    ui->matrixDisplay->setWidget(dp);
    dp->setEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dp;
}
