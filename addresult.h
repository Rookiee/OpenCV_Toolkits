#ifndef ADDRESULT_H
#define ADDRESULT_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include "qtheader.h"
namespace Ui {
class addResult;
}

class addResult : public QDialog
{
    Q_OBJECT

public:
    explicit addResult(QWidget *parent = 0);
    ~addResult();

private:
    Ui::addResult *ui;

private:
    cv::Mat result;
    cv::Mat img1;
    cv::Mat img2;
    int sliderValue;
public:
    void setImage(cv::Mat img1_, cv::Mat img2_);

private slots:
    void addResult_Slider_Slot(int);
    void addResult_Save_Slot();
};



#endif // ADDRESULT_H
