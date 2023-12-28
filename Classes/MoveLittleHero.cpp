#include "MoveLittleHero.h"
#include "ApplyLittleHero.h"
#include "cocos2d.h"
#include<vector>

//初始化,确定角色
littleHero::littleHero() : numPlayer(3) {
}

// 静态创建小小英雄
littleHero* littleHero::create(const std::string& filename) {
    littleHero* hero = new littleHero();
    if (hero && hero->initWithFile(filename)) {
        hero->autorelease();
        return hero;
    }
    CC_SAFE_DELETE(hero);
    return nullptr;
}

// 启用或停用鼠标控制,enabled 为 true 时启用鼠标控制，为 false 时禁用
void littleHero::enableMouseControl(bool enabled) {
    if (enabled) {
        if (!_mouseListener) {
            //加载角色图片
            preloadWalkingFrames(numPlayer);
            // 初始化监听器
            initMouseListener();
        }
        // 将监听器添加到事件分发器
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    }
    else {
        if (_mouseListener) {
            // 移除监听器
            _eventDispatcher->removeEventListener(_mouseListener);
        }
    }
}

// 初始化鼠标事件监听器
void littleHero::initMouseListener() {
    _mouseListener = cocos2d::EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(littleHero::setMouseParameter, this);
}

//对移动范围和位置参数设置
void littleHero::setMouseParameter(cocos2d::Event* event) {
    cocos2d::EventMouse* moveToClick = dynamic_cast<cocos2d::EventMouse*>(event);
    if (moveToClick) {
        cocos2d::EventMouse* moveToClick = dynamic_cast<cocos2d::EventMouse*>(event);
        //检查是否为右键点击移动
        if (moveToClick && moveToClick->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT) {
            //获取移动位置的坐标
            cocos2d::Vec2 location = moveToClick->getLocationInView();
            location = cocos2d::Director::getInstance()->convertToGL(location);
            //不知道y轴为什么是反的，此处手动调整
            auto refreshSize = cocos2d::Director::getInstance()->getWinSize();
            location.y = refreshSize.height - location.y;
            // 获取实际分辨率
            cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

            // 编写此处代码时的分辨率为 2560*1440
            cocos2d::Size designSize = cocos2d::Size(2560, 1440);

            // 计算实际分辨率与设计分辨率的缩放比例
            float scaleX = visibleSize.width / designSize.width;
            float scaleY = visibleSize.height / designSize.height;

            // 棋盘在设计分辨率下的位置和大小
            cocos2d::Rect designBoardRect(400,250,1880,1080);

            // 将设计分辨率下的棋盘区域转换为实际分辨率下的区域
            cocos2d::Rect actualBoardRect(
                designBoardRect.origin.x * scaleX,
                designBoardRect.origin.y * scaleY,
                designBoardRect.size.width * scaleX,
                designBoardRect.size.height * scaleY
            );

            if (actualBoardRect.containsPoint(location)) {
                // 如果在有效区域内，移动英雄
                moveHeroToLocation(location, numPlayer);
            }

        }
    }
}

//移动小小精灵
void littleHero::moveHeroToLocation(const cocos2d::Vec2& location, const int& numPlayer) {
    // 停止所有动画
    this->stopHeroAction(numPlayer);

    // 创建行走动画的帧
    cocos2d::Vector<cocos2d::SpriteFrame*> walkFrames;
    for (int i = 0; i <= 7; ++i) {
        //此处可考虑增加几个小小英雄
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; //帧图片
        auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame) {
            walkFrames.pushBack(frame);
        }
    }

    // 创建行走动画
    auto walkAnimation = cocos2d::Animation::createWithSpriteFrames(walkFrames, 0.1f);//每帧0.1s
    auto walkAnimate = cocos2d::Animate::create(walkAnimation);

    // 设置移动动作的持续时间
    float moveDuration = 1.8f;
    auto moveTo = cocos2d::MoveTo::create(moveDuration, location);

    // 计算重复行走动画的次数，以覆盖整个移动时间
    int numRepeats = static_cast<int>(moveDuration / (8 * 0.1f));//总时间除以一套动作的时间
    auto repeatWalkAnimate = cocos2d::Repeat::create(walkAnimate, numRepeats);

    // 使用 Spawn 同时执行移动动作和重复的行走动画
    auto moveAndAnimate = cocos2d::Spawn::createWithTwoActions(moveTo, repeatWalkAnimate);

    // 创建动作完成后的回调，以停止所有动画
    auto callback = cocos2d::CallFunc::create([this, numPlayer]() {
        this->stopHeroAction(numPlayer); // 停止所有动画
        });

    // 将移动动作、行走动画和回调组合成一个序列
    auto sequence = cocos2d::Sequence::create(moveAndAnimate, callback, nullptr);

    // 执行序列动作
    this->runAction(sequence);
}

void littleHero::stopHeroAction(const int& numPlayer) {
    // 停止行走动画，恢复到站立状态的精灵帧
    this->stopAllActions();
    auto frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("LittlePlayer_" + std::to_string(numPlayer) + "_8" + ".png");
    if (frame) {
        this->setSpriteFrame(frame);
    }
}

//加载行走动作帧，如果要增加小小精灵，注意该函数
void  littleHero::preloadWalkingFrames(const int& numPlayer) {
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
    for (int i = 0; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; // 加载player1帧图片
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
    for (int i = 0; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; // 加载player2帧图片
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
    for (int i = 0; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; // 加载player3帧图片
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
    for (int i = 0; i <= 8; ++i) {
        std::string frameName = "LittlePlayer_" + std::to_string(numPlayer) + "_" + std::to_string(i) + ".png"; // 加载player4帧图片
        auto frame = cocos2d::SpriteFrame::create(frameName, cocos2d::Rect(0, 0, frameWidth, frameHeight));
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFrame(frame, frameName);
    }
}