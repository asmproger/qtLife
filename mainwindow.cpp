#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->n = 50;
    this->m = 50;

    this->initLife();
    connect(&this->timer, SIGNAL(timeout()), this, SLOT(on_pushButton_2_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLife() {
    this->current = new char*[this->n];
    this->next = new char*[this->n];
    int i=0;
    int j=0;
    for(i=0; i<this->n; i++) {
        this->current[i] = new char[this->m];
        this->next[i] = new char[this->m];
        for(j=0; j<this->m; j++) {
            this->next[i][j] = 0;
            this->current[i][j] = qRound( 1.0*rand()/RAND_MAX );
            QTableWidgetItem *tmp = new QTableWidgetItem();
            tmp->setText(QString::number(this->current[i][j]).toUpper());
        }
    }
//    this->current[4][4] = 1;
//    this->current[4][5] = 1;
//    this->current[4][6] = 1;

    this->drawCurrent();
}

void MainWindow::nextStep()
{
    int i, j;
    for(i=0;i<this->n;i++) {
        for(j=0;j<this->m;j++) {
            this->next[i][j] = this->processCell(i, j);
        }
    }
    this->changeSteps();
    this->drawCurrent();
}

char MainWindow::processCell(int i, int j)
{
    char cnt = 0;
    if(i==0 && j==0) { // top left
        cnt += this->current[i+1][j];
        cnt += this->current[i][j+1];
        cnt += this->current[i+1][j+1];
    } else if ((i==0 && j==this->m-1)) { //top right
        cnt += this->current[i+1][j];
        cnt += this->current[i][j-1];
        cnt += this->current[i+1][j-1];
    } else if ((i==this->n-1 && j==0)) { //left bottom
        cnt += this->current[i-1][j];
        cnt += this->current[i-1][j+1];
        cnt += this->current[i][j+1];
    } else if ((i==this->n-1 && j==this->m-1)) { //right bottom
        cnt += this->current[i-1][j];
        cnt += this->current[i-1][j-1];
        cnt += this->current[i][j-1];
    } else if(i>0 && i<this->n-1 && j>0 && j<this->m-1) {
        cnt += this->current[i-1][j-1];
        cnt += this->current[i-1][j];
        cnt += this->current[i-1][j+1];

        cnt += this->current[i][j-1];
        cnt += this->current[i][j+1];

        cnt += this->current[i+1][j-1];
        cnt += this->current[i+1][j];
        cnt += this->current[i+1][j+1];
    } else if( (i==0 || i==this->n-1) && (j>0 && j<this->m-1) ) {
        if(i==0) {
            cnt += this->current[i][j-1];
            cnt += this->current[i][j+1];
            cnt += this->current[i+1][j-1];
            cnt += this->current[i+1][j+1];
            cnt += this->current[i+1][j];
        }
        if(i==this->n-1) {
            cnt += this->current[i][j-1];
            cnt += this->current[i][j+1];
            cnt += this->current[i-1][j-1];
            cnt += this->current[i-1][j+1];
            cnt += this->current[i-1][j];
        }
    } else if( (j==0 || j==this->m-1) && (i>0 && i<this->n-1) ) {
        if(j==0) {
            cnt += this->current[i-1][j];
            cnt += this->current[i+1][j];
            cnt += this->current[i+1][j+1];
            cnt += this->current[i-1][j+1];
            cnt += this->current[i][j+1];
        }
        if(j==this->m-1) {
            cnt += this->current[i-1][j];
            cnt += this->current[i+1][j];
            cnt += this->current[i+1][j-1];
            cnt += this->current[i-1][j-1];
            cnt += this->current[i][j-1];
        }
    }
    if(this->current[i][j] == 0) {
        if(cnt != 3) return 0;
    } else {
        if(cnt > 3 || cnt < 2) return 0;
    }
    return 1;
}

void MainWindow::changeSteps()
{
    int i,j;
    for(i=0;i<this->n;i++) {
        for(j=0;j<this->m;j++) {
            char t = this->next[i][j];
            this->current[i][j] = t;
            this->next[i][j] = 0;

            QTableWidgetItem *tmp = new QTableWidgetItem();
            tmp->setText(QString::number(this->current[i][j]).toUpper());
            this->ui->tableWidget_2->setItem(i,j, tmp);

            QTableWidgetItem *tmp2 = new QTableWidgetItem();
            tmp2->setText(QString::number(this->next[i][j]).toUpper());
            this->ui->tableWidget_3->setItem(i,j, tmp2);
        }
    }
    int y = 0;
}

void MainWindow::drawCurrent()
{
    int i, j;
    for(i=0; i<this->n; i++) {
        for(j=0; j<this->m; j++) {
            QTableWidgetItem *tmp = new QTableWidgetItem();
            if(this->current[i][j] == 1)
                tmp->setBackgroundColor(Qt::green);
            else
                tmp->setBackgroundColor(Qt::black);
//            tmp->setText(QString::number(this->current[i][j]).toUpper());
            this->ui->tableWidget->setItem(i,j, tmp);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    this->timer.start(10);
}

void MainWindow::on_pushButton_2_clicked()
{
    this->nextStep();
}
