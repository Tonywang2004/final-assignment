#include "transitionScene.h"
#include "openScene.h"
USING_NS_CC;

Scene* Transition::createScene()
{
    return Transition::create();
}


bool Transition::init()
{
    if (!Scene::init())
    {
        return false;
    }
    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

     // 创建背景精灵
    auto backgroundSprite_1 = Sprite::create("background_b.png");
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

    // 创建一个定时器，延迟一段时间后切换到下一个场景
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(Transition::switchToNextScene), 2.0f); // 2.0秒延迟
    return true;
}
void Transition::switchToNextScene(float dt)
{
    // 创建下一个场景
    auto newScene = StartScene::create();
    // 切换到下一个场景，使用淡出效果
    Director::getInstance()->replaceScene(TransitionFade::create(1.0, newScene, Color3B(255, 255, 240)));
}


