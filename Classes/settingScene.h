#pragma once
#ifndef __SRTTING_SCENE_H__
#define __SETTING_SCENE_H__
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"//音频头文件
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

class SettingScene : public cocos2d::Scene
{
    friend class StartScene;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    SettingScene();
    //创建背景函数
    void createSettingBackground(const string& picName);
    // 创建分辨率设置按钮的通用函数
    MenuItemImage* SettingScene::createResolutionButton(const std::string& title, int width, int height);

    // 通用分辨率调整函数
    void setResolution(int width, int height);

    //分辨率调用函数
    void SettingScene::conductSetResolution();



    //回到主界面
    void SettingScene::goToMainMenu();

    //退出当前界面
    void SettingScene::exitTheScene();

    // 音量控制函数
    void volumeSliderEvent(cocos2d::Ref* sender, cocos2d::ui::Slider::EventType type);
    void muteAllSounds();
    void muteEffects();
    //音量调用函数
    void conductSetMusic();

    //点击按钮触发下一场景
    void createMenuButtons_set();
    void createAndAddButton_set(const string& normalImage, const string& selectedImage, const Vec2& position, float scale, const function<void()>& callback);

    //静音复选框函数
    void muteSoundCheckBox();
    //关闭音效复选框函数
    void muteEffectCheckBox();

    //其他
    void SettingScene::otherSetScene();
    // implement the "static create()" method manually
    CREATE_FUNC(SettingScene);

private:
    int backgroundMusicID; // 背景音乐的音频ID
    bool clickSoundEnabled;  // 用于跟踪点击音效的状态

};

#endif 