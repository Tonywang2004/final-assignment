#include "ApplyLittleHero.h"
#include "MoveLittleHero.h"
#include "cocos2d.h"
#include"hero.h"
#include"RegisterAndLogin.h"
#include"settingScene.h"
USING_NS_CC;
using namespace cocos2d::ui;
Player my_hero;
Player enemy_hero;
int isfight=0;
Scene* ApplyLittleHero::createScene()
{
    return  ApplyLittleHero::create();
}
bool fight = 0;
void ApplyLittleHero::update(float delta) {
    // 更新倒计时
    //for (int i=0;i<my_hero.hero_on_board.size();i++)
    //{
    //    my_hero.hero_on_board[i];
    //   // hero->attack(hero->gettarget(enemy_hero), this, enemy_hero);
    //}
    //for (int i = 0; i < enemy_hero.hero_on_board.size(); i++) {
    //    Hero* hero = enemy_hero.hero_on_board[i];
    //    hero->attack(hero->gettarget(my_hero), this, my_hero);
    //}
    if (countdown > 0) {
        countdown -= delta;
        timerLabel->setString(std::to_string((int)countdown));
        //判断fight是否为1，为1时进行攻击，为0时可以移动
        //if (fight == 1)
        //{
        //    for (Hero* hero : my_hero.hero_on_board)
        //    {
        //        hero->attack(hero->gettarget(enemy_hero), this, enemy_hero);
        //    }
        //    for (Hero* hero : enemy_hero.hero_on_board) {
        //        hero->attack(hero->gettarget(my_hero), this, my_hero);
        //    }
        //}
    }
    else {
        // 倒计时结束时执行的操作
        countdown = countdown_max;
        timerLabel->setString(std::to_string((int)countdown));
        // 例如：结束游戏、改变场景等
        fight = (fight == 0 ? 1 : 0);
        if (fight == 1)
        {
            //新建场景
            auto newScene = SettingScene::create();
            //Director::getInstance()->pushScene();
            //退出场景
            //Director::getInstance()->popScene();
        }
    }
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
    auto backgroundSprite = Sprite::create("pink_1.jpg");
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
    countdown = 30.0f;
    // 创建并添加标签
    timerLabel = Label::createWithSystemFont(std::to_string((int)countdown), "Arial", 24);
    timerLabel->setColor(Color3B(255, 100, 0));
    timerLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
    Director::getInstance()->getVisibleSize().height));
    //添加倒计时标签
    this->addChild(timerLabel);

    /*以上场景仅为示例，需更改*/
    /*以下为小小英雄移动部分*/

    // 创建小小英雄
    auto hero = littleHero::create("LittlePlayer_4_0.png");
    if (hero) {
        hero->setPosition(Vec2(visibleSize.width / 4.5 + origin.x, visibleSize.height / 3.8 + origin.y)); // 设置英雄的位置
        hero->setScale(0.8);
        this->addChild(hero); // 将英雄添加到场景中
    }
    hero->enableMouseControl(true);
    //在游戏准备阶段，小小英雄移动
	//初始英雄
    Hero so(1, 1, this),so1(1,1,this);
    this->addChild(so.mine);
	this->addChild(so1.mine);
	my_hero.the = this;
	enemy_hero.the = this;
	my_hero.hero_on_board.push_back(&so);
	enemy_hero.hero_on_board.push_back(&so1);
    so.mine->setPosition(30, 30);
	so1.mine->setPosition(100, 100);
	so.enableMouseControl(1,this);
    this->scheduleUpdate();
	//so1.enableMouseControl(1,this);
	/*so.attack(so.gettarget(enemy_hero), this, enemy_hero);
	so1.attack(so1.gettarget(my_hero), this, my_hero);*/
    //创建初始英雄
    
	//战斗环节只能对备战席上英雄点击有效

	return true;
}

