#ifndef PSECANOPYCOVER_H
#define PSECANOPYCOVER_H

class pseCanopyCover
{
public:
    pseCanopyCover(int rullenpx=0,float rullencm=0.0,float pd=0.0,float rd=0.0,int npxp=0,int npx=0):sizeRulePx(rullenpx),sizeRuleCm(rullencm),plantDist(pd),rowDist(rd),plantxPic(npxp),numPx(npx)
    {
        cc=0.0;
        area=0.0;
    }
    int getRulerLengthPx();
    int getRulerLengthCm();
    float getPlantDistance();
    float getRowDistance();
    int getNumPlantxPicture();
    float getCc();
    float getArea();
    int getNumPx();
    void setRulerLengthPx(int);
    void setRulerLengthCm(int);
    void setPlantDistance(float);
    void setRowDistance(float);
    void setNumPlantxPicture(int);
    void setNumPx(int);
    float calculateCc();
    float calculateCc(float plantDist,float rowDist,int plantxPic);
    float calculateArea();
    float calculateArea(int sizeRulePx,float sizeRuleCm,int numPx);
    void clone(pseCanopyCover*);
    void clear();
private:
    int sizeRulePx;
    float sizeRuleCm;
    float plantDist;
    float rowDist;
    int plantxPic;
    float cc;
    float area;
    int numPx;
    float methodCalculateArea(int sizeRulePx,float sizeRuleCm,int numPx);
    float methodCalculateCc(float plantDist,float rowDist,int plantxPic);
};
#endif // PSECANOPYCOVER_H
