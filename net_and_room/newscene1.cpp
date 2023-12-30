#pragma once
#include "newscene1.h"
#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "ui/UITextField.h"
#include "GameClient.h"
#include <iostream>
USING_NS_CC;
using namespace cocos2d::ui;
Scene* newscene1::createScene()
{
    return newscene1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool newscene1::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();//获取可见大小
    Vec2 origin = Director::getInstance()->getVisibleOrigin();//获取opengl起点

    auto label = Label::createWithTTF("Please input room numbers", "fonts/Marker Felt.ttf", 24);//创建一个标签（内容、字体、字号）
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    
    
    // 创建输入框
    auto editBoxSize = cocos2d::Size(200, 40);
    roomNumberInput = cocos2d::ui::EditBox::create(editBoxSize, cocos2d::ui::Scale9Sprite::create("roomID.png"));
    roomNumberInput->setPosition(cocos2d::Vec2(240, 160));
    roomNumberInput->setFontColor(cocos2d::Color3B::BLACK);
    roomNumberInput->setPlaceHolder("Room Number:");
    roomNumberInput->setMaxLength(10);
    roomNumberInput->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
    this->addChild(roomNumberInput);

    // 创建按钮
    auto enterRoomButton = cocos2d::ui::Button::create();
    enterRoomButton->setTitleText("Create Room");
    enterRoomButton->setPosition(cocos2d::Vec2(240, 120));
    enterRoomButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            this->onEnterRoomButtonClicked();
        }
        });
    this->addChild(enterRoomButton);
    return true;
}
void newscene1::onEnterRoomButtonClicked() {
    const std::string roomNumberString = roomNumberInput->getText();
    // 将输入的字符串转换为char*类型
    const char* cString = roomNumberString.c_str();
    //room_number = std::atoi(roomNumberString.c_str());
    
    TCPClient client;
    client.SendMessage(cString);
    //Director::getInstance()->replaceScene(GameScene1::createScene());
    
    // 这里可以添加进一步的逻辑，如验证房间号或者加入房间等
}





void newscene1::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}