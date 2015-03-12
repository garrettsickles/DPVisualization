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
    ui->setupUi(this);
    ui->targetInput->setText(INIT_SOURCE);
    ui->sourceInput->setText(INIT_TARGET);
    connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->optionButton, SIGNAL(clicked()), this, SLOT(optionDialog()));
}

void MainWindow::update()
{
    this->source = ui->sourceInput->text();
    this->target = ui->targetInput->text();
    if(ui->matrixContents != NULL) delete ui->matrixContents;
    if(ui->algorithmType->currentIndex() == 0)
        ui->matrixContents = new EditDistance(this->source, this->target, this);
    else if(ui->algorithmType->currentIndex() ==1)
        ui->matrixContents = new CommonSubsequence(this->source, this->target, this);
    ui->matrixDisplay->setWidget(ui->matrixContents);
    ui->matrixDisplay->setWidgetResizable(true);
    ui->matrixContents->setEnabled(true);
}

void MainWindow::optionDialog() {
    bool ok;
    QInputDialog::getText(this, tr("Name"), tr("User Name:"), QLineEdit::Normal, "", &ok);
}

MainWindow::~MainWindow()
{
    delete ui;
}
