#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QDialog>
#include "qtheader.h"
#include <opencv2/opencv.hpp>

namespace Ui {
class HistogramWidget;
}

class HistogramWidget : public QDialog
{
    Q_OBJECT

public:
    explicit HistogramWidget(QWidget *parent = 0);
    ~HistogramWidget();

private:
    Ui::HistogramWidget *ui;

private:
    cv::Mat imgSrc;
    cv::Mat srcRGB;
    cv::Mat imgDst;
    cv::Mat dstRGB;

    cv::Mat grayImg;
    cv::MatND hist;

    cv::MatND redHist, greenHist, blueHist;

private:
    // For 1D
    /* void calcHist( const Mat* arrays, int narrays,
            const int* channels, const Mat& mask,
            MatND& hist, int dims, const int* histSize,
            const float** ranges, bool uniform=true,
            bool accumulate=false );
    */
    int histSize[1];    // number of bins
    float hranges[2];   // min and max pixel value
//    const float *ranges[1];   // 注释掉了，改为用的时候定义为局部变量，因为本身是const，用的
                                // 时候声明、定义方便一些；
    int channels[1];    // only 1 channel used here; For H-S 2D, 2 channels used,

private slots:
    void HistogramWidget_Open_Slot();
    void HistogramWidget_Run_Slot();

public:
    // Compute and plot 1D Histogram
    cv::MatND getHistogramD1(const cv::Mat &image);
    cv::Mat getHistogramImageD1();

    // Compute and plot 2D H-S Histogram
    cv::MatND getHistogramHS(const cv::Mat &image);
    cv::Mat getHistogramImageHS();

    // Compute and plot 3D RGB Histogram
    cv::MatND getHistogramRGB(const cv::Mat &image, const char flag);
    cv::Mat getHistogramImageRGB(const char flag);
};

#endif // HISTOGRAMWIDGET_H
