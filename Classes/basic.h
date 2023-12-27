#ifndef BASIC_H
#define BASIC_H
#include "cocos2d.h"
#include"hero.h"
USING_NS_CC;
class ImageSwitcher :public Scene
{
public:
    ImageSwitcher(string a, string b,Hero* hero);
    void switchImage(float dt);
private:
    Sprite* _imageA;
    Sprite* _imageB;
};
#endif