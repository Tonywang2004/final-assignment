#include "SettingScene.h"
#include "StartScene.h"
#include "RegisterAndLogin.h"
#include "AudioControl.h"
#include "cocos2d.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;

SettingScene::SettingScene() : clickSoundEnabled(true) {}  // 初始化



Scene* SettingScene::createScene()
{
    return SettingScene::create();
}

bool SettingScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    //设置背景
    createSettingBackground("set0.jpg");
    //点击按钮触发
    createMenuButtons_set();

    return true;
}

//创建背景函数
void SettingScene::createSettingBackground(const string& picName)
{
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景精灵
    auto backgroundSprite = Sprite::create(picName);

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
}


//设置屏幕分辨率函数
MenuItemImage* SettingScene::createResolutionButton(const std::string& title, int width, int height) {
    auto button = MenuItemImage::create(
        "button1.png",    // 正常状态的图片
        "button2.jpg",   // 选中状态的图片
        [this, width, height](Ref* sender) {
            this->setResolution(width, height);
        });

    // 创建一个标签放在按钮上
    auto label = Label::createWithTTF(title, "fonts/Marker Felt.ttf", 8);
    if (label != nullptr) {
        label->setPosition(button->getContentSize() / 2);
        button->addChild(label);
    }
    button->setScale(1.2f);

    return button;
}

//分辨率调整函数
void SettingScene::setResolution(int width, int height) {
    Director::getInstance()->getOpenGLView()->setFrameSize(width, height);
}

//分辨率调用函数
void SettingScene::conductSetResolution(){
    // 获取屏幕的实际尺寸
    Size screenSize = Director::getInstance()->getOpenGLView()->getFrameSize();

    // 使用通用函数创建分辨率设置按钮
    auto button1280x720 = createResolutionButton("1280x720", 1280, 720);
    auto button1920x1080 = createResolutionButton("1920x1080", 1920, 1080);
    auto button2560x1440 = createResolutionButton("2560x1440", 2560, 1440);
    auto button2880x1800 = createResolutionButton("2880x1800", 2880, 1800);
    auto button3840x2160 = createResolutionButton("3840x2160", 3840, 2160);

    // 将按钮添加到菜单
    auto menu = Menu::create(button1280x720, button1920x1080, button2560x1440, button2880x1800, button3840x2160, nullptr);
    menu->alignItemsVertically();// 垂直排列按钮
    this->addChild(menu);

    //退出设置界面
    exitTheScene();
}

//回到主界面函数
void SettingScene::goToMainMenu() {
    auto mainMenuScene = StartScene::create(); 
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, mainMenuScene));
}

//退出当前界面按钮函数
void SettingScene::exitTheScene() {
    // 创建退出按钮
    auto exitButton = MenuItemImage::create(
        "exit_button.jpg",  // 正常状态的图片
        "exit_button_click.jpg", // 选中状态的图片
        CC_CALLBACK_0(SettingScene::goToMainMenu, this));
    exitButton->setScale(1.5f);
    // 获取视图的大小和原点
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 设置按钮位置为右下角
    exitButton->setPosition(Vec2(origin.x + visibleSize.width - exitButton->getContentSize().width / 2 - 30,
        origin.y + exitButton->getContentSize().height / 2 + 10));

    // 创建菜单并添加按钮
    auto menu = Menu::create(exitButton, nullptr);
    menu->setPosition(Vec2::ZERO);  // 设置菜单的位置
    this->addChild(menu);
}

// 处理音量滑块的事件
void SettingScene::volumeSliderEvent(Ref* sender, Slider::EventType type) {
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        Slider* slider = dynamic_cast<Slider*>(sender);//滑块移动
        int volume = static_cast<Slider*>(sender)->getPercent(); // 计算新的音量值
        AudioControl::getInstance()->setVolume(volume); // 更新音量
    }
}

// 切换音效静音状态
void SettingScene::muteEffects() {
    clickSoundEnabled = !clickSoundEnabled;  // 切换状态
    AudioControl::getInstance()->setClickSoundEnabled(clickSoundEnabled);
}

//音量调用函数
void SettingScene::conductSetMusic() {
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建音量控制滑块
    auto volumeSlider = Slider::create();
    volumeSlider->loadBarTexture("sliderTrack.png"); // 滑动轨道
    volumeSlider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", ""); // 滑动端点
    volumeSlider->loadProgressBarTexture("sliderProgress.png"); // 滑动进度条
    volumeSlider->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 40));
    volumeSlider->setPercent(AudioControl::getInstance()->getVolume());// 设置滑块的初始音量
    volumeSlider->addEventListener(CC_CALLBACK_2(SettingScene::volumeSliderEvent, this));
    this->addChild(volumeSlider);

    muteSoundCheckBox();//静音函数
    muteEffectCheckBox();//关闭音效函数

    //退出设置界面
    exitTheScene();
}

