#include "nonlinearfilter.h"
#include "ui_nonlinearfilter.h"


NonLinearFilter::NonLinearFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NonLinearFilter)
{

    ui->setupUi(this);
    ui->showLabel->clear();

    /* Set tips */
    ui->toolBox->setToolTip("中值滤波适合去除椒盐噪声");

    ui->kernelSizespinBox->setValue(1);
    ui->kernelSizespinBox->setSingleStep(2);


    ui->dspinBox->setMinimum(-1);
    ui->dspinBox->setMaximum(100);
    ui->dspinBox->setValue(25);

    ui->colorspinBox->setSingleStep(0.1);
    ui->spacedoubleSpinBox->setSingleStep(0.1);
    ui->colorspinBox->setValue(25*2);
    ui->spacedoubleSpinBox->setValue(25.0/2);



    QObject::connect(ui->OpenButton, SIGNAL(clicked(bool)),
                     this, SLOT(NonLinearFilter_Open_Slot()));
    QObject::connect(ui->RunButton, SIGNAL(clicked(bool)),
                     this, SLOT(NonLinearFilter_Run_Slot()));
}

NonLinearFilter::~NonLinearFilter()
{
    delete ui;
}

void NonLinearFilter::NonLinearFilter_Open_Slot()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Image",
                                                    QDir::homePath(),
                                                    tr("(*.png *.jpg *.jpeg *.bmp)"));
    if (fileName.isEmpty())
        return;
    std::string path = fileName.toStdString();
    imgSrc = cv::imread(path);

    cv::cvtColor(imgSrc, imgSrcRGB, cv::COLOR_BGR2RGB);

//    QImage qImg;
//    convert2QtImg(imgSrcRGB, qImg);

    QImage qImg = QImage((const unsigned char*)(imgSrcRGB.data),
                         imgSrcRGB.cols,
                         imgSrcRGB.rows,
                         imgSrcRGB.cols * imgSrcRGB.channels(),
                         QImage::Format_RGB888);

    ui->showLabel->setPixmap(QPixmap::fromImage(qImg));
    ui->showLabel->resize(ui->showLabel->pixmap()->size());
}

void NonLinearFilter::NonLinearFilter_Run_Slot()
{
    if(ui->toolBox->currentIndex()==0){
        int ksize = ui->kernelSizespinBox->value();

        if (ksize <= 1){
            QMessageBox::information(this, "Error","The Kernel Size must be greater than 1.");
            return;
        }
        else if (ksize % 2 == 0){
            QMessageBox::information(this, "Error","The Kernel Size must be odd.");
            return;
        }

        else if ((ksize==3 || ksize==5) &&
                (imgSrc.depth() == CV_8U || imgSrc.depth() == CV_16U || imgSrc.depth() == CV_32F)){
            cv::medianBlur(imgSrc, imgDst, ksize);
        }
        else if ((ksize==3 || ksize==5) &&
                 (imgSrc.depth() != CV_8U && imgSrc.depth() != CV_16U && imgSrc.depth() != CV_32F)){
            QMessageBox::warning(this,"Warning", tr("When the ksize is 3 or 5, the depth of the "
                                                                    "image must be CV_8U, CV_16U or CV_32F"));
            return;
        }
        else if (ksize>5 && imgSrc.depth() == CV_8U){
            cv::medianBlur(imgSrc, imgDst, ksize);
        }
        else if (ksize>5 && imgSrc.depth() != CV_8U){
                QMessageBox::warning(this, "Waring", tr("For greater ksize, the depth of the image"
                                                        "must be CV_8U"));
                return;
        }

    }
    if(ui->toolBox->currentIndex() == 1){
        // 过滤过程中每个像素邻域的直径，如果为非整数，那么会从sigmaSpace中计算出来，与sigmaSpace成正比
        int d = ui->dspinBox->value();
        double sigmaColor = ui->colorspinBox->value();
        double sigmaSpace = ui->spacedoubleSpinBox->value();
        cv::bilateralFilter(imgSrc,imgDst,d,sigmaColor,sigmaSpace,cv::BorderTypes::BORDER_DEFAULT);
    }
    cv::cvtColor(imgDst, imgDstRGB, cv::COLOR_BGR2RGB);
    QImage qImg = QImage((const unsigned char*)(imgDstRGB.data),
                         imgDstRGB.cols, imgDstRGB.rows,
                         imgDstRGB.cols * imgDstRGB.channels(),
                         QImage::Format_RGB888);
    ui->showLabel->setPixmap(QPixmap::fromImage(qImg));
    ui->showLabel->resize(ui->showLabel->pixmap()->size());
}
