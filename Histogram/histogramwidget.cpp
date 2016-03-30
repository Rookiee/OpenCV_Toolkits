#include "histogramwidget.h"
#include "ui_histogramwidget.h"

HistogramWidget::HistogramWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistogramWidget)
{
    ui->setupUi(this);
    ui->showLabel->clear();




    /* for H-S Histogram */
    // init the private data member

    ui->d1BinsSpinbox->setMinimum(0);
    ui->d1BinsSpinbox->setMaximum(256);
    ui->d1BinsSpinbox->setValue(256);



    ui->d1MinSpinbox->setMinimum(0);
    ui->d1MinSpinbox->setMaximum(255);
    ui->d1MinSpinbox->setValue(0);



    ui->d1MaxSpinbox->setMinimum(0);
    ui->d1MaxSpinbox->setMaximum(255);
    ui->d1MaxSpinbox->setValue(255);



   /* for H-S Histogram */
    // HUE BIN
    ui->HSBinSpinBox->setMinimum(0);
    ui->HSBinSpinBox->setMaximum(255);
    ui->HSBinSpinBox->setValue(30);
    // Saturation BIN
    ui->HSStaturatioinBinSpinBox->setMinimum(0);
    ui->HSStaturatioinBinSpinBox->setMaximum(255);
    ui->HSStaturatioinBinSpinBox->setValue(32);
    // 饱和对 上限
    ui->HSSaturationMaxDoubleSpinBox->setMaximum(255);
    ui->HSSaturationMaxDoubleSpinBox->setMinimum(0);
    ui->HSSaturationMaxDoubleSpinBox->setValue(255.0);
    // 饱和度 下限
    ui->HSSaturationMinDoubleSpinBox->setMaximum(255);
    ui->HSSaturationMinDoubleSpinBox->setMinimum(0);
    // 色调 上限
    ui->HSHueMaxDoubleSpinBox->setMaximum(179);
    ui->HSHueMaxDoubleSpinBox->setMinimum(0);
    ui->HSHueMaxDoubleSpinBox->setValue(179.0);
    // 色调 下限
    ui->HSHueMinDoubleSpinBox->setMaximum(179);
    ui->HSHueMinDoubleSpinBox->setMinimum(0);;



    /* for RGB Histogram */
    ui->rgbBinSpinbox->setMinimum(0);
    ui->rgbBinSpinbox->setMaximum(255);
    ui->rgbBinSpinbox->setValue(255);

    // Range
    ui->rgbLowRangeDoubleBox->setMinimum(0);
    ui->rgbLowRangeDoubleBox->setMaximum(255);
    ui->rgbLowRangeDoubleBox->setValue(0);

    ui->rgbHighRangeDoubleBox->setMinimum(0);
    ui->rgbHighRangeDoubleBox->setMaximum(255);
    ui->rgbHighRangeDoubleBox->setValue(255);

    QObject::connect(ui->openButton, SIGNAL(clicked(bool)),
                     this, SLOT(HistogramWidget_Open_Slot()));
    QObject::connect(ui->runButton,SIGNAL(clicked(bool)),
                     this, SLOT(HistogramWidget_Run_Slot()));


}

HistogramWidget::~HistogramWidget()
{
    delete ui;
}

void HistogramWidget::HistogramWidget_Open_Slot()
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
    // 打开操作的时候，转为灰度图一份，存入私有变量grayImg, 对于HS colorspace的图像，在函数中定义；
    cv::cvtColor(imgSrc, grayImg, cv::COLOR_BGR2GRAY);
    if (ui->toolBox->currentIndex() == 0) {
        QImage qImg = QImage((const unsigned char *)(grayImg.data),
                             grayImg.cols,
                             grayImg.rows,
                             grayImg.channels() * grayImg.cols,
                             QImage::Format_Grayscale8);
        ui->showLabel->setPixmap(QPixmap::fromImage(qImg));
        ui->showLabel->resize(ui->showLabel->pixmap()->size());
    }
    else {
        cv::cvtColor(imgSrc, srcRGB, cv::COLOR_BGR2RGB);
        QImage qImg = QImage((const unsigned char *)(srcRGB.data),
                             srcRGB.cols,
                             srcRGB.rows,
                             srcRGB.channels() * srcRGB.cols,
                             QImage::Format_RGB888);
        ui->showLabel->setPixmap(QPixmap::fromImage(qImg));
        ui->showLabel->resize(ui->showLabel->pixmap()->size());
    }


}



