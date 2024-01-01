#include "openScene.h"
#include "settingScene.h"
#include "profile.h"
#include "newscene1.h"
#include "AudioControl.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"//音频头文件

#include"playerScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //创建开始界面背景
    createBackground();
    //点击按钮触发
    createMenuButtons();

    return true;
}

//创建背景函数
void StartScene::createBackground()
{
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景精灵
    auto backgroundSprite_1 = Sprite::create("SSS.jpg");
    if (backgroundSprite_1 != NULL)
    {
        // 设置背景精灵的位置
        backgroundSprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // 缩放背景以填充屏幕
        float scaleX = visibleSize.width / backgroundSprite_1->getContentSize().width;
        float scaleY = visibleSize.height / backgroundSprite_1->getContentSize().height;
        backgroundSprite_1->setScale(scaleX, scaleY);

        // 将背景精灵添加到场景中
        this->addChild(backgroundSprite_1, 0);
    }
}

//按键响应

//点击按钮触发下一场景
void StartScene::createMenuButtons()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    createAndAddButton("t1.png", "t1_click.jpg", Vec2(origin.x + visibleSize.width * 0.5 - 5, origin.y + visibleSize.height * 0.25 - 5), 0.85, []() {
        // 处理开始游戏按钮点击事件
        auto scene = playerScene::createScene();
    Director::getInstance()->replaceScene(scene);

        });

    createAndAddButton("t3.png", "t3_click.jpg", Vec2(origin.x + visibleSize.width * 0.2, origin.y + visibleSize.height * 0.26), 0.8, []() {
        // 处理加入房间按钮点击事件
        auto scene = newscene1::createScene();
    Director::getInstance()->replaceScene(scene);
        });

    createAndAddButton("t2.png", "t2_click.jpg", Vec2(origin.x + visibleSize.width * 0.79, origin.y + visibleSize.height * 0.26), 0.8, []() {
        // 处理创建房间按钮点击事件
        auto scene = newscene1::createScene();
    Director::getInstance()->replaceScene(scene);
        });

    createAndAddButton("setting.png", "setting_click.jpg", Vec2(origin.x + visibleSize.width * 0.067, origin.y + visibleSize.height * 0.882), 0.8, []() {
        // 处理设置按钮点击事件
        // 创建下一个场景
        auto settingScene = SettingScene::create();
    // 切换到下一个场景，使用淡出效果
    cocos2d::Director::getInstance()->pushScene(TransitionFade::create(1.0, settingScene, Color3B(255, 255, 240)));
        });

    createAndAddButton("profile.png", "profile_click.jpg", Vec2(origin.x + visibleSize.width * 0.93, origin.y + visibleSize.height * 0.882), 0.8, []() {
        // 处理profile按钮点击事件
         // 创建下一个场景
        auto settingScene = Profile::create();
    // 切换到下一个场景，使用淡出效果
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, settingScene, Color3B(255, 255, 240)));
        });
}

//创建点击按钮
void StartScene::createAndAddButton(const string& normalImage, const string& selectedImage, const Vec2& position, float scale, const function<void()>& callback)
{
    //设置按钮状态
    auto button = ui::Button::create(normalImage, selectedImage);
    button->setScale(scale);
    button->setPosition(position);
    addChild(button, 1);

    //创建点击事件
    button->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // 播放点击音效
            AudioControl::getInstance()->playClickSoundEffect();
            callback();
        }
        });
}

void StartScene::onEnter() {
    Scene::onEnter();
    // 检查是否处于静音状态
    if (!AudioControl::getInstance()->isMuted()) {
        // 如果没有静音，重新开始播放背景音乐
        AudioControl::getInstance()->playBackgroundMusic("BM.mp3", true);
    }
}

void StartScene::onExit() {
    Scene::onExit();
}

