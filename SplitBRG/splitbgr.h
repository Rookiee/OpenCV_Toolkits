#ifndef SPLITBGR_H
#define SPLITBGR_H

#include <QDialog>
#include "qtheader.h"
#include <opencv2/opencv.hpp>
namespace Ui {
class SplitBGR;
}

class SplitBGR : public QDialog
{
    Q_OBJECT

public:
    explicit SplitBGR(QWidget *parent = 0);
    ~SplitBGR();

private:
    Ui::SplitBGR *ui;


private:
    cv::Mat imgSrc;
    cv::Mat imgBchannel;
    cv::Mat imgGchannel;
    cv::Mat imgRchannel;

private:
    void SaveAndQuitImage(cv::Mat &image);
private slots:
    void SplitBGR_Open_Slot();
    void SPlitBGR_Run_Slot();

};

#endif // SPLITBGR_H
