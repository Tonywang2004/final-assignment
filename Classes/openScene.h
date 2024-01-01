#pragma once
#ifndef __START_SCENE_H__
#define __START_SCENE_H__
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"//音频头文件
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::ui;

using namespace std;

class StartScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    //创建背景
    void createBackground();

    //创建菜单按钮
    void createMenuButtons();

    //创建点击按钮
    void createAndAddButton(const string& normalImage, const string& selectedImage, const Vec2& position, float scale, const function<void()>& callback);

    // 重写 onEnter 和 onExit 
    virtual void onEnter() override;
    virtual void onExit() override;

    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);

};

#endif // __MY_NEW_SCENE_H__
