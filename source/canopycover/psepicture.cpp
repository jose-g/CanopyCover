#include "psepicture.h"
#include <iostream>
// Load an image file into img Mat object
void PsePicture::readPicture(std::string fn)
{
    filename=fn;
    img=cv::imread(filename);
}
void PsePicture::readPicture()
{
    img=cv::imread(filename);
}
std::string PsePicture::getFilename()
{
    return filename;
}
void PsePicture::setFilename(std::string fn)
{
    filename=fn;
}
void PsePicture::setOutputFilename(std::string ofn)
{
    outputFilename=ofn;
}
std::string PsePicture::getOutputFilename()
{
    return outputFilename;
}
void PsePicture::setThreshold(float thre)
{
    threshold=thre;
}
float PsePicture::getThreshold()
{
    return threshold;
}
int PsePicture::getHeight()
{
  return img.size().height;
}
int PsePicture::getWidth()
{
  return img.size().width;
}
bool PsePicture::isImageFile(const std::string fn)
{
  cv::Mat imgTmp;
  imgTmp=cv::imread(fn,1);
  return imgTmp.data;
}
int PsePicture::segment()
{
    // validar los inputs antes de ejecutar el proceso
    // implementar manejo de excepciones
    numPx=methodSegmentation(img,imgOut,threshold);
    return numPx;
}
cv::Mat PsePicture::flipImage()
{
  cv::flip(img,img,1);
  return img;
}
void PsePicture::saveOutputImage(std::string ofn)
{
  cv::imwrite(ofn, imgOut);
}
void PsePicture::saveOutputImage()
{
  cv::imwrite(outputFilename, imgOut);
}
void PsePicture::saveImage(std::string fn)
{
  cv::imwrite(fn, img);
}
float PsePicture::methodSegmentation(cv::Mat img,cv::Mat& imgOut,float threshold)
{
  imgOut=img.clone(); // clone the image
  imgOut= CV_RGB(255,255,255); // fill output image with white color
//  cv::imshow("img", img);
//  cv::imshow("imgOut", imgOut);
//  cv::waitKey(2000);
//  std::cout << imgOut.depth() << std::endl;
//  std::cout << imgOut.channels() << std::endl;

//
  int imgHeight=img.size().height;
  int imgWidth=img.size().width;
  int colR,colG;
  //int colB;
  float calc=0.0;
  int contPx=0;
//  FILE *streamRes;
//  streamRes = fopen ("d:\\out.txt","w");
  for(int irow=0;irow<imgHeight;irow++)
  {
      for(int icol=0;icol<imgWidth;icol++)
      {
//          colB=img.at<cv::Vec3b>(irow,icol)[0];
          colG=img.at<cv::Vec3b>(irow,icol)[1];
          colR=img.at<cv::Vec3b>(irow,icol)[2];
          if(colG==0 && colR==0)
          {
            calc=0.0;
          }
          else
          {
            calc=float(colG-colR)/float(colG+colR);
          }
          if(calc>=threshold)
          {
//            fprintf(streamRes,"%d %d %f\n",irow,icol,calc);
            contPx++;
            imgOut.at<cv::Vec3b>(irow,icol)[0]=0; // blue
            imgOut.at<cv::Vec3b>(irow,icol)[1]=255; // green
            imgOut.at<cv::Vec3b>(irow,icol)[2]=0; // red
          }
          else
          {
              imgOut.at<cv::Vec3b>(irow,icol)[0]=0; // blue
              imgOut.at<cv::Vec3b>(irow,icol)[1]=0; // green
              imgOut.at<cv::Vec3b>(irow,icol)[2]=255; // red
          }
      }
  }
//  fclose(streamRes);

//  cv::imshow("output", img);
//  cv::waitKey(2000);
  return contPx;
}
int PsePicture::getNumPx()
{
    return numPx;
}
void PsePicture::setFlag(int flag)
{
    this->flag=flag;
}


float PsePicture::getArea()
{
    return area;
}
float PsePicture::getCc()
{
    return cc;
}

void PsePicture::setArea(float ar)
{
    area=ar;
}
void PsePicture::setCc(float canopy)
{
    cc=canopy;
}
