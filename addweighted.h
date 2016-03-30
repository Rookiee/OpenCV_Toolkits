#ifndef ADDWEIGHTED_H
#define ADDWEIGHTED_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include "qtheader.h"
#include "addresult.h"
namespace Ui {
class AddWeighted;
}

class AddWeighted : public QDialog
{
    Q_OBJECT

public:
    explicit AddWeighted(QWidget *parent = 0);
    ~AddWeighted();

private:
    Ui::AddWeighted *ui;

private:
    // 这里的图像与mainwindow中的图像不相关
    cv::Mat imgSrc1;
    cv::Mat imgSrc2;
     cv::Mat imgDst;
    // addWeitghted 需要的
//    const int maxValue = 100;
    int alphaValueSlider;
    double alphaValue;
    double betaValue;

private slots:
    void addWeighted_firstImgButton_Slot();
    void addWeighted_secondImgButton_Slot();
//    void addWeighted_addWeightedButton_Slot();
    void addWeighted_addWeightedButtonQt_Slot();

public:
    // 使用OpenCV的createTrackbar函数，要有一个回调函数，
    // 在C++类中使用回调函数很复杂，换用Qt实现
//    typedef void (*fp)(int, void*);
//    typedef void (*TrackbarCallback)(int pos, void* userdata);
//    static void on_Trackbar(int, void *);


};

#endif // ADDWEIGHTED_H
