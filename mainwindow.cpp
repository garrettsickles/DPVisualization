#include "dpmatrix.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dp = new DPMatrix();
    ui->matrixDisplay->setWidget(dp);
    ui->targetInput->setText(INIT_STRING);
    ui->sourceInput->setText(INIT_STRING);
    this->resetAlgorithm();
    connect(ui->runButton, SIGNAL(clicked()), this, SLOT(runAlgorithm()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetAlgorithm()));
}

void MainWindow::runAlgorithm()
{
    toggleRun(false);
    toggleReset(true);
    ui->resetButton->setEnabled(true);
    updateSource();
    updateTarget();
    this->dp->setup(ui->sourceInput->text(), ui->targetInput->text());
}

void MainWindow::resetAlgorithm()
{
    toggleRun(true);
    toggleReset(false);
    resetSource();
    resetTarget();
    this->dp->setup(ui->sourceInput->text(), ui->targetInput->text());
}

void MainWindow::resetSource()
{
    ui->sourceInput->setEnabled(true);
    ui->sourceOutput->setText("Source");
}

void MainWindow::resetTarget()
{
    ui->targetInput->setEnabled(true);
    ui->targetOutput->setText("Target");
}

void MainWindow::toggleRun(bool var)
{
    ui->runButton->setEnabled(var);
    ui->runButton->setText(var ? "Run" : "Running");
}

void MainWindow::toggleReset(bool var)
{
    ui->resetButton->setEnabled(var);
}

void MainWindow::updateSource()
{
    ui->sourceOutput->setText(ui->sourceInput->text());
    ui->sourceInput->setDisabled(true);
}

void MainWindow::updateTarget()
{
    ui->targetOutput->setText(ui->targetInput->text());
    ui->targetInput->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
