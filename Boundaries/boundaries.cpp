#include "boundaries.h"
#include "ui_boundaries.h"

Boundaries::Boundaries(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Boundaries)
{
    ui->setupUi(this);
    /* 功能说明 */
    // Instructions for Canny
    ui->Canny_Page->setToolTip("Canny边缘检测算子是John F.Canny于1986年开发出来的一个多级边缘检测算法，\n"
                               "大体步骤：1、消除噪声；2、计算梯度幅值和方向；3、非极大值抑制(排除非边缘\n"
                               "仅仅保留了一些细线条);4、滞后阈值(需要两个阈值，低和高，若高于高阈值，保留\n"
                               "为边缘，低于低阈值，排除， 处于高低之间，该像素仅仅在连接到一个高于高阈值的\n"
                               "像素时被保留)");
    ui->threshold1Label->setToolTip("第一个滞后性阈值");
    ui->Threshold1DoubleSpinbox->setMinimum(0.0);
    ui->Threshold1DoubleSpinbox->setMaximum(100.0);
    ui->Threshold1DoubleSpinbox->setValue(3.0);

    ui->threshold2Label->setToolTip("第二个滞后性阈值");
    ui->Threshold2DoubleSpinbox->setMinimum(0.0);
    ui->Threshold2DoubleSpinbox->setMaximum(100.0);
    ui->Threshold2DoubleSpinbox->setValue(9.0);

    ui->apertureSizeLabel->setToolTip("应用Sobel算子的孔径大小，其默认值为3");
    ui->apertureIntSizeSpinbox->setMinimum(1);
    ui->apertureIntSizeSpinbox->setMaximum(99);
    ui->apertureIntSizeSpinbox->setSingleStep(2);
    ui->apertureIntSizeSpinbox->setValue(3);

    ui->l2GradientLabel->setToolTip("计算图像梯度幅值的标识，默认False");
    ui->l2GradientcomboBox->setCurrentIndex(1);






    /* CONNECT */
    QObject::connect(ui->openButton, SIGNAL(clicked(bool)),
                     this, SLOT(Boundaries_Open_Slot()));
    QObject::connect(ui->runButton,SIGNAL(clicked(bool)),
                     this,SLOT(Boundaries_Run_Slot()));

}

Boundaries::~Boundaries()
{
    delete ui;
}

void Boundaries::Boundaries_Open_Slot()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open Image",
                                                    QDir::homePath(),
                                                    tr("(*.png *.jpg *.jpeg *.bmp)"));
    if (fileName.isEmpty())
        return;
    std::string path = fileName.toStdString();
    imgSrc = cv::imread(path);
    cv::cvtColor(imgSrc, imgSrcGray,cv::COLOR_BGR2GRAY);
    cv::Mat imgSrcRGB;
    cv::cvtColor(imgSrc, imgSrcRGB, cv::COLOR_BGR2RGB);

//    QImage qImg;
//    convert2QtImg(imgSrcRGB, qImg);

    QImage qImg = QImage((const unsigned char*)(imgSrcRGB.data),
                         imgSrcRGB.cols,
                         imgSrcRGB.rows,
                         imgSrcRGB.cols * imgSrcRGB.channels(),
                         QImage::Format_RGB888);

    ui->cannyShowLabel->setPixmap(QPixmap::fromImage(qImg));
    ui->cannyShowLabel->resize(ui->cannyShowLabel->pixmap()->size());

}

void Boundaries::Boundaries_Run_Slot()
{
    // Canny
    if(ui->toolBox->currentIndex()==0){
        bool L2Gradient;
        if (ui->l2GradientcomboBox->currentText()=="True")
            L2Gradient = true;
        else
            L2Gradient = false;
        // 对imgSrcGray使用3x3内核降噪
        cv::blur(imgSrcGray, imgEdges, cv::Size(3,3));
        // 运行Canny算子
        cv::Canny(imgEdges, imgEdges,
                  ui->Threshold1DoubleSpinbox->value(),
                  ui->Threshold2DoubleSpinbox->value(),
                  ui->apertureIntSizeSpinbox->value(),
                  L2Gradient);


        cv::imshow("Edges", imgEdges);
        // 显示彩色检测图
        cv::Mat colorEdges, dst;
        colorEdges = imgSrc.clone();
        dst.create(colorEdges.size(),colorEdges.type());
        // dst内所有元素置0
        dst = cv::Scalar::all(0);
        colorEdges.copyTo(dst, imgEdges);
        cv::imshow("Color", dst);



    }
}
