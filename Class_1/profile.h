#pragma once
#ifndef __MY_NEW_SCENE_H__
#define __MY_NEW_SCENE_H__

#include "cocos2d.h"

class Profile : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void goToMainMenu();
    // implement the "static create()" method manually
    CREATE_FUNC(Profile);
};

#endif // __MY_NEW_SCENE_H__
