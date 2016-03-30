#ifndef LINEARFILTER_H
#define LINEARFILTER_H

#include <QDialog>
#include "qtheader.h"
#include <opencv2/opencv.hpp>


namespace Ui {
class LinearFilter;
}

class LinearFilter : public QDialog
{
    Q_OBJECT

public:
    explicit LinearFilter(QWidget *parent = 0);
    ~LinearFilter();

private:
    Ui::LinearFilter *ui;

private:
    cv::Mat imgSrc;
    cv::Mat imgDst;
    cv::Mat imgSrcRGB;
    cv::Mat imgDstRGB;
    int ksize = 3;
    int depth = -1;


private slots:
    void LinearFilter_Open_Slot();
    void LinearFilter_Run_Slot();
    void LinearFilter_Save_Slot();
};

#endif // LINEARFILTER_H
