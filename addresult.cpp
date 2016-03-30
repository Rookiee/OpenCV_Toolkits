#include "addresult.h"
#include "ui_addresult.h"

addResult::addResult(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addResult)
{
    ui->setupUi(this);
    // 界面相关内容

    ui->valueSlider->setMinimum(1);
    ui->valueSlider->setMaximum(100);
    ui->valueSlider->setValue(50);
    this->sliderValue = ui->valueSlider->value();




    QObject::connect(ui->valueSlider, SIGNAL(valueChanged(int)),
                     this, SLOT(addResult_Slider_Slot(int)));
    QObject::connect(ui->valueSlider,SIGNAL(valueChanged(int)),
                     ui->numberLabel,SLOT(setNum(int)));
    QObject::connect(ui->saveButton, SIGNAL(clicked(bool)),
                     this, SLOT(addResult_Save_Slot()));


}

addResult::~addResult()
{
    delete ui;
}

void addResult::setImage(cv::Mat img1_, cv::Mat img2_)
{
    this->img1 = img1_.clone();
    this->img2 = img2_.clone();
}

void addResult::addResult_Slider_Slot(int value)
{
    this->sliderValue = value;
    cv::addWeighted(img1, value/(double)(100),
                    img2, 1.0 -(value/(double)(100)),
                    0.0, result);
    cv::cvtColor(result, result, cv::COLOR_BGR2RGB);
    QImage qresult = QImage((const unsigned char*)(result.data),
                            result.cols, result.rows,
                            result.cols*result.channels(),
                            QImage::Format_RGB888);
    ui->addResultImageLabel->setPixmap(QPixmap::fromImage(qresult));
    ui->addResultImageLabel->resize(ui->addResultImageLabel->pixmap()->size());
//    cv::cvtColor(result, result, cv::COLOR_RGB2BGR);
//    cv::imshow("a",result);
}

void addResult::addResult_Save_Slot()
{
//    cv::imshow("a",result); // Now is RGB
    cv::cvtColor(result, result, cv::COLOR_RGB2BGR);
//    cv::imshow("b",result); // Now is BGR
    QString saveFileName = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),
                                                        tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));
    if(saveFileName.isEmpty())
    {
//        QMessageBox::information(this,"Error Message","Please select a file");
        return;
    }
//    cvtColor(result,result,CV_RGB2BGR);
    std::string savePath = saveFileName.toStdString();
    imwrite(savePath, result);
}
