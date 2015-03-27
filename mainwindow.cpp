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
    ui->zoomSlider->setMinimum(30);
    ui->zoomSlider->setMaximum(100);
    connect(ui->sourceInput, SIGNAL(textEdited(QString)), this, SLOT(update()));
    connect(ui->targetInput, SIGNAL(textEdited(QString)), this, SLOT(update()));
    connect(ui->algorithmType, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
    connect(ui->transposeButton, SIGNAL(clicked()), this, SLOT(transpose()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom()));
    connect(ui->tracebackCheckBox, SIGNAL(stateChanged(int)), this, SLOT(update()));
    connect(ui->caseCheckBox, SIGNAL(stateChanged(int)), this, SLOT(update()));
}

void MainWindow::update()
{
    if(ui->sourceInput->text().length() < DEFAULT_MAX_LENGTH && ui->targetInput->text().length() < DEFAULT_MAX_LENGTH) {
        this->source = ui->sourceInput->text();
        this->target = ui->targetInput->text();
        if(ui->matrixContents != NULL) delete ui->matrixContents;
        if(ui->algorithmType->currentIndex() == 0) {
            ui->matrixContents = new EditDistance(this->source, this->target, this);
            dp = static_cast<EditDistance*>(ui->matrixContents);
        }
        else if(ui->algorithmType->currentIndex() ==1) {
            ui->matrixContents = new CommonSubsequence(this->source, this->target, this);
            dp = static_cast<CommonSubsequence*>(ui->matrixContents);
        }
        dp->resizeSquare(ui->zoomSlider->value());
        dp->setManualTraceback(ui->tracebackCheckBox->isChecked());
        dp->setCaseSensitive(ui->caseCheckBox->isChecked());

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

void MainWindow::reset()
{
    ui->targetInput->setText(INIT_SOURCE);
    ui->sourceInput->setText(INIT_TARGET);
    this->update();
}

void MainWindow::zoom()
{
    dp->resizeSquare(ui->zoomSlider->value());
    ui->matrixContents->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}