void HistogramWidget::HistogramWidget_Run_Slot()
{
    if(imgSrc.empty()){
        QMessageBox::information(this, "Notice", "Please load an image firstly!");
        return;
    }
    // Compute histogram
    if(ui->toolBox->currentIndex() == 0){
        cv::Mat histImg = this->getHistogramImageD1();
        QImage qImg = QImage((const unsigned char *)(histImg.data),
                             histImg.cols,
                             histImg.rows,
                             histImg.channels() * histImg.cols,
                             QImage::Format_Grayscale8);
        ui->showLabel->setPixmap(QPixmap::fromImage(qImg));
        ui->showLabel->resize(ui->showLabel->pixmap()->size());
        ui->showLabel->resize(grayImg.cols, grayImg.rows);

        cv::namedWindow("Histogram 1D");
        cv::imshow("Histogram 1D", histImg);
        int wait = cv::waitKey(0);
        if(wait == 27){
            cv::destroyWindow("Histogram 1D");
        }

    }
    if(ui->toolBox->currentIndex() == 1){
        cv::Mat histImg = this->getHistogramImageHS();
        QImage qImg = QImage((const unsigned char *)(histImg.data),
                             histImg.cols,
                             histImg.rows,
                             histImg.channels() * histImg.cols,
                             QImage::Format_Grayscale8);
        ui->showLabel->setPixmap(QPixmap::fromImage(qImg));
        ui->showLabel->resize(ui->showLabel->pixmap()->size());
        ui->showLabel->resize(grayImg.cols, grayImg.rows);

        cv::namedWindow("Histogram HS");
        cv::imshow("Histogram HS", histImg);
        int wait = cv::waitKey(0);
        if(wait == 27){
            cv::destroyWindow("Histogram HS");
        }
    }
    if(ui->toolBox->currentIndex() == 2){
        cv::Mat histImg;
        std::string windowName;
        if(ui->RradioButton->isChecked()){
            histImg = this->getHistogramImageRGB('r');
            windowName = "Red";
            cv::imshow(windowName, histImg);


//            QImage qImg = QImage((const char *)(histImg.data),
//                                 histImg.cols,
//                                 histImg.rows,
//                                 histImg.channels()*histImg.cols,
//                                 QImage::Format_Mono);

        }
        else if(ui->GradioButton->isChecked()){
            histImg = this->getHistogramImageRGB('g');
            windowName = "Green";
            cv::imshow(windowName, histImg);

//            QImage qImg = QImage((const char *)(histImg.data),
//                                 histImg.cols,
//                                 histImg.rows,
//                                 histImg.channels()*histImg.cols,
//                                 QImage::Format_Mono);

        }
        else if(ui->BradioButton->isChecked()){
            histImg = this->getHistogramImageRGB('b');
            windowName = "Blue";
            cv::imshow(windowName, histImg);

//            QImage qImg = QImage((const char *)(histImg.data),
//                                 histImg.cols,
//                                 histImg.rows,
//                                 histImg.channels()*histImg.cols,
//                                 QImage::Format_Mono);

        }
        else
            exit(EXIT_FAILURE);

//        ui->showLabel->setPixmap(QPixmap::fromImage(qImg));
//        ui->showLabel->resize(ui->showLabel->pixmap()->size());
//        ui->showLabel->resize(grayImg.cols, grayImg.rows);

        if (cv::waitKey(0) == 27)
            cv::destroyWindow(windowName);
    }


}

