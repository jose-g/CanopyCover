#ifndef PSEPICTURE_H
#define PSEPICTURE_H
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
//#include <opencv/cv.h>
class PsePicture
{
public:
    PsePicture(std::string fn="",float thre=0.0,std::string ofn=""):filename(fn),threshold(thre),outputFilename(ofn)
    {
        numPx=0;
        isImage=false;
        flag=1;
        area=0;
        cc=0;
//        std::cout << "PsePicture constructor " << filename << std::endl;
    }
    ~PsePicture()
    {
//        std::cout << "PsePicture destructor " << filename << std::endl;
    }

    std::string getFilename();
    void setFilename(std::string);
    std::string getOutputFilename();
    int getHeight();
    int getWidth();
    void setThreshold(float);
    float getThreshold();
    int getNumPx();
    float getArea();
    float getCc();

    void readPicture(std::string);
    void readPicture();
    void setOutputFilename(std::string);
    bool isImageFile(const std::string);
    int segment();
    void saveOutputImage(std::string);
    void saveOutputImage();
    void saveImage(std::string);
    cv::Mat flipImage();
    int flag;
    void setFlag(int);
    void setArea(float);
    void setCc(float);
private:
    std::string filename;
    float threshold;
    std::string outputFilename;
    int numPx;
    bool isImage;
    cv::Mat img; // declare the type Mat for image variable
    cv::Mat imgOut; // declare the type Mat for imageProc variable
    float methodSegmentation(cv::Mat image,cv::Mat& imageProc,float threshold);
    float area;
    float cc;
};
#endif // PSEPICTURE_H
