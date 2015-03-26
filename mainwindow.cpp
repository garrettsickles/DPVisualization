#include "editdistance.h"
#include "mainwindow.h"
#include "dpmatrix.h"
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
    connect(ui->transposeButton, SIGNAL(clicked()), this, SLOT(transpose()));
    connect(ui->optionButton, SIGNAL(clicked()), this, SLOT(options()));
}

void MainWindow::update()
{
    if(ui->sourceInput->text().length() < DEFAULT_MAX_LENGTH && ui->targetInput->text().length() < DEFAULT_MAX_LENGTH) {
        this->source = ui->sourceInput->text();
        this->target = ui->targetInput->text();
        if(ui->matrixContents != NULL) delete ui->matrixContents;
        if(ui->algorithmType->currentIndex() == 0)
            ui->matrixContents = new EditDistance(this->source, this->target, this);
        else if(ui->algorithmType->currentIndex() ==1)
            ui->matrixContents = new CommonSubsequence(this->source, this->target, this);

        QRect r = ui->matrixDisplay->geometry();

        ui->matrixDisplay = new QScrollArea(this);
        ui->matrixDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ui->matrixDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ui->matrixDisplay->setGeometry(r);
        ui->matrixDisplay->setFixedHeight(r.height());
        ui->matrixDisplay->setFixedWidth(r.width());
        ui->matrixDisplay->setWidget(ui->matrixContents);
        ui->matrixDisplay->adjustSize();
        ui->matrixDisplay->show();
        ui->matrixContents->show();
        this->setFixedSize(this->size());
    }
    else {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Source or Target too Long!!!");
        messageBox.setFixedSize(500,200);
        ui->targetInput->setText(INIT_SOURCE);
        ui->sourceInput->setText(INIT_TARGET);
        this->update();
    }
}

void MainWindow::transpose()
{
    ui->sourceInput->setText(this->target);
    ui->targetInput->setText(this->source);
    this->update();
}

void MainWindow::options()
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
