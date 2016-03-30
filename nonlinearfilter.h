#ifndef NONLINEARFILTER_H
#define NONLINEARFILTER_H

#include <QDialog>
#include "qtheader.h"
#include <opencv2/opencv.hpp>

namespace Ui {
class NonLinearFilter;
}

class NonLinearFilter : public QDialog
{
    Q_OBJECT

public:
    explicit NonLinearFilter(QWidget *parent = 0);
    ~NonLinearFilter();

private:
    Ui::NonLinearFilter *ui;

private:
    cv::Mat imgSrc;
    cv::Mat imgSrcRGB;
    cv::Mat imgDst;
    cv::Mat imgDstRGB;

private slots:
    void NonLinearFilter_Open_Slot();
    void NonLinearFilter_Run_Slot();
};

#endif // NONLINEARFILTER_H
