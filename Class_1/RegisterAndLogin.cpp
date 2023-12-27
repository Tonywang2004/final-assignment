#include "RegisterAndLogin.h"
#include "transitionScene.h"
#include "ui/CocosGUI.h" //使用UI组件
#include "audio/include/AudioEngine.h"//音频头文件
#include <iostream>
#include <string>

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

Scene* RegisterAndLogin::createScene()
{
    return RegisterAndLogin::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool RegisterAndLogin::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    //退出游戏按钮
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(RegisterAndLogin::menuCloseCallback, this));

    if (closeItem == NULL ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu0 = Menu::create(closeItem, NULL);
    menu0->setPosition(Vec2::ZERO);
    this->addChild(menu0, 1);
  

    // 创建背景精灵
    auto backgroundSprite = Sprite::create("bg.png");
    if (backgroundSprite != NULL)
    {
        // 设置背景精灵的位置
        backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
       
        // 缩放背景以填充屏幕
        float scaleX = visibleSize.width / backgroundSprite->getContentSize().width;
        float scaleY = visibleSize.height / backgroundSprite->getContentSize().height;
        backgroundSprite->setScale(scaleX, scaleY);

        // 将背景精灵添加到场景中
        this->addChild(backgroundSprite, 0); //确保背景在最底层
    }
    //加入同济大学logo
    auto tj_sprite = Sprite::create("tju.jpg");
    tj_sprite->setScale(0.5); 
    if (tj_sprite != NULL)
    {
        // position the sprite on the center of the screen
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        tj_sprite->setPosition(Vec2(float(origin.x + visibleSize.width * 0.85 + 3), origin.y + visibleSize.height - 75));
        // add the sprite as a child to this layer
        this->addChild(tj_sprite, 1);
    }

    // add "password" splash screen"
   auto sprite = Sprite::create("password.jpg");
   sprite->setScale(2.5);  //扩大
    if (sprite != NULL)
    {
        // position the sprite on the center of the screen
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        sprite->setPosition(Vec2(float(origin.x + visibleSize.width * 0.85+3), origin.y + visibleSize.height - 150));
      
        // add the sprite as a child to this layer
        this->addChild(sprite, 1);
    }

    // 调用创建登录界面的函数
    this->createLogin();

    //创建设置按钮
    auto setting = createButton("setting_icon.png", "setting_icon_click.png", Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.95),
        2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // 播放音效
                int audioId = AudioEngine::play2d("click_sound.mp3", false, 1.0f);
                // 创建下一个场景
                auto newScene = SettingScene::create();
                // 切换到下一个场景
                cocos2d::Director::getInstance()->pushScene(TransitionFade::create(1.0, newScene, Color3B(255, 255, 240)));
            }
        });

    return true;
}

//创建输入框
ui::EditBox* RegisterAndLogin::createInputBox(const Size& size, const Vec2& position, bool isPassword) {
    auto inputBox = ui::EditBox::create(size, ui::Scale9Sprite::create("button1.png"));
    inputBox->setPosition(position);
    if (isPassword) {
        inputBox->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    }
    this->addChild(inputBox, 2);
    return inputBox;
}

//创建按钮
ui::Button* RegisterAndLogin::createButton(const string& normalImage, const string& selectedImage, const Vec2& position,
    const float& scale, const std::function<void(Ref*, ui::Widget::TouchEventType)>& callback) {
    auto button = ui::Button::create(normalImage, selectedImage);
    button->setPosition(position);
    button->setScale(scale);
    button->addTouchEventListener(callback);
    this->addChild(button, 2);
    return button;
}

