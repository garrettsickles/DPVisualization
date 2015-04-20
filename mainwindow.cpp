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
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoom()));
    connect(ui->tracebackCheckBox, SIGNAL(stateChanged(int)), this, SLOT(update()));
    connect(ui->caseCheckBox, SIGNAL(stateChanged(int)), this, SLOT(update()));
}

void MainWindow::update()
{
    if(dm != NULL) delete dm;
    if(ui->algorithmType->currentIndex() == 0) {
        this->reset();
        this->source = ui->sourceInput->text();
        this->target = ui->targetInput->text();
        dm = new DPDisplay(new EditDistance(this->source.toStdString(), this->target.toStdString()), this);
        dm->getCellText()->setOptimalMin();
        dm->getCellText()->setOperationCosts(0, 1, 1, 1);
        dm->getCellText()->setOperationText('m', 's', 'i', 'd');
        dm->getCellText()->initialize();
        this->dm->updateDisplay();
        this->dm->repaint();
    }
    else if(ui->algorithmType->currentIndex() == 1) {
        this->reset();
        this->source = ui->sourceInput->text();
        this->target = ui->targetInput->text();
        dm = new DPDisplay(new EditDistance(this->source.toStdString(), this->target.toStdString()), this);
        dm->getCellText()->setOptimalMax();
        dm->getCellText()->setOperationCosts(1, 0, 0, 0);
        dm->getCellText()->setOperationText('m', '-', '-', '-');
        dm->getCellText()->initialize();
        this->dm->updateDisplay();
        this->dm->repaint();
    }
    else if(ui->algorithmType->currentIndex() == 2) {
        this->reset();
        this->source = ui->sourceInput->text();
        this->target = ui->targetInput->text();
        dm = new DPDisplay(new EditDistance(this->source.toStdString(), this->target.toStdString()), this);
        dm->getCellText()->setOptimalMax();
        dm->getCellText()->setOperationCosts(1, 0, 0, 0);
        dm->getCellText()->setOperationText('m', '-', '-', '-');
        dm->getCellText()->initialize();
        this->dm->updateDisplay();
        this->dm->repaint();
    }

    for(int i = 2; i < dm->getRows(); i++) dm->setCellText(i, 0, this->source.at(i-2));
    for(int i = 2; i < dm->getColumns(); i++) dm->setCellText(0, i, this->target.at(i-2));

    dm->getCellText()->setCaseSensitive(ui->caseCheckBox->isChecked());
    dm->setManualTraceback(ui->tracebackCheckBox->isChecked());
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
    if(this->ui->algorithmType->currentIndex() == 1 || this->ui->algorithmType->currentIndex() == 0) {
        ui->targetInput->setEnabled(true);
        ui->transposeButton->setEnabled(true);
        ui->caseCheckBox->setEnabled(true);
    } else if(this->ui->algorithmType->currentIndex() == 2) {
        ui->sourceInput->setText("4259");
        ui->targetInput->setText(MMS);
        ui->targetInput->setEnabled(false);
        ui->transposeButton->setEnabled(false);
        ui->caseCheckBox->setEnabled(false);
    }
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
