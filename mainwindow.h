#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <stdlib.h>
#include <QMainWindow>

#include <opencv2/opencv.hpp>
#include <string>

#include "erodedialog.h"
#include "addweighted.h"
#include "linearfilter.h"
#include "nonlinearfilter.h"
#include "Histogram/histogramwidget.h"
#include "Boundaries/boundaries.h"
#include "SplitBRG/splitbgr.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    cv::Mat getImageRGB();  // 用于获取Qt格式的图像进行其余操作
    cv::Mat getImageBGR();  // 用于获取原始图像

private:
    Ui::MainWindow *ui;
    cv::Mat imgSrc;     // 最初打开的源图片
    cv::Mat imgSave;    // 最终保存的图片
    cv::Mat imgSrcRGB;  // 中间图像,为了保证Qt在处理的时候不改变原始的imgSrc
    std::string path;

private slots:
    void action_Files_OpenImage_Slot();     // 打开图片的槽函数
    void action_Files_SaveAs_Slot();        // 另存为图片, 为了保留原始图片,不提供直接保存, 不提供直接保存功能
    void action_Tools_Erode_Slot();
    void action_Tools_AddWeighted_Slot();
    void action_Tools_LinearFilter_Slot();
    void action_Tools_NonLinearFilter_Slot();
    void action_Tools_Histogram_Slot();
    void action_Tools_Boundaries_Slot();
    void action_Tools_SplitBGR_Slot();


};

#endif // MAINWINDOW_H
