#include "clsmngpictures.h"
//
// constructor
ClsMngPictures::ClsMngPictures()
{
     cc=std::make_shared<pseCanopyCover>();
     outputDir="";
     threshold=0.0;
}

// setter methods
void ClsMngPictures::setFilename(int index,std::string fn)
{
    pic.at(index)->setFilename(fn);
}

void ClsMngPictures::setOutputFilename(int index,std::string fn)
{
    pic.at(index)->setOutputFilename(fn);
}
void ClsMngPictures::setOutputFilename(std::string odir,std::string prefix)
{
    std::string name;
    for(int index=0;index<(int)pic.size();index++)
    {
          name=pic.at(index)->getFilename();
          const size_t last_slash_idx = name.find_last_of("\\/");
          if (std::string::npos != last_slash_idx)
          {
              name.erase(0, last_slash_idx + 1);
          }
          const size_t idx = odir.find_last_of("\\/");
          int length=odir.length();
          if((int)idx+1==length)
          {
            name=odir+prefix+name;
          }
          else
          {
            name=odir+"//"+prefix+name;
          }
          pic.at(index)->setOutputFilename(name);
    }
}
void ClsMngPictures::setOutputDir(std::string odir)
{
    outputDir=odir;
}
void ClsMngPictures::setThreshold(int index,float thre)
{
    pic.at(index)->setThreshold(thre);
}
void ClsMngPictures::setThreshold(float thre)
{
    for(int index=0;index<(int)pic.size();index++)
    {
        if(pic.at(index)->flag==1) pic.at(index)->setThreshold(thre);
    }
    threshold=thre;
}

void ClsMngPictures::setFlag(int index,int flag)
{
    pic.at(index)->setFlag(flag);
}

void ClsMngPictures::setFlag(int flag)
{
    for(int index=0;index<(int)pic.size();index++)
    {
      pic.at(index)->setFlag(flag);
    }
}

// getter methods
std::string ClsMngPictures::getFilename(int index)
{
    return pic.at(index)->getFilename();
}

std::string ClsMngPictures::getOutputFilename(int index)
{
    return pic.at(index)->getOutputFilename();
}
std::string ClsMngPictures::getOutputDir()
{
    return outputDir;
}

float ClsMngPictures::getThreshold(int index)
{
    return pic.at(index)->getThreshold();
}
float ClsMngPictures::getThreshold()
{
    return threshold;
}
int ClsMngPictures::getHeight(int index)
{
    return pic.at(index)->getHeight();
}

int ClsMngPictures::getWidth(int index)
{
    return pic.at(index)->getWidth();
}

// other methods
int ClsMngPictures::size() // return number of elements of pic vector
{
    return pic.size();
}

void ClsMngPictures::clear()  // delete all elements of pic vector
{
    pic.clear();
    cc->clear();
    threshold=0.0;
    outputDir="";
}

cv::Mat ClsMngPictures::flipImage(int index) // flip an image
{
    return pic.at(index)->flipImage();
}

void ClsMngPictures::addPicture(std::string fn)
{
    pic.push_back(std::make_shared<PsePicture>(fn));
}
void ClsMngPictures::addPicture(std::string fn,bool flag)
{
    pic.push_back(std::make_shared<PsePicture>(fn));
    pic.at(pic.size()-1)->flag=flag;
}
void ClsMngPictures::addPicture(std::vector<std::string> vfn)
{
    for(std::string& fn : vfn)
    {
        pic.push_back(std::make_shared<PsePicture>(fn));
    }
}
void ClsMngPictures::addPicture(std::vector<std::string> vfn,std::vector<bool> flag)
{
    for(std::string& fn : vfn)
    {
        pic.push_back(std::make_shared<PsePicture>(fn));
        if(flag.at(pic.size()-1))
        {
          pic.at(pic.size()-1)->flag=1;
        }
        else
        {
          pic.at(pic.size()-1)->flag=0;
        }

    }
}
void ClsMngPictures::readPicture(int index)
{
    pic.at(index)->readPicture();
}
void ClsMngPictures::readPicture(std::vector<std::string> vfn)
{
    for(std::string& fn : vfn)
    {
        pic.push_back(std::make_shared<PsePicture>(fn));
        pic.at(pic.size()-1)->readPicture();
    }
}
void ClsMngPictures::readPicture()
{
    for(int index=0;index<(int)pic.size();index++)
    {
      if(pic.at(index)->flag==1)
        pic.at(index)->readPicture();
    }
}

