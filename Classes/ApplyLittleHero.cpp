#include "ApplyLittleHero.h"
#include "MoveLittleHero.h"
#include "cocos2d.h"
#include"hero.h"
USING_NS_CC;
Player my_hero;
Player enemy_hero;
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
    auto hero = littleHero::create("LittlePlayer_4_0.png");
    if (hero) {
        hero->setPosition(Vec2(visibleSize.width / 2.8 + origin.x, visibleSize.height / 2.8 + origin.y)); // 设置英雄的位置
        hero->setScale(0.5);
        this->addChild(hero); // 将英雄添加到场景中
    }
    hero->enableMouseControl(true);
    // 在游戏准备阶段，关闭小小英雄移动
    this->schedule([=](float dt) {
        
        }, 1.0f, "time");
    //hero->enableMouseControl(false);
    Hero hero1(1, 1, this),hero2(2,1,this);
    hero1.mine->setPosition(200, 200);
    hero2.mine->setPosition(300, 300);
    this->addChild(hero1.mine);
    this->addChild(hero2.mine);
    my_hero.hero_on_board.push_back(&hero1);
    enemy_hero.hero_on_board.push_back(&hero2);
    hero1.attack(hero1.gettarget(enemy_hero),this,enemy_hero);
    hero2.attack(hero2.gettarget(my_hero), this, my_hero);
    return true;
}

