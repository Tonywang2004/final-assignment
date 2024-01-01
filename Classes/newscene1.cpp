#pragma once
#include "newscene1.h"
#include "ui/CocosGUI.h"
#include "openScene.h"
#include "ui/UITextField.h"
#include <iostream>
#include "Roommanager.h"
#include "playerScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
int room_number;//表示用户输入的房间号
Scene* newscene1::createScene()//创建背景
{
    return newscene1::create();
}

// 问题分析
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// 初始化
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
    //创建标签：Please input room numbers
    auto label = Label::createWithTTF("Please input room numbers", "fonts/Marker Felt.ttf", 24);//创建一个标签（内容、字体、字号）
    if (label == nullptr)//错误处理
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // 放置到正中间
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // 添加到当前图层
        this->addChild(label, 1);
    }
    // 创建退出按钮
    auto exitButton = MenuItemImage::create(
        "return.png",  // 正常状态的图片
        "return_h.png", // 选中状态的图片
        CC_CALLBACK_0(newscene1::goToMainMenu, this));
    exitButton->setScale(3.0f);

    // 设置按钮位置为右下角
    exitButton->setPosition(Vec2(origin.x + visibleSize.width - exitButton->getContentSize().width / 0.5,
        origin.y + exitButton->getContentSize().height + 8));

    // 创建菜单并添加按钮
    auto menu = Menu::create(exitButton, nullptr);
    menu->setPosition(Vec2::ZERO);  // 设置菜单的位置
    this->addChild(menu);
    
    // 创建输入框
    auto editBoxSize = cocos2d::Size(200, 40);
    roomNumberInput = cocos2d::ui::EditBox::create(editBoxSize, cocos2d::ui::Scale9Sprite::create("roomID.png"));
    roomNumberInput->setPosition(cocos2d::Vec2(1000, 700));
    roomNumberInput->setScale(4);
    roomNumberInput->setFontColor(cocos2d::Color3B::BLACK);
    roomNumberInput->setPlaceHolder("Room Number:");
    roomNumberInput->setMaxLength(10);
    roomNumberInput->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC);
    this->addChild(roomNumberInput);

    // 创建按钮
    auto enterRoomButton = cocos2d::ui::Button::create();
    enterRoomButton->setTitleText("Create Room");
    enterRoomButton->setScale(4);
    enterRoomButton->setPosition(cocos2d::Vec2(1000, 500));
    enterRoomButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            this->onEnterRoomButtonClicked();//设置点击按钮之后的操作
        }
        });
    this->addChild(enterRoomButton);
    return true;
}
void newscene1::onEnterRoomButtonClicked() {
    //在输入框里输入数字
    const std::string roomNumberString = roomNumberInput->getText();
    // 将输入的字符串转换为int类型
    room_number = std::atoi(roomNumberString.c_str());
    //初始化房间管理器
    RoomManager manager;
    // 寻找房间
    Room* foundroom = manager.getRoom(room_number);

    if (foundroom == nullptr) {//未找到则创建房间
        auto room= manager.createRoom(room_number);
        room->addPlayer(Player0(1, "Player1"));//添加玩家
        
    }
    else {
        foundroom->addPlayer(Player0(1, "Player1"));//添加玩家
    }
    //切换到游戏场景
    auto scene = playerScene::createScene();
    Director::getInstance()->replaceScene(scene);
    
}


//回到主界面函数
void newscene1::goToMainMenu() {
    auto mainMenuScene = StartScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, mainMenuScene));
}


void newscene1::menuCloseCallback(Ref* pSender)//退出程序
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}