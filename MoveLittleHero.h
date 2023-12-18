#pragma once
#ifndef __LITTLE_HERO_H__ 
#define __LITTLR_HERO_H__

#include "cocos2d.h" 

class littleHero : public cocos2d::Sprite {
public:
    //构造函数
    littleHero();

    // 静态创建小小英雄
    static littleHero* create(const std::string& filename);

    // 启用或停用鼠标控制,enabled 为 true 时启用鼠标控制，为 false 时禁用
    void enableMouseControl(bool enabled);

    //移动小小英雄到指定位置
    void moveHeroToLocation(const cocos2d::Vec2& location, const int& numPlayer);

    //加载玩家和小小英雄的图片
    void  preloadWalkingFrames(const int& numPlayer);

    // 停止行走动画
    void stopHeroAction(const int& numPlayer);

    //不同玩家的编号
    int numPlayer;

private:
    //鼠标监听器初始
    cocos2d::EventListenerMouse* _mouseListener = nullptr;

    // 初始化鼠标事件监听器
    void initMouseListener();

    //鼠标按下时的参数设置
    void setMouseParameter(cocos2d::Event* event);
};

#endif 