void ClsMngPictures::readPicture(std::string fn)
{ // agrega el nombre del archivo al vector de pictures y luego lo lee
    pic.push_back(std::make_shared<PsePicture>(fn));
    pic.at(pic.size()-1)->readPicture();
}
void ClsMngPictures::readPicture(std::vector<std::string> vfn,std::vector<bool> flag)
{
    for(std::string& fn : vfn)
    {
        pic.push_back(std::make_shared<PsePicture>(fn));
        if(flag.at(pic.size()-1))
        {
          pic.at(pic.size()-1)->flag=1;
        }
        else
        {
          pic.at(pic.size()-1)->flag=0;
        }
        if(pic.at(pic.size()-1)->flag==1) pic.at(pic.size()-1)->readPicture();
    }
}
void ClsMngPictures::segment()
{
    for(int index=0;index<(int)pic.size();index++)
    {
          pic.at(index)->segment();
    }
}
void ClsMngPictures::segment(float thre)
{
    for(int index=0;index<(int)pic.size();index++)
    {
        pic.at(index)->setThreshold(thre);
        pic.at(index)->segment();
    }
}
void ClsMngPictures::segment(std::string fn,float thre,std::string ofn)
{
  pic.push_back(std::make_shared<PsePicture>(fn));
  pic.at(pic.size()-1)->readPicture();
  pic.at(pic.size()-1)->setThreshold(thre);
  pic.at(pic.size()-1)->segment();
  pic.at(pic.size()-1)->setOutputFilename(ofn);
  pic.at(pic.size()-1)->saveOutputImage(ofn);
}
void ClsMngPictures::segment(int index)
{
   pic.at(index)->segment();
}

void ClsMngPictures::segment(std::vector<std::string> vfn,std::vector<bool> flag,float thre,std::string ofn,std::string prefix)
{
  for(std::string& fn : vfn)
  {
      pic.push_back(std::make_shared<PsePicture>(fn));
      if(flag.at(pic.size()-1))
      {
        pic.at(pic.size()-1)->flag=1;
      }
      else
      {
        pic.at(pic.size()-1)->flag=0;
      }
      if(pic.at(pic.size()-1)->flag==1)
      {
        pic.at(pic.size()-1)->readPicture();
        pic.at(pic.size()-1)->setThreshold(thre);
        pic.at(pic.size()-1)->setOutputFilename(ofn);
        pic.at(pic.size()-1)->segment();
      }
  }
  saveOutputImage(ofn,prefix);
}
void ClsMngPictures::segment(std::vector<std::string> vfn,float thre,std::string ofn,std::string prefix)
{
  for(std::string& fn : vfn)
  {
      pic.push_back(std::make_shared<PsePicture>(fn));
      pic.at(pic.size()-1)->readPicture();
      pic.at(pic.size()-1)->setThreshold(thre);
      pic.at(pic.size()-1)->setOutputFilename(ofn);
      pic.at(pic.size()-1)->segment();
  }
  saveOutputImage(ofn,prefix);
}
int ClsMngPictures::getNumPx()
{
    int numPx=pic.at(pic.size()-1)->getNumPx();
    return numPx;
}
int ClsMngPictures::getNumPx(int index)
{
    int numPx=pic.at(index)->getNumPx();
    return numPx;
}
std::vector<int> ClsMngPictures::getNumPx(bool all)
{
    std::vector<int> numpx;
    if(all)
    {
        for(int index=0;index<(int)pic.size();index++)
        {
          numpx.push_back(pic.at(index)->getNumPx());
        }
    }
    return numpx;
}
void ClsMngPictures::segment(int index,float thre,std::string ofn,std::string prefix)
{
  readPicture(index);
  setThreshold(index,thre);
  segment(index);
  saveOutputImage(index,ofn,prefix);
}
void ClsMngPictures::segment(int index,float thre,std::string ofn)
{
  readPicture(index);
  setThreshold(index,thre);
  segment(index);
  saveOutputImage(index,ofn);
}

