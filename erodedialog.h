#ifndef ERODEDIALOG_H
#define ERODEDIALOG_H

#include <QDialog>
#include <QImage>
#include <opencv2/opencv.hpp>
#include "mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
namespace Ui {
class ErodeDialog;
}

class ErodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErodeDialog(QWidget *parent = 0);

    ~ErodeDialog();

private:
    Ui::ErodeDialog *ui;
    cv::Mat erodeImg;   // 从mainwindow复制过来的图像
    cv::Mat erodeCopy;  // 在这个类中用于操作的图像, 要在构造函数中

private slots:
    void erode_Excute_Slot();
    void erode_Save_slot();

public:
    void setErodeImage(cv::Mat);

};

#endif // ERODEDIALOG_H
