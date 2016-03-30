#include "linearfilter.h"
#include "ui_linearfilter.h"



LinearFilter::LinearFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinearFilter)
{
    ui->setupUi(this);
    ui->showImage->clear();
    this->setWindowTitle("Linear Filter");
    /* initial parameter in boxFilter */
    ui->boxKernelDepthspinBox->setMinimum(-1);
    ui->boxKernelDepthspinBox->setMaximum(100);
    ui->boxKernelDepthspinBox->setValue(-1);
    ui->boxKernelSizespinBox->setValue(3);

    /* initial parameter in blurFilter */
    ui->blurKernelSizespinBox->setValue(3);

    /* initial parameter in gaussianFilter */
    ui->gaussianKernelSizespinBox->setValue(3);



    QObject::connect(ui->openImageButton, SIGNAL(clicked()),
                     this, SLOT(LinearFilter_Open_Slot()));
    QObject::connect(ui->runButton,SIGNAL(clicked()),
                     this,SLOT(LinearFilter_Run_Slot()));
    QObject::connect(ui->saveButton, SIGNAL(clicked(bool)),
                     this, SLOT(LinearFilter_Save_Slot()));
}

LinearFilter::~LinearFilter()
{
    delete ui;
}
/*---------------------Open Image------------------------*/
void LinearFilter::LinearFilter_Open_Slot()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Image",
                                                    QDir::homePath(),
                                                    tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));
    if (fileName.isEmpty())
        return;
    std::string path = fileName.toStdString();
    imgSrc = cv::imread(path);

    cv::cvtColor(imgSrc, imgSrcRGB,CV_BGR2RGB);
    QImage qImg = QImage((const unsigned char*)(imgSrcRGB.data),
                         imgSrcRGB.cols,
                         imgSrcRGB.rows,
                         imgSrcRGB.cols*imgSrcRGB.channels(),
                         QImage::Format_RGB888);

//    QImage qImg;
//    convert2QtImg(imgSrcRGB, qImg);

    ui->showImage->clear();
    ui->showImage->setPixmap(QPixmap::fromImage(qImg));
    ui->showImage->resize(ui->showImage->pixmap()->size());
}

/*-----------------------RUN------------------------*/
void LinearFilter::LinearFilter_Run_Slot()
{
    if(ui->toolBox->currentIndex()==0){
        ksize = ui->boxKernelSizespinBox->value();
        depth = ui->boxKernelDepthspinBox->value();

        cv::boxFilter(imgSrc,imgDst,
                      depth,
                      cv::Size(ksize, ksize));
    }
    if(ui->toolBox->currentIndex()==1){
        ksize = ui->blurKernelSizespinBox->value();
        cv::blur(imgSrc, imgDst,cv::Size(ksize, ksize));
    }
    if(ui->toolBox->currentIndex()==2){
        ksize = ui->gaussianKernelSizespinBox->value();
        int sigmaX = ui->sigmaXspinBox->value();
        int sigmaY = ui->sigmaYspinBox->value();
        cv::GaussianBlur(imgSrc,imgDst, cv::Size(ksize, ksize),sigmaX, sigmaY);
    }
//    cv::imshow("a", imgSrc);
    cv::cvtColor(imgDst,imgDstRGB,cv::COLOR_BGR2RGB);
    QImage qImg = QImage((const unsigned char*)(imgDstRGB.data),
                         imgDstRGB.cols,imgDstRGB.rows,
                         imgDstRGB.cols * imgDstRGB.channels(),
                         QImage::Format_RGB888);
    ui->showImage->setPixmap(QPixmap::fromImage(qImg));
    ui->showImage->resize(ui->showImage->pixmap()->size());
}

void LinearFilter::LinearFilter_Save_Slot()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save Image",
                                                    QDir::homePath(),
                                                    tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));
    if(fileName.isEmpty())
        return;
    std::string path = fileName.toStdString();
    cv::imwrite(path, imgDst);
}

/*---------------------SAVE------------------------*/

