#include "mainwindow.h"
#include "ui_mainwindow.h"
// 打开,另存图片(文件)
#include <QFile>
#include <QFileDialog>
// opencv, qt图片转换
#include <QImage>
#include <QPixmap>
//--------------------
#include <QMessageBox>
#include <iostream>
#include <string>
#include <QString>
#include <QDebug>

//--------------------
//#include "ErodeDialog.h"

using namespace cv;
using namespace std;

class ErodeDialog;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*-------------------开始界面准备-------------------------------*/
    this->setWindowTitle("OpenCV ToolKits");    // 显示标题栏内容
    ui->imgSrcLabel->clear();   // 开始时就清空主界面 imgSrcLabel 的显示内容
    this->setCentralWidget(ui->imgSrcLabel);    // 设置布局



    /*------------------信号/槽-----------------------------------*/
    QObject::connect(ui->action_OpenImage,SIGNAL(triggered()),
                     this,SLOT(action_Files_OpenImage_Slot()));
    QObject::connect(ui->action_SaveAs,SIGNAL(triggered(bool)),
                     this, SLOT(action_Files_SaveAs_Slot()));

    QObject::connect(ui->action_Erode, SIGNAL(triggered(bool)),
                     this,SLOT(action_Tools_Erode_Slot()));
    QObject::connect(ui->action_addWeighted,SIGNAL(triggered(bool)),
                     this, SLOT(action_Tools_AddWeighted_Slot()));
    QObject::connect(ui->action_LinearFilter,SIGNAL(triggered(bool)),
                     this,SLOT(action_Tools_LinearFilter_Slot()));
    QObject::connect(ui->action_Non_LinearFilter, SIGNAL(triggered(bool)),
                     this, SLOT(action_Tools_NonLinearFilter_Slot()));
    QObject::connect(ui->action_Histogram, SIGNAL(triggered(bool)),
                     this, SLOT(action_Tools_Histogram_Slot()));
    QObject::connect(ui->action_Boundaries, SIGNAL(triggered(bool)),
                     this, SLOT(action_Tools_Boundaries_Slot()));
    QObject::connect(ui->action_SplitRGB, SIGNAL(triggered(bool)),
                     this, SLOT(action_Tools_SplitBGR_Slot()));

}



MainWindow::~MainWindow()
{
    delete ui;
}



Mat MainWindow::getImageRGB()   // 获取Qt-RGB图像
{
    return this->imgSrcRGB;
}

Mat MainWindow::getImageBGR()   // 获取OpenCV-BGR图像
{
    return this->imgSrc;
}

void MainWindow::action_Files_OpenImage_Slot()  // 打开图片的槽函数
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Image",
                                                    QDir::homePath(),
                                                    tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));
//    path = fileName.toLatin1().data();
    path = fileName.toStdString();
    imgSrc = imread(path);
    if(imgSrc.empty()){
//        QMessageBox::warning(this, "Warning","Can not open the image");
        return;

    }
    cvtColor(imgSrc, imgSrcRGB, CV_BGR2RGB);
    QImage qImgSrc = QImage((const unsigned char*)(imgSrcRGB.data),
                            imgSrcRGB.cols, imgSrcRGB.rows,
                            imgSrcRGB.cols * imgSrcRGB.channels(),
                            QImage::Format_RGB888);
    ui->imgSrcLabel->clear();
    ui->imgSrcLabel->setPixmap(QPixmap::fromImage(qImgSrc));
    ui->imgSrcLabel->resize(ui->imgSrcLabel->pixmap()->size());




}

void MainWindow::action_Files_SaveAs_Slot()
{
    QString saveFileName = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),
                                                        tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));
    if(saveFileName.isEmpty())
    {
//        QMessageBox::information(this,"Error Message","Please select a file");
        return;
    }
//    cvtColor(imgSrc,imgSrc,CV_RGB2BGR);
    std::string savePath = saveFileName.toStdString();
    imwrite(savePath, imgSrc);

}




// 这个函数很关键: 1. 从一个界面跳转到另一个界面;
//              2. 在跳转的同时,也把这个类的私有成员,赋值给了另一个类的私有成员
//              3. 并且这两个类没有继承关系
void MainWindow::action_Tools_Erode_Slot()
{
    ErodeDialog *erodeDialog = new ErodeDialog;
    erodeDialog->setErodeImage(this->imgSrc);
//    erodeDialog->exec();
    erodeDialog->show();
}

void MainWindow::action_Tools_AddWeighted_Slot()
{
    AddWeighted *addDialog = new AddWeighted;
    addDialog->exec();
    //    addDialog->show();    // 有了exec， 就不用再show了
}

void MainWindow::action_Tools_LinearFilter_Slot()
{
    LinearFilter *linearFilterDialog = new LinearFilter;
    linearFilterDialog->exec();
}

void MainWindow::action_Tools_NonLinearFilter_Slot()
{
    NonLinearFilter *nonLinearFilterDialog = new NonLinearFilter;
    nonLinearFilterDialog->exec();
}

void MainWindow::action_Tools_Histogram_Slot()
{
    HistogramWidget * histogramWidget = new HistogramWidget();
    histogramWidget->exec();
}

void MainWindow::action_Tools_Boundaries_Slot()
{
    Boundaries * boundariesDialog = new Boundaries;
    boundariesDialog->exec();
}

void MainWindow::action_Tools_SplitBGR_Slot()
{
    SplitBGR * splitBGRDialog = new SplitBGR;
    splitBGRDialog->exec();
}