//登录函数
void RegisterAndLogin::createLogin() {
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 计算右侧位置
    float rightSideX = float(origin.x + visibleSize.width * 0.85 + 6);

    // 创建账号输入框并设置大小和位置，同时输入账号
    auto accountBox = createInputBox(Size(100, 14), Vec2(rightSideX, origin.y + visibleSize.height - 136));
    auto passwordBox = createInputBox(Size(100, 14), Vec2(rightSideX, origin.y + visibleSize.height - 157), true);
    //创建登录按钮
    auto loginButton = createButton("button_qd_00.png", "button_qd_01.png",
        Vec2(rightSideX - 50, origin.y + visibleSize.height - 200), 2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // 播放音效
                int audioId = AudioEngine::play2d("click_sound.mp3", false, 1.0f);
                string account = accountBox->getText();
                string password = passwordBox->getText();

                // 从本地存储中获取与账号对应的密码
                string storedPassword = UserDefault::getInstance()->getStringForKey(account.c_str(), "");

                // 检查账号密码
                if (!storedPassword.empty() && password == storedPassword) {
                    // 账号密码正确,创建下一个场景
                    auto newScene = Transition::createScene();
                    // 切换到下一个场景
                    Director::getInstance()->replaceScene(TransitionFade::create(1.0, newScene, Color3B(255, 255, 240)));
                }
                else {
                    //账号密码错误，重新输入
                    accountBox->setText("");
                    passwordBox->setText("");
                    // 创建一个输入错误提示
                    auto registerButton = ui::Button::create("wrongInput2.jpg", "wrongInput2.jpg");
                    registerButton->setScale(float(0.12));  //缩小
                    registerButton->setPosition(Vec2(rightSideX - 3, origin.y + visibleSize.height - 170));
                    this->addChild(registerButton, 2);
                }
            }
        });

    //创建取消按钮
    auto exitButton = createButton("button_qx_00.png", "button_qx_01.png", Vec2(rightSideX + 30, origin.y + visibleSize.height - 200),
        2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // 播放音效
                int audioId = AudioEngine::play2d("click_sound.mp3", false, 1.0f);
                // 清空账号和密码输入框
                accountBox->setText("");
                passwordBox->setText("");
            }
        });

    //进行注册
    // 创建一个注册界面切换按钮
    auto registerButton = createButton("rigister.jpg", "rigister.jpg", Vec2(rightSideX - 5, origin.y + visibleSize.height - 230),
        0.2, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // 播放音效
                int audioId = AudioEngine::play2d("click_sound.mp3", false, 1.0f);
                //进入注册函数
                this->createRegistration();
            }
        });
}

//注册函数
void RegisterAndLogin::createRegistration() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // 清除场景中的所有子节点，以准备新的界面
    this->removeAllChildren();

    //创建新背景
    auto registerBackground = Sprite::create("reg.png");
    registerBackground->setScale(4);
    registerBackground->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 20));
    this->addChild(registerBackground, 0);


    // 创建一个账号输入框并输入账号
    auto accountInput = ui::EditBox::create(Size(200, 40), ui::Scale9Sprite::create("button1.png"));
    accountInput->setScale(float(0.8));
    accountInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 25));
    // 设置输入框的提示文本
    accountInput->setPlaceHolder("ACCOUNT");
    this->addChild(accountInput, 1);

    // 创建一个密码输入框并输入密码，此处没有使密码不可见
    auto passwordInput = ui::EditBox::create(Size(200, 40), ui::Scale9Sprite::create("button1.png"));
    passwordInput->setScale(float(0.8));
    passwordInput->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 35));
    // 设置密码输入框的提示文本
    passwordInput->setPlaceHolder("PASSWORD");
    this->addChild(passwordInput, 1);

    // 创建确认按钮
    auto loginButton_1 = createButton("button_qd_00.png", "button_qd_01.png", Vec2(float(visibleSize.width / 2 - 45), visibleSize.height / 2 - 100)
        , 2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // 播放音效
                int audioId = AudioEngine::play2d("click_sound.mp3", false, 1.0f);
                // 获取输入的用户名和密码
                string username = accountInput->getText();
                string password = passwordInput->getText();

                // 将用户名和密码保存到本地存储
                UserDefault::getInstance()->setStringForKey(username.c_str(), password);

                if (type == ui::Widget::TouchEventType::ENDED) {
                    //清除当前界面
                    this->removeAllChildren();
                    //返回登录界面
                    this->init();
                }
            }
        });

    // 创建取消按钮
    auto exitButton_1 = createButton("button_qx_00.png", "button_qx_01.png", Vec2(float(visibleSize.width / 2 + 25), visibleSize.height / 2 - 100)
        , 2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                // 播放音效
                int audioId = AudioEngine::play2d("click_sound.mp3", false, 1.0f);
                //清除当前界面，返回登录界面
                this->removeAllChildren();
                this->init();
            }
        });
}

//菜单回调
void RegisterAndLogin::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

//切换场景
void RegisterAndLogin::menuPlayCut(Ref* pSender)
{
    // 创建下一个场景
    auto newScene = Transition::create();
    // 切换到下一个场景
    Director::getInstance()->replaceScene(newScene);
}
