#ifndef __R_AND_L_H__
#define __R_AND_L_H__
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

class RegisterAndLogin : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // 菜单回调
    void menuCloseCallback(cocos2d::Ref* pSender);
    // 切换场景
    void menuPlayCut(cocos2d::Ref* pSender);
    // 用于创建登录界面的函数声明
    void createLogin();
    // 用于创建注册界面的函数声明
    void createRegistration();
    //创建输入框
    ui::EditBox* createInputBox(const Size& size, const Vec2& position, bool isPassword = false);
    //创建按钮
    ui::Button* createButton(const string& normalImage, const string& selectedImage, const cocos2d::Vec2& position,
        const float& scale, const function<void(Ref*, ui::Widget::TouchEventType)>& callback);
    // implement the "static create()" method manually
    CREATE_FUNC(RegisterAndLogin);

   

};

#endif 
