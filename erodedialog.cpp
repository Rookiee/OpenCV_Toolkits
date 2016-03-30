#include "erodedialog.h"
#include "ui_erodedialog.h"
#include "mainwindow.h" // 因为要调用getImageBGR()
#include <QDebug>
ErodeDialog::ErodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErodeDialog)
{
    ui->setupUi(this);

    // 设置控件属性
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(100);
    ui->spinBox->setValue(3);


    QObject::connect(ui->excuteButton,SIGNAL(clicked(bool)),
                     this, SLOT(erode_Excute_Slot()));
    QObject::connect(ui->saveButton, SIGNAL(clicked(bool)),
                     this, SLOT(erode_Save_slot()));

}

ErodeDialog::~ErodeDialog()
{
    delete ui;
}

void ErodeDialog::erode_Excute_Slot()
{
    // 先把原图复制,用于操作
    erodeCopy = erodeImg.clone();
   // 先处理,在考虑:在Opencv显示,还是在Qt显示
    cv::Mat element;
    if(ui->radioRect->isChecked()){
        element = cv::getStructuringElement(cv::MORPH_RECT,
                                                    cv::Size( int(ui->spinBox->value()), int(ui->spinBox->value()) ) );
    }
    else if (ui->radioEllipse->isChecked()){
        element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                                    cv::Size(ui->spinBox->value(), ui->spinBox->value()));
    }
    else if (ui->radioCross->isChecked()){
        element = cv::getStructuringElement(cv::MORPH_CROSS,
                                                    cv::Size(ui->spinBox->value(), ui->spinBox->value()));
    }
    // 腐蚀操作
    cv::erode(erodeCopy, erodeCopy, element);
    // 判断显示方式
    if (ui->radioOpenCV->isChecked()){
        ui->erodeLabel->setText("Show in Opencv Window");


        while(1){
            cv::imshow("Erode", erodeCopy);
            int timeWait = cv::waitKey(0);
            if(timeWait == 27){
                cv::destroyWindow("Erode");
                break;
            }
            else if (timeWait == int('s')){
                QString fileName = QFileDialog::getSaveFileName(this,"Save File",
                                                                QDir::homePath(),
                                                                "Image File (*.png *.jpg *.jpeg *.bmp)");
                if (fileName.isEmpty()) {
                    continue;

                }
                std::string path = fileName.toStdString();
                cv::imwrite(path, erodeCopy);
            }
        }
    }
    else if (ui->radioQt->isChecked()){
        // 转为Qt颜色空间
//        cv::imshow("a", erodeCopy);
        cv::cvtColor(erodeCopy,erodeCopy,cv::COLOR_BGR2RGB);
//        cv::imshow("b", erodeCopy);
        QImage qerodeImg = QImage((const unsigned char*)(erodeCopy.data),
                                  erodeCopy.cols, erodeCopy.rows,
                                  erodeCopy.cols * erodeCopy.channels(),
                                  QImage::Format_RGB888);
//        ui->erodeLabel->clear();
        ui->erodeLabel->setPixmap(QPixmap::fromImage(qerodeImg));
        ui->erodeLabel->resize(ui->erodeLabel->pixmap()->size());
    }
//    erodeCopy = erodeImg.clone();


}
// 只在Qt方式显示的时候保存
void ErodeDialog::erode_Save_slot()
{
    if(ui->radioOpenCV->isChecked()){
        QMessageBox::information(this,"Information","Only work in 'OpenCV Display Manner'");
        return;
    }
    QString saveFileName = QFileDialog::getSaveFileName(this,"Save File",QDir::homePath(),
                                                        tr ("Image File (*.png *.jpg *.jpeg *.bmp)"));
    if(saveFileName.isEmpty())
    {
//        QMessageBox::information(this,"Error Message","Please select a file");
        return;
    }
    cvtColor(erodeCopy,erodeCopy,CV_RGB2BGR);
    std::string savePath = saveFileName.toStdString();
    cv::imwrite(savePath, erodeCopy);
}

void ErodeDialog::setErodeImage(cv::Mat temp)
{
    erodeImg = temp;
}


