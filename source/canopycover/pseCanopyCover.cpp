#include "pseCanopyCover.h"

int pseCanopyCover::getRulerLengthPx()
{
    return sizeRulePx;
}
int pseCanopyCover::getRulerLengthCm()
{
    return sizeRuleCm;
}
float pseCanopyCover::getPlantDistance()
{
    return plantDist;
}
float pseCanopyCover::getRowDistance()
{
    return rowDist;
}
int pseCanopyCover::getNumPlantxPicture()
{
    return plantxPic;
}
float pseCanopyCover::getCc()
{
    return cc;
}
float pseCanopyCover::getArea()
{
    return area;
}
int pseCanopyCover::getNumPx()
{
    return numPx;
}
void pseCanopyCover::setRulerLengthPx(int length)
{
    sizeRulePx=length;
}
void pseCanopyCover::setRulerLengthCm(int length)
{
    sizeRuleCm=length;
}
void pseCanopyCover::setPlantDistance(float pd)
{
    plantDist=pd;
}
void pseCanopyCover::setRowDistance(float rd)
{
    rowDist=rd;
}
void pseCanopyCover::setNumPlantxPicture(int npxp)
{
    plantxPic=npxp;
}
void pseCanopyCover::setNumPx(int npx)
{
    numPx=npx;
}
float pseCanopyCover::calculateCc()
{
    cc=methodCalculateCc(plantDist,rowDist,plantxPic);
    return cc;
}
float pseCanopyCover::calculateCc(float plantDist,float rowDist,int plantxPic)
{
    return methodCalculateCc(plantDist,rowDist,plantxPic);
}
float pseCanopyCover::calculateArea()
{
    area=methodCalculateArea(sizeRulePx,sizeRuleCm,numPx);
    return area;
}
float pseCanopyCover::calculateArea(int sizeRulePx,float sizeRuleCm,int numPx)
{
    return methodCalculateArea(sizeRulePx,sizeRuleCm,numPx);
}
float pseCanopyCover::methodCalculateArea(int sizeRulePx,float sizeRuleCm,int numPx)
{
    return (double(numPx)*sizeRuleCm*sizeRuleCm)/(double(sizeRulePx)*double(sizeRulePx));
}
float pseCanopyCover::methodCalculateCc(float plantDist,float rowDist,int plantxPic)
{
    return (area/(double(plantxPic)*plantDist*rowDist))*100.00;
}
void pseCanopyCover::clone(pseCanopyCover* canopy)
{
    sizeRulePx=canopy->getRulerLengthPx();
    sizeRuleCm=canopy->getRulerLengthCm();
    plantDist=canopy->getPlantDistance();
    rowDist=canopy->getRowDistance();
    plantxPic=canopy->getNumPlantxPicture();
    cc=canopy->getCc();
    area=canopy->getCc();
    numPx=canopy->getNumPx();
}
void pseCanopyCover::clear()
{
    sizeRulePx=0.0;
    sizeRuleCm=0.0;
    plantDist=0.0;
    rowDist=0.0;
    plantxPic=0.0;
}
