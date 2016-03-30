#include "splitbgr.h"
#include "ui_splitbgr.h"
#include <vector>

SplitBGR::SplitBGR(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplitBGR)
{
    ui->setupUi(this);
    this->showMaximized();
    ui->label->clear();

    QObject::connect(ui->openButton, SIGNAL(clicked(bool)),
                     this, SLOT(SplitBGR_Open_Slot()));
    QObject::connect(ui->runButton,SIGNAL(clicked(bool)),
                     this, SLOT(SPlitBGR_Run_Slot()));
}

SplitBGR::~SplitBGR()
{
    delete ui;
}

void SplitBGR::SplitBGR_Open_Slot()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Image",
                                                    QDir::homePath(),
                                                    tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));
    if(fileName.isEmpty()){
        return;
    }
    std::string path = fileName.toStdString();
    imgSrc = cv::imread(path);
    cv::Mat imgRGB;
    cv::cvtColor(imgSrc, imgRGB, cv::COLOR_BGR2RGB);
    QImage qImg = QImage((const unsigned char *)(imgRGB.data),
                         imgRGB.cols,
                         imgRGB.rows,
                         imgRGB.channels() * imgRGB.cols,
                         QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(qImg));
    ui->label->resize(ui->label->pixmap()->size());


}

void SplitBGR::SPlitBGR_Run_Slot()
{
    typedef std::vector<cv::Mat> MatVector;
    MatVector mv;
    cv::split(imgSrc,mv);
    if (ui->splitRradioButton->isChecked()){
        imgRchannel = mv[2];
        cv::namedWindow("R Channel");
        cv::imshow("R Channel", imgRchannel);
        SaveAndQuitImage(imgRchannel);
    }
    if (ui->splitGradioButton->isChecked()){
        imgGchannel = mv[1];
        cv::namedWindow("G Channel");
        cv::imshow("G Channel", imgGchannel);
        SaveAndQuitImage(imgGchannel);
    }
    if (ui->splitBradioButton->isChecked()){
        imgBchannel = mv[0];
        cv::namedWindow("B Channel");
        cv::imshow("B Chnanel", imgBchannel);
        SaveAndQuitImage(imgBchannel);
    }
}

void SplitBGR::SaveAndQuitImage(cv::Mat &image){
    int key = cv::waitKey();
    if(key == 27){
        cv::destroyAllWindows();
    }
    else if (key == int('s')){
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        "Open Image",
                                                        QDir::homePath(),
                                                        tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));
        if(fileName.isEmpty()){
            return;
        }
        std::string path = fileName.toStdString();
        cv::imwrite(path, image);
    }
}
