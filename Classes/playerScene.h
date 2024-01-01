#pragma once
#include"cocos2d.h"
#include"preparationSeat.h"
#include"chessboardSeat.h"
#include"storeLayer.h"
#include"hero.h"
#include"playerroleLayer.h"
USING_NS_CC;
extern Vector<Hero*> allMyHeroes;//我方所有英雄
extern Vector<Hero*> allEnemyHeroes;//敌方所有英雄
extern int fight;
extern int enemyType;

class playerScene : public Scene
{
public:
    playerroleLayer* myrole;
    playerroleLayer* enemyrole1;  //人机1
    playerroleLayer* enemyrole2;  //人机2

	storeLayer* store;

    Sprite* progress0;
    ProgressTimer* progress1;
    Sequence* to1;
    Sequence* gameprogress;

    float totalTime = 20.0f;
    float currentTime = 0.0f;

    MenuItemSprite* seeEnemy1;
    MenuItemSprite* seeEnemy2;
    MenuItemSprite* goback;

	static playerScene* createScene();
	virtual bool init();
	CREATE_FUNC(playerScene);
	void ShowHeroes(int IsMine);
	void CoverHeroes(int IsMine);

    //重写
    void onEnter();
    void onExit();

    //创建按钮
    ui::Button* playerScene::createButton(const string& normalImage, const string& selectedImage, const Vec2& position,
        const float& scale, const std::function<void(Ref*, ui::Widget::TouchEventType)>& callback);

    void startattack() {
        schedule(CC_SCHEDULE_SELECTOR(playerScene::attack), 2.0f);
    }

    // 攻击方法
    void attack(float dt)
    {
        bool attacked = 0;

        //我方攻击动作
        for (auto myHero : allMyHeroes)
        {
            if (!myHero->getdie() && myHero->isonboard()) {
                Hero* target;
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto enemyHero : allEnemyHeroes) {
                    if (!enemyHero->getdie() && enemyHero->isonboard()) {
                        targetFind = 1;
                        long long x_distance = myHero->getPosition().x - enemyHero->getPosition().x;
                        long long y_distance = myHero->getPosition().y - enemyHero->getPosition().y;
                        long long distance = pow(x_distance, 2) + pow(y_distance, 2);
                        if (distance < nearst_distance) {
                            target = enemyHero;
                            nearst_distance = distance;
                        }
                    }
                }
                if (targetFind) {
                    myHero->attack(target);
                    attacked = 1;
                }
            }
        }
        //敌方攻击动作
        for (auto enemyHero : allEnemyHeroes)
        {
            if (!enemyHero->getdie()&&enemyHero->isonboard()) {
                Hero* target;
                bool targetFind = 0;
                long long nearst_distance = 99999999999;
                for (auto myHero : allMyHeroes) {
                    if (!myHero->getdie()&&myHero->isonboard()) {
                        targetFind = 1;
                        long long x_distance = myHero->getPosition().x - enemyHero->getPosition().x;
                        long long y_distance = myHero->getPosition().y - enemyHero->getPosition().y;
                        long long distance = pow(x_distance, 2) + pow(y_distance, 2);
                        if (distance < nearst_distance) {
                            target = myHero;
                            nearst_distance = distance;
                        }
                    }
                }

                if (targetFind) {
                    enemyHero->attack(target);
                    attacked = 1;
                }

            }
        }
        if (!attacked) {
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::attack));
            fight = 0;

            //小小英雄的攻击、会自动扣血
            int countUnDead = 0;
            for (Hero* hero : allEnemyHeroes) {
                if (hero->isonboard() && !hero->getdie()) {
                    countUnDead++;
                }
            }
            if (countUnDead == 0) {
                if (enemyType == 1)
                {
                    myrole->attack(enemyrole1);
                }
                else {
                    myrole->attack(enemyrole2);
                }
            }
            countUnDead = 0;
            for (Hero* hero : allMyHeroes) {
                if (hero->isonboard() && !hero->getdie()) {
                    countUnDead++;
                }
            }
            if (countUnDead == 0) {
                if (enemyType == 1)
                {
                    enemyrole1->attack(myrole);
                }
                else {
                    enemyrole2->attack(myrole);
                }
            }
            schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);
        }
    }

    //通过检测fight全局变量来实现准备环节与战斗环节的交替
    void startGame(float dt) {  
        if (fight == 0) {  //退出战斗，轮到准备环节
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::startGame));  //停止外层循环回调
            static int count = 0;  //用于跳过初始界面商店的重复刷新
            if (count)
            {
                store->gold += 2;  
                store->refresh();   //新的环节会刷新商店

                //每一轮的额外奖励
                store->gold += 2;

                // 每满10个金币可以返回一个金币的利息
                store->gold += store->gold / 10;
                store->updateUI();
            }
            count++;

            seeEnemy1->setEnabled(true);
            seeEnemy2->setEnabled(true);

            //重现我方英雄
            ShowHeroes(0);

            //撤去敌方英雄
            CoverHeroes(enemyType);

            // 切换对手
            enemyType = 3 - enemyType;             

            //进度条开始
            progress0->setVisible(true);
            progress1->setVisible(true);
            // 设置定时器更新频率
            this->schedule([this](float dt) {
                currentTime += dt;
            // 计算当前进度
            float progressPercentage = (currentTime / totalTime) * 100.0f;
            // 更新进度条
            progress1->setPercentage(progressPercentage);

            // 判断是否达到定时时间，如果达到则取消定时器或进行其他操作
            if (currentTime >= totalTime) {  //准备时间结束
                this->unschedule("progress");
                currentTime = 0.0f;   //重置
                fight = 1;
                progress0->setVisible(false);
                progress1->setVisible(false);
                schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);
            }
                }, "progress");
        }
        else {
            unschedule(CC_SCHEDULE_SELECTOR(playerScene::startGame));  //停止外层回调
            //显示敌方英雄
            ShowHeroes(enemyType);
            ShowHeroes(0);
            store->setVisible(true);

            // 设置观察按键的禁用
            goback->setVisible(false);
            seeEnemy1->setEnabled(false);
            seeEnemy2->setEnabled(false);

            //开始对打
            startattack();
        }
    }

    void seeEnemy1_callback(Ref* pSender);  //观察人机1的棋盘
    void seeEnemy2_callback(Ref* pSender);  //观察人机2的棋盘
    void goback_callback(Ref* pSender);     //返回
    void enemyMove(float dt);    //人机的移动
};

