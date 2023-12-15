#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "utils.h"
#include <QGridLayout>
#include <QSize>
#include <QFileDialog>
#include <QDebug>
#include <QString>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    utils.ImageReslice();
    //utils.test5_3_2();
    ui->vtk_leftTop->setRenderWindow(utils.renderWindowLeftTop);
    ui->vtk_rightTop->setRenderWindow(utils.renderWindowRightTop);
    ui->vtk_leftBottom->setRenderWindow(utils.renderWindowLeftBottom);
    ui->vtk_rightBottom->setRenderWindow(utils.renderWindowRightBottom);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSaveImage_clicked()
{
    QString qstrDir = QFileDialog::getExistingDirectory(this,QString("selectDir"),"../images/");
    qDebug() << qstrDir;


}