// 计算1D直方图
cv::MatND HistogramWidget::getHistogramD1(const cv::Mat &image)
{
    histSize[0] = ui->d1BinsSpinbox->value();
    hranges[0] = ui->d1MinSpinbox->value();
    hranges[1] = ui->d1MaxSpinbox->value();
//    ranges[0] = hranges;
    const float* ranges[] = {hranges};
    channels[0] = 0;    // by default, look at channel 0
    cv::calcHist(&image,
                 1,     // histogram from 1 image only
                 channels,  // the channel used
                 cv::Mat(),     // no mask is used
                 hist,      // output histogram, a dense or sparse dims-dimensional array
                 1,     //The histogram dimensionality; must be positive and not greater than CV MAX DIMS(=32 in
                        //  the current OpenCV version)
                 histSize,  // The array of histogram sizes in each dimension
                 ranges);
    return hist;
}

// 绘制1D直方图
cv::Mat HistogramWidget::getHistogramImageD1()
{
    hist = this->getHistogramD1(grayImg);
    double maxVal = 0;
    double minVal = 0;
    cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
    // Image on which to display histogram
    cv::Mat histImg(histSize[0], histSize[0],
            CV_8U,cv::Scalar(255));
    // Set highest point at 90% of nbins
    int hpt = static_cast<int>(0.9*histSize[0]);
    // Draw a vertical line for each bin
    for(int h = 0; h < histSize[0]; ++h){
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal*hpt/maxVal);
        // This function draw a line between 2 points
        cv::line(histImg, cv::Point(h,histSize[0]),
                cv::Point(h, histSize[0]-intensity),
                cv::Scalar::all(0));
    }
    return histImg;


}

// Calculate H-S Histogram
cv::MatND HistogramWidget::getHistogramHS(const cv::Mat &image)
{
    // convert to HS colorspace
    cv::Mat hsImage;
    cv::cvtColor(image, hsImage, cv::COLOR_BGR2HSV );

    // 色调和饱和度的BINS
    int hueBinNum = ui->HSBinSpinBox->value();
    int saturationBinNum = ui->HSStaturatioinBinSpinBox->value();
    histSize[0] = hueBinNum;
    histSize[1] = saturationBinNum;

    // 饱和度的取值范围
    float saturationMin = ui->HSSaturationMinDoubleSpinBox->value();
    float saturationMax = ui->HSSaturationMaxDoubleSpinBox->value();
    float saturationRange[] = {saturationMin, saturationMax};

    // Hue的取值范围
    float hueMin = ui->HSHueMinDoubleSpinBox->value();
    float hueMax = ui->HSHueMaxDoubleSpinBox->value();
    float hueRange[] = {hueMin, hueMax};

    // ranges is the parameter need to give the function cv::calcHist()
    // cv的原型中，calcHist的ranges参数是const float* ranges[], 注意const
//    ranges[0] = hueRange;
//    ranges[1] = saturationRange;
    const float* Rranges[] = {hueRange, saturationRange};
    // This (channels) is also different from "getHistogramD1()"
    channels[0] = 0;
    channels[1] = 1;
    // Note: the first one is Image
    cv::calcHist(&hsImage,
                 1,     // histogram from 1 image only
                 channels,  // the channel used
                 cv::Mat(),     // no mask is used
                 hist,      // output histogram, a dense or sparse dims-dimensional array
                 2,     //The histogram dimensionality; must be positive and not greater than CV MAX DIMS(=32 in
                        //  the current OpenCV version)
                 histSize,  // The array of histogram sizes in each dimension
                 Rranges);
    return hist;
}
// Plot H-S Histogram
cv::Mat HistogramWidget::getHistogramImageHS()
{
    hist = this->getHistogramHS(imgSrc);
    // prepare parameters for plotting
    double maxValue = 0;
    cv::minMaxLoc(hist, 0, &maxValue, 0, 0); // 查找数组和子数组的全局最小值和最大值存入maxValue
    int scale = 10;
    cv::Mat histImg = cv::Mat::zeros(histSize[1] * scale, histSize[0] * 10, CV_8UC3);

    // plot by double loops
    for (int hue = 0; hue < histSize[0]; ++hue){
        for(int saturation = 0; saturation < histSize[1]; ++ saturation){
            float binValue = hist.at<float>(hue, saturation); // 直方图直条的值
//            int intensity = cv::Round(binValue*255/maxValue); // 强度
            int intensity = cvRound(binValue*255/maxValue);

            // Ploting
            cv::rectangle(histImg, cv::Point(hue*scale, saturation*scale),
                          cv::Point( (hue+1)*scale-1, (saturation+1)*scale-1),
                          cv::Scalar::all(intensity), cv::FILLED);

        }
    }
    return histImg;
//    cv::namedWindow("H-S Histogram");
    //    cv::imshow("H-S Histogram", histImg);
}






