#include "addweighted.h"
#include "ui_addweighted.h"
#include <string>
#define WINDOW_NAME "ADD_WEIGHT"

AddWeighted::AddWeighted(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWeighted)
{
    ui->setupUi(this);

    QObject::connect(ui->firstImgButton, SIGNAL(clicked(bool)),
                     this, SLOT(addWeighted_firstImgButton_Slot()));
    QObject::connect(ui->secondImgButton, SIGNAL(clicked(bool)),
                     this, SLOT(addWeighted_secondImgButton_Slot()));
//    QObject::connect(ui->addWeightedButton, SIGNAL(clicked(bool)),
//                     this, SLOT(addWeighted_addWeightedButton_Slot()));
    QObject::connect(ui->addWeightedButtonQt, SIGNAL(clicked(bool)),
                     this, SLOT(addWeighted_addWeightedButtonQt_Slot()));

}

AddWeighted::~AddWeighted()
{
    delete ui;
}

void AddWeighted::addWeighted_firstImgButton_Slot()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Image",
                                                    QDir::homePath(),
                                                    tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));
    std::string path = fileName.toStdString();
    if (path.empty()){
        return;
    }
    imgSrc1 = cv::imread(path);

    cv::Mat imgSrc1Copy;
    cv::cvtColor(imgSrc1, imgSrc1Copy, cv::COLOR_BGR2RGB);
    QImage qImgSrc1 = QImage((const unsigned char*)(imgSrc1Copy.data),
                             imgSrc1.cols, imgSrc1.rows,
                             imgSrc1.cols*imgSrc1.channels(),
                             QImage::Format_RGB888);
    ui->firstImgLabel->clear();
    ui->firstImgLabel->setPixmap(QPixmap::fromImage(qImgSrc1));
    ui->firstImgLabel->resize(ui->firstImgLabel->pixmap()->size());
}

void AddWeighted::addWeighted_secondImgButton_Slot()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Image",
                                                    QDir::homePath(),
                                                    tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));

    std::string path = fileName.toStdString();
    if(path.empty()){
        return;
    }
    imgSrc2 = cv::imread(path);
    cv::Mat imgSrc2Copy;
    cv::cvtColor(imgSrc2, imgSrc2Copy, cv::COLOR_BGR2RGB);
    QImage qImgSrc2 = QImage((const unsigned char*)(imgSrc2Copy.data),
                             imgSrc2.cols, imgSrc2.rows,
                             imgSrc2.cols*imgSrc2.channels(),
                             QImage::Format_RGB888);
    ui->secondImgLabel->clear();
    ui->secondImgLabel->setPixmap(QPixmap::fromImage(qImgSrc2));
    ui->secondImgLabel->resize(ui->secondImgLabel->pixmap()->size());
}

void AddWeighted::addWeighted_addWeightedButtonQt_Slot()
{
    addResult * result = new addResult;
    if (imgSrc1.size != imgSrc2.size){
        QMessageBox::information(this, "NO MATHCH",
                                 "The size of these two images are different!");
        return;
    }

    result->setImage(this->imgSrc1, this->imgSrc2);

    result->exec();
}
/******************************************************************************
// 使用OpenCV的createTrackbar函数，要有一个回调函数，
// 在C++类中使用回调函数很复杂，换用Qt实现
//void AddWeighted::addWeighted_addWeightedButton_Slot()
//{
//    if (imgSrc1.size != imgSrc2.size){
//        QMessageBox::information(this, "NO MATHCH", "The size of these two images are different!");
//        return;
//    }
//    this->alphaValueSlider = 50;
//    cv::namedWindow(WINDOW_NAME, CV_WINDOW_NORMAL);
//    const char trackbarName[50] = "Cap: 100";

////    cv::createTrackbar(trackbarName,WINDOW_NAME,&(this->alphaValueSlider),100,&on_Trackbar);
////    cv::createTrackbar(trackbarName,WINDOW_NAME,&alphaValueSlider,100,on_Trackbar);
//    on_Trackbar(this->alphaValueSlider, 0);

//    if (cv::waitKey(0) == 27){
//        cv::destroyAllWindows();
//    }

//}


//void AddWeighted::on_Trackbar(int, void *)
//{

//    alphaValue = (double)(alphaValueSlider/100);
//    betaValue = 1.0 - alphaValue;
//    cv::addWeighted(imgSrc1, alphaValue,
//                    imgSrc2, betaValue,
//                    0.0, imgDst);

//    cv::imshow(WINDOW_NAME, imgDst);

//}
**********************************************************************************/
