#ifndef __NEWSCENE1_SCENE_H__
#define __NEWSCENE1_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UITextField.h"
//提供了创建和使用用户界面元素的类和函数
USING_NS_CC;

class newscene1 : public cocos2d::Scene//继承
{
public:
    static cocos2d::Scene* createScene();//创建场景

    virtual bool init();//初始化

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);//退出程序

    void onEnterRoomButtonClicked();//按钮点击

    void goToMainMenu();//回到主界面
    // implement the "static create()" method manually
    CREATE_FUNC(newscene1);
    
private:
    cocos2d::ui::EditBox* roomNumberInput;//创建输入框
};

#endif // __NEWSCENE1_SCENE_H__