// Calculate RGB Histograms
cv::MatND HistogramWidget::getHistogramRGB(const cv::Mat &imgSrc, const char flag)
{
    // 准备参数
    int bins = ui->rgbBinSpinbox->value();
    int hist_size[] = {bins};
    float lowRange = ui->rgbLowRangeDoubleBox->value();
    float highRange = ui->rgbHighRangeDoubleBox->value();
    float range[]  = {lowRange, highRange};
    const float * ranges[] = {range};

    if (flag == 'b' || flag == 'B'){
        int channel_b[] = {2};
        cv::calcHist(&imgSrc, 1, channel_b, cv::Mat(),blueHist, 1, hist_size, ranges, true, false);
        return blueHist;
    }

    if (flag == 'g' || flag == 'G'){
        int channel_g[] = {1};
        cv::calcHist(&imgSrc, 1, channel_g, cv::Mat(),greenHist, 1, hist_size, ranges, true, false);
        return greenHist;
    }
    if (flag == 'r' || flag == 'R'){
        int channel_r[] = {0};
        cv::calcHist(&imgSrc, 1, channel_r, cv::Mat(),redHist, 1, hist_size, ranges, true, false);
        return redHist;
    }
//    else
//        exit(EXIT_FAILURE);
}

cv::Mat HistogramWidget::getHistogramImageRGB(const char flag)
{
    // 虽然私有成员中已有了redHist, greenHist, blueHist, 这三个变量放在私有成员中保存待以后使用
    // 直接写入私有变量

    redHist = this->getHistogramRGB(imgSrc, 'r');
    greenHist = this->getHistogramRGB(imgSrc, 'g');
    blueHist = this->getHistogramRGB(imgSrc, 'b');
    // 准备参数
    double maxValueRed, maxValueGreen, maxValueBlue;
    cv::minMaxLoc(redHist, 0, &maxValueRed, 0, 0);
    cv::minMaxLoc(greenHist, 0, &maxValueGreen, 0, 0);
    cv::minMaxLoc(blueHist, 0, &maxValueBlue, 0, 0);
    int scale = 1;
    int histHeight = 256;
    cv::Mat histImg = cv::Mat::zeros(histHeight, ui->rgbBinSpinbox->value(), CV_8UC3);

    // Begin plot
    for(int i = 0; i < ui->rgbBinSpinbox->value(); ++i){
        float binValueRed = redHist.at<float>(i);
        float binValueGreen = greenHist.at<float>(i);
        float binValueBlue = blueHist.at<float>(i);

        // 要绘制的高度
        int intensityRed = cvRound(binValueRed*histHeight/maxValueRed);
        int intensityGreen = cvRound(binValueGreen*histHeight/maxValueGreen);
        int intensityBlue = cvRound(binValueBlue*histHeight/maxValueBlue);
        if (flag == 'r' || flag == 'R'){

            cv::rectangle(histImg, cv::Point((i*scale),histHeight-1),
                          cv::Point((i+1)*scale-1, histHeight-intensityRed),
                          cv::Scalar(0,0,255));

        }
        if (flag == 'g' || flag == 'G'){

            cv::rectangle(histImg, cv::Point((i*scale),histHeight-1),
                          cv::Point((i+1)*scale-1, histHeight-intensityGreen),
                          cv::Scalar(0,255,0));

        }
        if (flag == 'b' || flag == 'B'){

            cv::rectangle(histImg, cv::Point((i*scale),histHeight-1),
                          cv::Point((i+1)*scale-1, histHeight-intensityBlue),
                          cv::Scalar(255,0,0));

        }
//        else
//            exit(EXIT_FAILURE);


    }
    return histImg;
}


// Plot RGB Histograms
