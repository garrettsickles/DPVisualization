#include "editdistance.h"
#include "mainwindow.h"
#include "displaygrid.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->dm = NULL;
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
    this->source = ui->sourceInput->text();
    this->target = ui->targetInput->text();

    if(dm != NULL) delete dm;
    if(ui->algorithmType->currentIndex() == 0) {
        dm = new DPDisplay(new EditDistance(this->source.toStdString(), this->target.toStdString()), this);
    }
    else if(ui->algorithmType->currentIndex() ==1) {
        dm = new DPDisplay(new CommonSubsequence(this->source.toStdString(), this->target.toStdString()), this);
    }

    for(int i = 2; i < dm->getRows(); i++) dm->set(i, 0, this->source.at(i-2));
    for(int i = 2; i < dm->getColumns(); i++) dm->set(0, i, this->target.at(i-2));

    ui->matrixContents = dm;
    this->zoom();

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
    dm->setCellSize(ui->zoomSlider->value(), ui->zoomSlider->value());
    ui->matrixContents->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dm;
}