void ClsMngPictures::saveOutputImage()
{
    for(int index=0;index<(int)pic.size();index++)
    {
      if(pic.at(index)->flag==1)
      {
          pic.at(index)->saveOutputImage();
      }
    }
}

void ClsMngPictures::saveOutputImage(int index,std::string odir,std::string prefix)
{
  std::string name=pic.at(index)->getFilename();
  const size_t last_slash_idx = name.find_last_of("\\/");
  if (std::string::npos != last_slash_idx)
  {
      name.erase(0, last_slash_idx + 1);
  }
  const size_t idx = odir.find_last_of("\\/");
  int length=odir.length();
  if((int)idx+1==length)
  {
    name=odir+prefix+name;
  }
  else
  {
    name=odir+"//"+prefix+name;
  }
  pic.at(index)->setOutputFilename(name);
  pic.at(index)->saveOutputImage(name);
}

void ClsMngPictures::saveOutputImage(std::string ofn)
{
   pic.at(pic.size()-1)->setOutputFilename(ofn);
   pic.at(pic.size()-1)->saveOutputImage(ofn);
}

void ClsMngPictures::saveOutputImage(int index,std::string ofn)
{
    pic.at(index)->setOutputFilename(ofn);
    pic.at(index)->saveOutputImage(ofn);
}

void ClsMngPictures::saveOutputImage(std::string odir,std::string prefix)
{
    std::string name;
    for(int index=0;index<(int)pic.size();index++)
    {
      if(pic.at(index)->flag==1)
      {
          name=pic.at(index)->getFilename();
          const size_t last_slash_idx = name.find_last_of("\\/");
          if (std::string::npos != last_slash_idx)
          {
              name.erase(0, last_slash_idx + 1);
          }
          const size_t idx = odir.find_last_of("\\/");
          int length=odir.length();
          if((int)idx+1==length)
          {
            name=odir+prefix+name;
          }
          else
          {
            name=odir+"//"+prefix+name;
          }
          pic.at(index)->setOutputFilename(name);
          pic.at(index)->saveOutputImage(name);
      }
    }
}

void ClsMngPictures::erase(int index)
{
    pic.erase(pic.begin()+index);
}








int ClsMngPictures::getRulerLengthPx()
{
    return cc->getRulerLengthPx();
}

int ClsMngPictures::getRulerLengthCm()
{
    return cc->getRulerLengthCm();
}

float ClsMngPictures::getPlantDistance()
{
    return cc->getPlantDistance();
}
float ClsMngPictures::getRowDistance()
{
    return cc->getRowDistance();
}

int ClsMngPictures::getNumPlantxPicture()
{
    return cc->getNumPlantxPicture();
}

void ClsMngPictures::setRulerLengthPx(int value)
{
    cc->setRulerLengthPx(value);
}

void ClsMngPictures::setRulerLengthCm(int value)
{
    cc->setRulerLengthCm(value);
}

void ClsMngPictures::setPlantDistance(float value)
{
    cc->setPlantDistance(value);
}

void ClsMngPictures::setRowDistance(float value)
{
    cc->setRowDistance(value);
}

void ClsMngPictures::setNumPlantxPicture(int value)
{
    cc->setNumPlantxPicture(value);
}

void ClsMngPictures::setArea(int index,float area)
{
    pic.at(index)->setArea(area);
}

void ClsMngPictures::setCc(int index,float cc)
{
    pic.at(index)->setCc(cc);
}

float ClsMngPictures::getArea(int index)
{
    return pic.at(index)->getArea();
}

float ClsMngPictures::getCc(int index)
{
    return pic.at(index)->getCc();
}

void ClsMngPictures::setNumPx(int numpx)
{
    cc->setNumPx(numpx);
}

float ClsMngPictures::calculateArea()
{
    return cc->calculateArea();
}
float ClsMngPictures::calculateCc()
{
    return cc->calculateCc();
}
