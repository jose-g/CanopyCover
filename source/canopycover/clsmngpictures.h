#ifndef CLSMNGPICTURES_H
#define CLSMNGPICTURES_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <algorithm>
#include <memory>
#include "psepicture.h"
#include "pseCanopyCover.h"
class ClsMngPictures
{
public:
    ClsMngPictures();
    ~ClsMngPictures()
    {
//        std::cout << "ClsMngPictures destructor " << std::endl;
        //delete cc;
    }
    void addPicture(std::string);
    void addPicture(std::string,bool);
    void addPicture(std::vector<std::string>);
    void addPicture(std::vector<std::string>,std::vector<bool>);
    // setter methods
    void setFilename(int,std::string);
    void setOutputFilename(int,std::string);
    void setOutputFilename(std::string,std::string prefix="out");
    void setOutputDir(std::string);
    void setThreshold(int,float);
    void setThreshold(float thre);
    void setFlag(int,int);
    void setFlag(int);
    // getter methods
    std::string getFilename(int);
    std::string getOutputFilename(int index=0);
    std::string getOutputDir();
    float getThreshold(int);
    float getThreshold();
    int getHeight(int);
    int getWidth(int);
    // other methods
    int size();
    void clear();
    cv::Mat flipImage(int index);
    void readPicture(int);
    void readPicture(std::string);
    void readPicture(std::vector<std::string>);
    void readPicture();
    void readPicture(std::vector<std::string>,std::vector<bool>);
    void segment(float);
    void segment(int);
    void segment();
    void segment(std::string,float,std::string);
    void segment(std::vector<std::string>,float,std::string,std::string);
    void segment(std::vector<std::string>,std::vector<bool>,float,std::string,std::string);
    void segment(int,float,std::string,std::string);
    void segment(int,float,std::string);
    void saveOutputImage(std::string,std::string);
    void saveOutputImage(int,std::string,std::string);
    void saveOutputImage(int,std::string);
    void saveOutputImage(std::string);
    void saveOutputImage();

    void erase(int);

    int getNumPx();
    int getNumPx(int);
    std::vector<int> getNumPx(bool);

    void setNumPx(int);

    int getRulerLengthPx();
    int getRulerLengthCm();
    float getPlantDistance();
    float getRowDistance();
    int getNumPlantxPicture();

    void setRulerLengthPx(int);
    void setRulerLengthCm(int);
    void setPlantDistance(float);
    void setRowDistance(float);
    void setNumPlantxPicture(int);

    float getArea(int);
    float getCc(int);
    void setArea(int,float);
    void setCc(int,float);
    float calculateArea();
    float calculateCc();
private:
    std::vector<std::shared_ptr<PsePicture>> pic;
    std::shared_ptr<pseCanopyCover> cc;
    float threshold;
    std::string outputDir;
};

#endif // CLSMNGPICTURES_H