//静音复选框
void SettingScene::muteSoundCheckBox() {
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建静音提示
    auto mute_sound1 = Sprite::create("SMM1.jpg");
    mute_sound1->setScale(0.4);
    if (mute_sound1 != NULL)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        mute_sound1->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 2 + 15));
        this->addChild(mute_sound1);
    }

    // 创建全局静音复选框
    auto muteAllCheckBox = ui::CheckBox::create("check_box1.png", "check_box2.png");
    muteAllCheckBox->setSelected(AudioControl::getInstance()->isMuted());
    muteAllCheckBox->setPosition(Vec2(origin.x + visibleSize.width / 1.75, origin.y + visibleSize.height / 2 + 15));
    muteAllCheckBox->setScale(1.2f);

    // 设置复选框状态改变
    muteAllCheckBox->addEventListener([=](Ref* sender, ui::CheckBox::EventType type) {
        if (type == ui::CheckBox::EventType::SELECTED) {
            // 当复选框被选中时
            if (!AudioControl::getInstance()->isMuted()) {
                AudioControl::getInstance()->muteAllSounds(); // 静音
            }
        }
        else if (type == ui::CheckBox::EventType::UNSELECTED) {
            // 当复选框未被选中时
            if (AudioControl::getInstance()->isMuted()) {
                AudioControl::getInstance()->unmuteAllSounds(); // 取消静音
            }
        }
        });
    this->addChild(muteAllCheckBox);

}

//关闭音效复选框
void SettingScene::muteEffectCheckBox() {
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //创建关闭音效提示
    auto mute_sound2 = Sprite::create("SMM2.jpg");
    mute_sound2->setScale(0.4);
    if (mute_sound2 != NULL)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        mute_sound2->setPosition(Vec2(origin.x + visibleSize.width / 2.2, origin.y + visibleSize.height / 2 - 20));
        this->addChild(mute_sound2);
    }
    // 创建音效复选框
    auto muteEffectsCheckBox = ui::CheckBox::create("check_box1.png", "check_box2.png");
    muteEffectsCheckBox->setSelected(AudioControl::getInstance()->isClickSoundEnabled());
    muteEffectsCheckBox->setPosition(Vec2(origin.x + visibleSize.width / 1.75, origin.y + visibleSize.height / 2 - 20));
    muteEffectsCheckBox->setScale(1.2f);

    // 设置复选框状态改变
    muteEffectsCheckBox->addEventListener([=](Ref* sender, ui::CheckBox::EventType type) {
        if (type == ui::CheckBox::EventType::SELECTED) {
            // 当复选框被选中时
            clickSoundEnabled = !clickSoundEnabled;  // 切换状态
            AudioControl::getInstance()->setClickSoundEnabled(clickSoundEnabled);
        }
        else if (type == ui::CheckBox::EventType::UNSELECTED) {
            // 当复选框未被选中时
            clickSoundEnabled = !clickSoundEnabled;  // 切换状态
            AudioControl::getInstance()->setClickSoundEnabled(clickSoundEnabled);
        }
        });

    this->addChild(muteEffectsCheckBox);
}

//其他设置函数
void SettingScene::otherSetScene() {
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //退出设置界面
    exitTheScene();

    // 创建退出登陆按钮
    auto exitLoginButton = ui::Button::create("exit_login1.jpg", "exit_login2.jpg");
    exitLoginButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 15));
    exitLoginButton->setScale(2.0f);
    addChild(exitLoginButton);

    exitLoginButton->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            auto initScene = RegisterAndLogin::create();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, initScene));
        }
        });
}

//创建点击按钮
void SettingScene::createAndAddButton_set(const string& normalImage, const string& selectedImage, const Vec2& position, float scale, const function<void()>& callback)
{
    auto button = ui::Button::create(normalImage, selectedImage);
    button->setScale(scale);
    //button->setPosition(Vec2(getContentSize().width * position.x, getContentSize().height * position.y));
    button->setPosition(position);
    addChild(button, 3);

    button->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // 播放点击音效
            AudioControl::getInstance()->playClickSoundEffect();
            callback();
        }
        });
}

//点击按钮触发下一场景
void SettingScene::createMenuButtons_set()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    createAndAddButton_set("setA1.jpg", "", Vec2(origin.x + visibleSize.width * 0.218, origin.y + visibleSize.height * 0.708), 0.9, [this]() {
        this->createSettingBackground("set1.jpg");
        // 分辨率设置
       this->conductSetResolution();
        });

    createAndAddButton_set("setA2.jpg", "", Vec2(origin.x + visibleSize.width * 0.218, origin.y + visibleSize.height * 0.526), 0.7, [this]() {
        this->createSettingBackground("set2.jpg");
        // 音量设置
        conductSetMusic();
        });

    createAndAddButton_set("setA3.jpg", "", Vec2(origin.x + visibleSize.width * 0.225, origin.y + visibleSize.height * 0.385), 1.0, [this]() {
        this->createSettingBackground("set3.jpg");
        //其他设置
        otherSetScene();
        });
}

