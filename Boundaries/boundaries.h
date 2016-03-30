#ifndef BOUNDARIES_H
#define BOUNDARIES_H

#include <QDialog>
#include "qtheader.h"
#include <opencv2/opencv.hpp>

namespace Ui {
class Boundaries;
}

class Boundaries : public QDialog
{
    Q_OBJECT

public:
    explicit Boundaries(QWidget *parent = 0);
    ~Boundaries();

private:
    Ui::Boundaries *ui;

private:
    cv::Mat imgSrc;
    cv::Mat imgSrcGray;
    cv::Mat imgEdges;

private slots:
    void Boundaries_Open_Slot();
    void Boundaries_Run_Slot();


};

#endif // BOUNDARIES_H
