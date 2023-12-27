#include "profile.h"
#include "StartScene.h"
USING_NS_CC;

Scene* Profile::createScene()
{
    return Profile::create();
}

bool Profile::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建背景精灵
    auto backgroundSprite_1 = Sprite::create("reg.png");
    if (backgroundSprite_1 != NULL)
    {
        // 设置背景精灵的位置
        backgroundSprite_1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // 缩放背景以填充屏幕
        float scaleX = visibleSize.width / backgroundSprite_1->getContentSize().width;
        float scaleY = visibleSize.height / backgroundSprite_1->getContentSize().height;
        backgroundSprite_1->setScale(scaleX, scaleY);

        // 将背景精灵添加到场景中
        this->addChild(backgroundSprite_1, 0); // 0 表示层级，确保背景在最底层
    }

    // 创建退出按钮
    auto exitButton = MenuItemImage::create(
        "exit_button.jpg",  // 正常状态的图片
        "exit_button_click.jpg", // 选中状态的图片
        CC_CALLBACK_0(Profile::goToMainMenu, this));
    exitButton->setScale(1.2f);

    // 设置按钮位置为右下角
    exitButton->setPosition(Vec2(origin.x + visibleSize.width - exitButton->getContentSize().width / 2 - 24,
        origin.y + exitButton->getContentSize().height / 2 + 3));

    // 创建菜单并添加按钮
    auto menu = Menu::create(exitButton, nullptr);
    menu->setPosition(Vec2::ZERO);  // 设置菜单的位置
    this->addChild(menu);

    return true;
}
//回到主界面函数
void Profile::goToMainMenu() {
    auto mainMenuScene = StartScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, mainMenuScene));
}