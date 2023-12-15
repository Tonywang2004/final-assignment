#include "ApplyLittleHero.h"
#include "MoveLittleHero.h"
USING_NS_CC;

Scene* ApplyLittleHero::createScene()
{
    return  ApplyLittleHero::create();
}

bool  ApplyLittleHero::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景精灵
    auto backgroundSprite = Sprite::create("GameBack.jpg");
    if (backgroundSprite != NULL)
    {
        // 设置背景精灵的位置
        backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // 缩放背景以填充屏幕
        float scaleX = visibleSize.width / backgroundSprite->getContentSize().width;
        float scaleY = visibleSize.height / backgroundSprite->getContentSize().height;
        backgroundSprite->setScale(scaleX, scaleY);

        // 将背景精灵添加到场景中
        this->addChild(backgroundSprite, 0); 
    }


    /*以上场景仅为示例，需更改*/
    /*以下为小小英雄移动部分*/

    // 创建小小英雄
    auto hero = littleHero::create("LittlePlayer_1_0.png"); 
    if (hero) {
        hero->setPosition(Vec2(visibleSize.width / 2.8 + origin.x, visibleSize.height / 2.8 + origin.y)); // 设置英雄的位置
        hero->setScale(0.5);
        this->addChild(hero); // 将英雄添加到场景中
    }
    //加载小小英雄的动作帧图片,该步必不可少
    preloadWalkingFrames();

    // 在对局开始,启用小小英雄移动
    hero->enableMouseControl(true);

    // 在游戏准备阶段，关闭小小英雄移动
    //hero->enableMouseControl(false);
 

    return true;
}

//加载行走动作帧，如果要增加小小精灵，注意该函数
void  ApplyLittleHero::preloadWalkingFrames() {
    // 写这段代码时的屏幕分辨率
    const float designWidth = 2560.0f;
    const float designHeight = 1440.0f;

    // 获取当前视窗大小
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    // 计算缩放因子
    float scaleX = visibleSize.width / designWidth;
    float scaleY = visibleSize.height / designHeight;

    // 当前帧图片的尺寸
    float originalFrameWidth = 400.0f;
    float originalFrameHeight = 320.0f;

    // 调整帧尺寸以适应当前分辨率
    float frameWidth = originalFrameWidth * scaleX;
    float frameHeight = originalFrameHeight * scaleY;
    for (int i = 1; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_1_" + std::to_string(i) + ".png"; // 加载帧图片
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
}
