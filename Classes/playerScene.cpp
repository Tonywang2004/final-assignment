#include "playerScene.h"
#include"hero.h"
#include"AudioControl.h"
#include"SettingScene.h"
#include"MoveLittleHero.h"
#include<vector>
#include"endScene.h"
USING_NS_CC;

#define STORETAG   462

std::vector<Sprite*>MySeat;  //大小为14


int enemyType = 1;  // 第一个对手

chessboardSeat seat1(1);   //棋盘位置
preparationSeat seat2(1);   //备战席位置

chessboardSeat seat3(0);   //敌方棋盘位置
preparationSeat seat4(0);   //敌方备战席位置

extern Vector<Hero*> allMyHeroes;//我方所有英雄
extern Vector<Hero*> allEnemyHeroes;//敌方所有英雄

extern int fight;  //阶段切换

playerScene* playerScene::createScene() {
	return playerScene::create();
}

bool playerScene::init() {

	if (!Scene::create()) {
		return 0;
	}

	// 获取当前屏幕的尺寸和原点位置
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 创建背景精灵
	auto background = Sprite::create("pink_1.jpg");
	if (background != NULL)
	{
		// 设置背景精灵的位置
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// 缩放背景以填充屏幕
		float scaleX = visibleSize.width / background->getContentSize().width;
		float scaleY = visibleSize.height / background->getContentSize().height;
		background->setScale(scaleX, scaleY);

		// 将背景精灵添加到场景中
		this->addChild(background, 0); // 0 表示层级，确保背景在最底层
	}


	// 创建小小英雄
	auto hero = littleHero::create("LittlePlayer_1_0.png");
	if (hero) {
		hero->setPosition(Vec2(visibleSize.width / 4.5 + origin.x, visibleSize.height / 3.8 + origin.y)); // 设置英雄的位置
		hero->setScale(0.8);
		this->addChild(hero); // 将英雄添加到场景中
	}
	hero->enableMouseControl(true);

	//创建设置按钮
	auto setting = createButton("setting_icon.png", "setting_icon_click.png", Vec2(origin.x + visibleSize.width * 0.95, origin.y + visibleSize.height * 0.9),
		2.5, [=](Ref* sender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				// 播放点击音效
				AudioControl::getInstance()->playClickSoundEffect();
				// 创建下一个场景
				auto newScene = SettingScene::create();
				//切换到下一个场景
				cocos2d::Director::getInstance()->pushScene(TransitionFade::create(1.0, newScene, Color3B(255, 255, 240)));
			}
		});



	// 我方的初始英雄
	auto hero1 = Hero::creatHero(1, Vec2(seat1.seats[0].x + 70, seat1.seats[0].y + 50), 1);
	seat1.seats[0].state = 1;
	this->addChild(hero1, 2);
	hero1->enterboard();
	hero1->setIndex(0);


	//英雄位置移动
	auto changePosListener = EventListenerTouchOneByOne::create();
	changePosListener->setSwallowTouches(true);   
	//英雄点击判定
	changePosListener->onTouchBegan = [this](Touch* t, Event* e)->bool {
		//战斗环节只能对备战席上英雄点击有效
		if (fight) {
			for (Hero* hero : allMyHeroes) {
				if (!hero->isonboard()) {  //不在战斗席上
					Vec2 myclick = t->getLocation();
					myclick = hero->convertToNodeSpace(myclick);
					Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
					if (spriteBoundingBox.containsPoint(myclick)) {
						hero->setclick(1);
						return true;
					}
				}
			}
			return false;  //即没有点击到备战席上任何英雄
		}
		else {  //非战斗环节对所有己方英雄点击均有效
			for (Hero* hero : allMyHeroes) {
				Vec2 myTurn = t->getLocation();
				myTurn = hero->convertToNodeSpace(myTurn);
				Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
				if (spriteBoundingBox.containsPoint(myTurn)) {
					hero->setclick(1);
					return true;
				}
			}
			return false;  //没有点击到任何英雄
		}

	};
	//英雄的移动
	changePosListener->onTouchMoved = [](Touch* t, Event* e)->void {
		for (Hero* hero : allMyHeroes) {
			if (hero->getclick()) {
				hero->setPosition(hero->getPosition() + t->getDelta());
				break;
			}
		}
	};
	//英雄放置
	changePosListener->onTouchEnded = [this](Touch* t, Event* e)->void {
		if (fight) {  //结束点只考虑是否落在备战席上
			int i;
			for (i = 5; i < 14; i++) {
				Vec2 clickEnd = t->getLocation();
				clickEnd = MySeat[i]->convertToNodeSpace(clickEnd);
				Rect spriteBoundingBox = Rect(0, 0, MySeat[i]->getContentSize().width, MySeat[i]->getContentSize().height);
				if (spriteBoundingBox.containsPoint(clickEnd)) {
					int index = i - 5;  //备战席位置下标
					
					//判断该位置是否为空
					if (seat2.seats[index].state == 0) {  //空位置
						for (Hero* hero : allMyHeroes) {
							if (hero->getclick()) {  //找到被点击的英雄
								seat2.seats[hero->getindex()].Removesprite();  //原位置设为空
								hero->setIndex(index);  //英雄存储新下标
								hero->setPosition(seat2.seats[index].x + 70, seat2.seats[index].y + 50);
								seat2.seats[index].Setsprite();
								hero->setclick(0);  //重置点击
								break;
							}
						}
					}
					else {   //非空位置
						for (Hero* hero1 : allMyHeroes) {
							if (hero1->getclick()) {  //找到被点击的英雄
								for (Hero* hero2 : allMyHeroes) {
									if (!hero2->isonboard() && hero2->getindex() == index) {
										//交换位置
										hero2->setIndex(hero1->getindex());
										hero1->setIndex(index);
										hero1->setPosition(seat2.seats[hero1->getindex()].x + 70, seat2.seats[hero1->getindex()].y + 50);
										hero2->setPosition(seat2.seats[hero2->getindex()].x + 70, seat2.seats[hero2->getindex()].y + 50);
										hero1->setclick(0);
										break;
									}
								}
								break;
							}
						}
					}
					break;  //退出查找其他备战席位置
				}
			}
			if (i == 14) {  //回到原点
				for (Hero* hero : allMyHeroes) {
					if (hero->getclick()) {
						hero->setPosition(seat2.seats[hero->getindex()].x + 70, seat2.seats[hero->getindex()].y + 50);
						hero->setclick(0);
						break;
					}
				}
			}
		}
		else {   //结束点考虑所有点位
			int i;
			for (i = 0; i < 14; i++) {
				Vec2 clickEnd = t->getLocation();
				clickEnd = MySeat[i]->convertToNodeSpace(clickEnd);
				Rect spriteBoundingBox = Rect(0, 0, MySeat[i]->getContentSize().width, MySeat[i]->getContentSize().height);
				if (spriteBoundingBox.containsPoint(clickEnd)) {  //停留在了某个位置
					if (i >= 5) {  //停留的位置是备战席
						int index = i - 5;  //备战席位置下标

						//判断该位置是否为空
						if (seat2.seats[index].state == 0) {  //空位置
							for (Hero* hero : allMyHeroes) {
								if (hero->getclick()) {  //找到被点击的英雄
									if (hero->isonboard()) {  //原位置在战斗席
										seat1.seats[hero->getindex()].Removesprite();  //原位置设为空
									}
									else {   //原位置在备战席
										seat2.seats[hero->getindex()].Removesprite();  //原位置设为空
									}
									
									hero->setIndex(index);  //英雄存储新下标
									hero->setPosition(seat2.seats[index].x + 70, seat2.seats[index].y + 50);
									seat2.seats[index].Setsprite();
									hero->outboard();  //回到备战席
									hero->setclick(0);  //重置点击
									break;
								}
							}
						}
						else {   //非空位置
							for (Hero* hero1 : allMyHeroes) {
								if (hero1->getclick()) {  //找到被点击的英雄
									for (Hero* hero2 : allMyHeroes) {
										if (!hero2->isonboard() && hero2->getindex() == index) {
											//交换位置
											hero2->setIndex(hero1->getindex());
											hero1->setIndex(index);
											hero1->setPosition(seat2.seats[hero1->getindex()].x + 70, seat2.seats[hero1->getindex()].y + 50);
											if (!hero1->isonboard())
											{
												hero2->setPosition(seat2.seats[hero2->getindex()].x + 70, seat2.seats[hero2->getindex()].y + 50);
											}
											else {
												hero2->setPosition(seat1.seats[hero2->getindex()].x + 70, seat1.seats[hero2->getindex()].y + 50);
											}
											hero1->setclick(0);
											hero2->setboard(hero1->isonboard());
											hero1->outboard();
											break;
										}
									}

									break;
								}
							}
						}
					}
					else {   //停留的位置是战斗席
						int index = i;
						if (seat1.seats[index].state == 0) {  //空位置
							int hero_in_board = 0;
							for (Hero* hero : allMyHeroes) {
								if (hero->isonboard()) {
									hero_in_board++;
								}
							}
							for (Hero* hero : allMyHeroes) {
								if (hero->getclick()) {  //找到被点击的英雄
									if (hero->isonboard()) {  //原位置在战斗席
										seat1.seats[hero->getindex()].Removesprite();  //原位置设为空
										hero->setIndex(index);  //英雄存储新下标
										hero->setPosition(seat1.seats[index].x + 70, seat1.seats[index].y + 50);
										seat1.seats[index].Setsprite();
										hero->enterboard();  //上战场
										hero->setclick(0);  //重置点击
									}
									else {   //原位置在备战席
										if (hero_in_board >= store->level)  //超出人数
										{
											hero->setPosition(seat2.seats[hero->getindex()].x + 70, seat2.seats[hero->getindex()].y + 50);
										}
										else {
											seat2.seats[hero->getindex()].Removesprite();  //原位置设为空
											hero->setIndex(index);  //英雄存储新下标
											hero->setPosition(seat1.seats[index].x + 70, seat1.seats[index].y + 50);
											seat1.seats[index].Setsprite();
											hero->enterboard();  //上战场
											hero->setclick(0);  //重置点击
										}
									}
									break;
								}
							}
						}
						else {   //非空位置
							for (Hero* hero1 : allMyHeroes) {
								if (hero1->getclick()) {  //找到被点击的英雄
									for (Hero* hero2 : allMyHeroes) {
										if (hero2->isonboard() && hero2->getindex() == index) {
											//交换位置
											hero2->setIndex(hero1->getindex());
											hero1->setIndex(index);
											hero1->setPosition(seat1.seats[hero1->getindex()].x + 70, seat1.seats[hero1->getindex()].y + 50);
											if(!hero1->isonboard())
											{
												hero2->setPosition(seat2.seats[hero2->getindex()].x + 70, seat2.seats[hero2->getindex()].y + 50);
											}
											else {
												hero2->setPosition(seat1.seats[hero2->getindex()].x + 70, seat1.seats[hero2->getindex()].y + 50);
											}
											hero1->setclick(0);
											hero2->setboard(hero1->isonboard());
											hero1->enterboard();
											break;
										}
									}

									break;
								}
							}
						}
					}

					break;  //退出查找其他备战席位置
				}
			}
			if (i == 14) {  //回到原点
				for (Hero* hero : allMyHeroes) {
					if (hero->getclick()) {
						if(!hero->isonboard())
						{
							hero->setPosition(seat2.seats[hero->getindex()].x + 70, seat2.seats[hero->getindex()].y + 50);
						}
						else {
							hero->setPosition(seat1.seats[hero->getindex()].x + 70, seat1.seats[hero->getindex()].y + 50);
						}
						hero->setclick(0);
						break;
					}
				}
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(changePosListener, this);


	//每一帧更新英雄的血条和蓝条
	this->schedule([this](float dt) {
		//更新我方英雄血量和蓝量
		for (Hero* hero : allMyHeroes) {
			hero->updatebloodandmagic();
		}
        //更新敌方英雄的血量和蓝量
	    for (Hero* hero : allEnemyHeroes) {
		    hero->updatebloodandmagic();
	    }
	}, "updateherobar");


	//每一帧更新
	this->schedule([this](float dt) {
		float mypercentage = myrole->cur_blood / myrole->max_blood * 100.0f;
	    myrole->healthBar->setPercentage(mypercentage);
		if (enemyType == 2)
		{
			float enemypercentage = enemyrole1->cur_blood / enemyrole1->max_blood * 100.0f;
			enemyrole1->healthBar->setPercentage(enemypercentage);
		}
		else {
			float enemypercentage = enemyrole2->cur_blood / enemyrole2->max_blood * 100.0f;
			enemyrole2->healthBar->setPercentage(enemypercentage);
		}

		if (myrole->cur_blood == 0 && (enemyrole1->cur_blood != 0 || enemyrole2->cur_blood != 0)) {  //我方失败
			auto delayAction = DelayTime::create(1.0f); // 停顿1秒
			auto callback = CallFunc::create([]() {
				auto endscene = endScene::createScene(0);
			    Director::getInstance()->replaceScene(endscene);
			});
			auto sequence = Sequence::create(delayAction, callback, nullptr);
			this->runAction(sequence);
		}
		if (myrole->cur_blood != 0 && enemyrole1->cur_blood == 0 && enemyrole2->cur_blood == 0) {  //敌方失败
			auto delayAction = DelayTime::create(1.0f); // 停顿1秒
			auto callback = CallFunc::create([]() {
				auto endscene = endScene::createScene(1);
			    Director::getInstance()->replaceScene(endscene);
			});
			auto sequence = Sequence::create(delayAction, callback, nullptr);
			this->runAction(sequence);
		}
		if (myrole->cur_blood == 0 && enemyrole1->cur_blood == 0 && enemyrole2->cur_blood == 0) {  //平局
			auto delayAction = DelayTime::create(1.0f); // 停顿1秒
			auto callback = CallFunc::create([]() {
				auto endscene = endScene::createScene(2);
			    Director::getInstance()->replaceScene(endscene);
			});
			auto sequence = Sequence::create(delayAction, callback, nullptr);
			this->runAction(sequence);
		}
	}, "updaterolebar");

	//进度条设置
	progress0 = Sprite::create("progress0.png");
	progress1 = ProgressTimer::create(Sprite::create("progress1.png"));
	progress0->setPosition(955, 1000);
	progress1->setPosition(955, 1000);
	this->addChild(progress0, 5);
	this->addChild(progress1, 6);
	progress1->setType(ProgressTimer::Type::BAR);
	progress1->setMidpoint(Vec2(0, 0.5)); // 从左到右
	progress1->setBarChangeRate(Vec2(1, 0)); // 沿水平方向改变


	//游戏主循环的回调函数
	this->schedule(CC_SCHEDULE_SELECTOR(playerScene::startGame), 1.0f);


	/*我方位置图标的显示(仅显示我方)*/
//位置图标初始化
	for (int i = 0; i < 14; i++) {
		MySeat.push_back(Sprite::create("seats.png"));
	}
	//图标显示
	for (int i = 0; i < 5; i++) {
		MySeat[i]->setScale(0.25);
		MySeat[i]->setPosition(seat1.seats[i].x + 70, seat1.seats[i].y + 50);
		this->addChild(MySeat[i], 1);
	}
	for (int i = 0; i < 9; i++) {
		MySeat[i + 5]->setScale(0.25);
		MySeat[i + 5]->setPosition(seat2.seats[i].x + 70, seat2.seats[i].y + 50);
		this->addChild(MySeat[i + 5], 1);
	}




	//英雄售卖
	auto sellheroListener = EventListenerMouse::create();
	sellheroListener->onMouseDown = [this](EventMouse* event)->void {
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
			//在战斗，则只能卖备战席上的英雄
			if (fight) {
				for (Hero* hero : allMyHeroes) {
					if (!hero->isonboard()) {  //不在战斗席上
						Vec2 touchLocation = Vec2(event->getCursorX(), event->getCursorY());
						touchLocation = hero->convertToNodeSpace(touchLocation);
						Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
						if (spriteBoundingBox.containsPoint(touchLocation)) {
							//商店加钱，要显示刷新
							store->gold += (store->herocost[hero->getNo()]) * pow(3, (hero->getlevel()) - 1);
							store->updateUI();

							//英雄消失
							seat2.seats[hero->getindex()].Removesprite();
							allMyHeroes.eraseObject(hero);
							hero->removeFromParent();
							break;
						}
					}
				}
			}
			else {  //非战斗环节，可以点击所有英雄
				for (Hero* hero : allMyHeroes) {
					Vec2 touchLocation = Vec2(event->getCursorX(), event->getCursorY());
					touchLocation = hero->convertToNodeSpace(touchLocation);
					Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
					
					if (spriteBoundingBox.containsPoint(touchLocation)) {
						//刷新余额
						store->gold += (store->herocost[hero->getNo()]) * pow(3, (hero->getlevel()) - 1);
						store->updateUI();

						//去除卖掉的英雄
						if (hero->isonboard()) {
							seat1.seats[hero->getindex()].Removesprite();
						}
						else {
							seat2.seats[hero->getindex()].Removesprite();
						}
						allMyHeroes.eraseObject(hero);
						hero->removeFromParent();
						break;
					}
				}
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(sellheroListener, this);


	//小小英雄
	myrole = playerroleLayer::createLayer(0);
	this->addChild(myrole, 3, ROLETAG);
	enemyrole1= playerroleLayer::createLayer(1);
	this->addChild(enemyrole1, 3);
	enemyrole2 = playerroleLayer::createLayer(2);
	this->addChild(enemyrole2, 3);

	/* 人机1 */
	auto enemy11 = Sprite::create("enemy11.png");
	auto enemy12 = Sprite::create("enemy12.png");
	auto enemy13 = Sprite::create("enemy13.png");
	seeEnemy1 = MenuItemSprite::create(enemy11, enemy12, enemy13,
		CC_CALLBACK_1(playerScene::seeEnemy1_callback, this));
	auto see_enemy1 = Menu::create(seeEnemy1, NULL);
	this->addChild(see_enemy1, 4);
	see_enemy1->setScale(0.7);
	see_enemy1->setPosition(1400, 700);
	
	/* 人机2 */
	auto enemy21 = Sprite::create("enemy21.png");
	auto enemy22 = Sprite::create("enemy22.png");
	auto enemy23 = Sprite::create("enemy23.png");
	seeEnemy2 = MenuItemSprite::create(enemy21, enemy22, enemy23,
		CC_CALLBACK_1(playerScene::seeEnemy2_callback, this));
	auto see_enemy2 = Menu::create(seeEnemy2, NULL);
	this->addChild(see_enemy2, 4);
	see_enemy2->setScale(0.7);
	see_enemy2->setPosition(1400, 600);

	/* 返回按键 */
	auto goback1 = Sprite::create("goback1.png");
	auto goback2 = Sprite::create("goback2.png");
	goback = MenuItemSprite::create(goback1, goback2,
		CC_CALLBACK_1(playerScene::goback_callback, this));
	auto go_back = Menu::create(goback, NULL);
	this->addChild(go_back, 4);
	go_back->setScale(0.7);
	go_back->setPosition(1400, 500);
	goback->setVisible(false);

	//商店
	store = storeLayer::createLayer();   
	this->addChild(store, 4);


	//小小英雄的移动
	auto roleMoveListener = EventListenerTouchOneByOne::create();
	roleMoveListener->setSwallowTouches(true);
	roleMoveListener->onTouchBegan = [background, this](Touch* t, Event* e)-> bool {
		Vec2 pos = background->convertTouchToNodeSpace(t);
		if (pos.x > 323 && pos.x < 1247 && pos.y>327 && pos.y < 839)  //小小英雄移动范围
		{
			myrole->cur_position = Vec2(pos.x + 70, pos.y + 50);
			auto role = this->myrole->getChildByTag(ROLETAG);
			role->stopAllActions();
			role->runAction(MoveTo::create(0.3, Vec2(pos.x + 55.25, pos.y + 46.875)));
			return true;   //事件不再传递给其他监听器
		}
		else {
			return false;  //事件可以继续传递
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(roleMoveListener, this);
	


	// 人机小小英雄的随机移动
	this->schedule(CC_SCHEDULE_SELECTOR(playerScene::enemyMove), 10.0f); // 10秒的时间间隔
	//检测敌方英雄的移动
	this->schedule([this](float dt) {
		enemyrole1->getChildByTag(ROLETAG)->stopAllActions();
	enemyrole1->getChildByTag(ROLETAG)->runAction(MoveTo::create(0.3f, Vec2(enemyrole1->cur_position.x - 14.75, enemyrole1->cur_position.y - 3.125)));
	enemyrole2->getChildByTag(ROLETAG)->stopAllActions();
	enemyrole2->getChildByTag(ROLETAG)->runAction(MoveTo::create(0.3f, Vec2(enemyrole2->cur_position.x - 14.75, enemyrole2->cur_position.y - 3.125)));
		}, 0.3, "enemymove");
	return 1;
}

//显示所有英雄
void playerScene::ShowHeroes(int turn) {
	if (turn == 0) {  //我方
		for (Hero* hero : allMyHeroes) {
			if (hero->isonboard()) {  //在战场上
				hero->setPosition(seat1.seats[hero->getindex()].x + 70, seat1.seats[hero->getindex()].y + 50);
			}
			else {  //在备战席上
				hero->setPosition(seat2.seats[hero->getindex()].x + 70, seat2.seats[hero->getindex()].y + 50);
			}
			hero->sethp(hero->gethpmax());   //设置初始满血
			hero->setmp(hero->getmpstart());  //设置初始蓝量
			hero->setVisible(true);   //重新显示
			if (hero->getdie()) {   //重置Die标志
				hero->setdie(0);
			}
		}
	}
	else{  //生成enemyrole1的英雄
		//删除原本的英雄
		Vector<Hero*>heroToDelete;
		for (Hero* hero : allEnemyHeroes) {
			heroToDelete.pushBack(hero);
		}
		for (Hero* hero : heroToDelete) {
			allEnemyHeroes.eraseObject(hero);
			hero->removeFromParent();
		}

		//重置seat3的state为0
		for (int i = 0; i < 5; i++) {
			seat3.seats[i].state = 0;
		}

		int myPriority[5] = { 1,6,5,3,4 };  //英雄类型的优先级
		int enemyPriority[5] = { 3,6,1,4,5 };
		int i = 0;  
		for (Hero* myhero : allMyHeroes) {
			if (myhero->isonboard()) {
				Hero* enemy;
				if (turn == 1)
				{
					enemy = Hero::creatHero(myPriority[i], Vec2(0, 0), 0);
				}
				else if (turn == 2) {
					enemy = Hero::creatHero(enemyPriority[i], Vec2(0, 0), 0);
				}
				enemy->setIndex(myhero->getindex());    //设置下标
				enemy->enterboard();    
				this->addChild(enemy, 2);   
				enemy->setVisible(false);  
				seat3.seats[myhero->getindex()].state = 1;   
				enemy->upgrade(myhero->getlevel());  //设置为相同的星级
				i++;
			}
		}

		//显示敌方英雄
		for (Hero* hero : allEnemyHeroes) {
			if (hero->isonboard()) {  //在战场上
				hero->setPosition(seat3.seats[hero->getindex()].x + 70, seat3.seats[hero->getindex()].y + 50);
			}
			else {  //在备战席上
				hero->setPosition(seat4.seats[hero->getindex()].x + 70, seat4.seats[hero->getindex()].y + 50);
			}
			hero->sethp(hero->gethpmax());
			hero->setmp(hero->getmpstart());
			hero->setVisible(true);
			if (hero->getdie()) {
				hero->setdie(0);
			}
		}
	}
	Hero::mergeHeroes();
}


//覆盖所有英雄
void playerScene::CoverHeroes(int tag) {
	if (tag == 0) {
		for (Hero* hero : allMyHeroes) {
			hero->setVisible(false);
		}
	}
	else {
		for (Hero* hero : allEnemyHeroes) {
			hero->setVisible(false);
		}
	}
}


//人机1的棋盘
void playerScene::seeEnemy1_callback(Ref* pSender) {
	seeEnemy1->setEnabled(false); 
	seeEnemy2->setEnabled(false);  
	goback->setVisible(true);  //返回按键

	//显示敌方
	CoverHeroes(0);
	store->setVisible(false);
	ShowHeroes(1);
}


//人机2的棋盘
void playerScene::seeEnemy2_callback(Ref* pSender) {
	seeEnemy1->setEnabled(false); 
	seeEnemy2->setEnabled(false);  
	goback->setVisible(true);  //返回按键

	// 显示敌方
	CoverHeroes(0);
	store->setVisible(false);
	ShowHeroes(2);
}


// 返回
void playerScene::goback_callback(Ref* pSender) {
	goback->setVisible(false);
	seeEnemy1->setEnabled(true);
	seeEnemy2->setEnabled(true);

	//撤去敌方英雄，显示我方英雄和商店
	CoverHeroes(1);
	ShowHeroes(0);
	store->setVisible(true);
}


// 人机的随机移动
void playerScene::enemyMove(float dt) {
	// 获取实际分辨率
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	// 编写此处代码时的分辨率为 2560*1440
	cocos2d::Size designSize = cocos2d::Size(2560, 1440);

	// 计算实际分辨率与设计分辨率的缩放比例
	float scaleX = visibleSize.width / designSize.width;
	float scaleY = visibleSize.height / designSize.height;

	// 棋盘在设计分辨率下的位置和大小
	cocos2d::Rect designBoardRect(400, 250, 1880, 1080);
	srand(time(0));
	int x = rand() % 540 + 400;
	int y = rand() % 430 + 250;
	// 人机1的位置数据变化 
	enemyrole1->cur_position = Vec2(x + 70, y + 50);

	x = rand() % 540 + 400;
	y = rand() % 430 + 250;
	// 人机2的位置数据变化 
	enemyrole1->cur_position = Vec2(x + 70, y + 50);
}

//创建按钮
ui::Button* playerScene::createButton(const string& normalImage, const string& selectedImage, const Vec2& position,
	const float& scale, const std::function<void(Ref*, ui::Widget::TouchEventType)>& callback) {
	auto button = ui::Button::create(normalImage, selectedImage);
	button->setPosition(position);
	button->setScale(scale);
	button->addTouchEventListener(callback);
	this->addChild(button, 2);
	return button;
}


void  playerScene::onEnter() {
	Scene::onEnter();
	// 检查是否处于静音状态
	if (!AudioControl::getInstance()->isMuted()) {
		// 如果没有静音，重新开始播放背景音乐
		AudioControl::getInstance()->playBackgroundMusic("BM.mp3", true);
	}
}

void  playerScene::onExit() {
	Scene::onExit();
}