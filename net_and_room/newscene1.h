#ifndef __nHELLOWORLD_SCENE_H__
#define __nHELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
//using namespace cocos2d::ui;

class newscene1 : public cocos2d::Scene//ผฬณะ
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onEnterRoomButtonClicked();
    // implement the "static create()" method manually
    CREATE_FUNC(newscene1);
    //void comeback(Ref* temp);
    //void comeback2(Ref* temp);
private:
    //cocos2d::ui::TextField* roomNumberInput;
    cocos2d::ui::EditBox* roomNumberInput;
};

#endif // __nHELLOWORLD_SCENE_H__