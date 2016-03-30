#ifndef PUBLICFUNCTIONS_H
#define PUBLICFUNCTIONS_H
#include <opencv2/opencv.hpp>
#include <QImage>
void convert2QtImg(cv::Mat imgSrc, QImage &imgDst){
    imgDst = QImage((const unsigned char *)(imgSrc.data),
                    imgSrc.cols,
                    imgSrc.rows,
                    imgSrc.cols * imgSrc.channels(),
                    QImage::Format_RGB888);
}


#endif // PUBLICFUNCTIONS_H
