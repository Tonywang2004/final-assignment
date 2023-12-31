#include "networkScene.h"
#include"hero.h"
#include<vector>
#include"endScene.h"
USING_NS_CC;

#define STORETAG   462

extern std::vector<Sprite*>MySeat;  //大小为14
/*
  0——战斗席0
  1——战斗席1
  2——战斗席2
  3——战斗席3
  4——战斗席4

  5——备战席0
  6——备战席1
  7——备战席2
  8——备战席3
  9——备战席4
  10——备战席5
  11——备战席6
  12——备战席7
  13——备战席8
*/

playerroleLayer* myrole_;
playerroleLayer* enemyrole_;

extern chessboardSeat seat1;   //棋盘位置
extern preparationSeat seat2;   //备战席位置

extern chessboardSeat seat3;   //敌方棋盘位置
extern preparationSeat seat4;   //敌方备战席位置

extern Vector<Hero*> allMyHeroes;//我方所有英雄
extern Vector<Hero*> allEnemyHeroes;//敌方所有英雄

extern int fight;  //全局战况

networkScene* networkScene::createScene() {
	return networkScene::create();
}


bool networkScene::init() {

	if (!Scene::create()) {
		return 0;
	}

	//背景设置
	auto background = Sprite::create("playerSceneBackground.png");
	this->addChild(background, 0);
	background->setPosition(955, 540);

	// 我方的初始英雄
	auto hero1 = Hero::creatHero(1, Vec2(seat1.seats[0].x + 70, seat1.seats[0].y + 50), 1);
	seat1.seats[0].state = 1;
	this->addChild(hero1, 2);
	hero1->enterboard();
	hero1->setIndex(0);

	//英雄位置移动
	auto changePosListener = EventListenerTouchOneByOne::create();
	//事件吞没
	changePosListener->setSwallowTouches(true);
	//英雄点击判定
	changePosListener->onTouchBegan = [this](Touch* t, Event* e)->bool {
		//获取点击的位置

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
				Vec2 myclick = t->getLocation();
				myclick = hero->convertToNodeSpace(myclick);
				Rect spriteBoundingBox = Rect(0, 0, hero->getContentSize().width, hero->getContentSize().height);
				if (spriteBoundingBox.containsPoint(myclick)) {
					hero->setclick(1);
					return true;
				}
			}
			return false;  //即没有点击到任何英雄
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
											if (!hero1->isonboard())
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
						if (!hero->isonboard())
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
		}, "updateherobar_");

	//每一帧更新小小英雄的血条
	this->schedule([this](float dt) {
		float mypercentage = myrole_->cur_blood / myrole_->max_blood * 100.0f;
	float enemypercentage = enemyrole_->cur_blood / enemyrole_->max_blood * 100.0f;
	myrole_->healthBar->setPercentage(mypercentage);
	enemyrole_->healthBar->setPercentage(enemypercentage);
	if (mypercentage == 0 && enemypercentage != 0) {  //我方失败
		auto delayAction = DelayTime::create(1.0f); // 2秒钟的延迟时间
		auto callback = CallFunc::create([]() {
			auto endscene = endScene::createScene(0);
		Director::getInstance()->replaceScene(endscene);
			});
		auto sequence = Sequence::create(delayAction, callback, nullptr);
		this->runAction(sequence);
	}
	if (enemypercentage == 0 && mypercentage != 0) {  //敌方失败
		auto delayAction = DelayTime::create(1.0f); // 2秒钟的延迟时间
		auto callback = CallFunc::create([]() {
			auto endscene = endScene::createScene(1);
		Director::getInstance()->replaceScene(endscene);
			});
		auto sequence = Sequence::create(delayAction, callback, nullptr);
		this->runAction(sequence);
	}
	if (mypercentage == 0 && enemypercentage == 0) {  //平局
		auto delayAction = DelayTime::create(1.0f); // 2秒钟的延迟时间
		auto callback = CallFunc::create([]() {
			auto endscene = endScene::createScene(2);
		Director::getInstance()->replaceScene(endscene);
			});
		auto sequence = Sequence::create(delayAction, callback, nullptr);
		this->runAction(sequence);
	}
		}, "updaterolebar_");

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
	this->schedule(CC_SCHEDULE_SELECTOR(networkScene::startGame), 1.0f);

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

	//英雄售卖——通过鼠标点击右键来实现
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
						//商店加钱，要显示刷新
						store->gold += (store->herocost[hero->getNo()]) * pow(3, (hero->getlevel()) - 1);
						store->updateUI();

						//英雄消失
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
	myrole_ = playerroleLayer::createLayer(0);
	this->addChild(myrole_, 3, ROLETAG);
	enemyrole_ = playerroleLayer::createLayer(1);
	this->addChild(enemyrole_, 3);

	//英雄列表
	/* 敌方 */
	auto enemy1 = Sprite::create("enemyplayer1.png");
	auto enemy2 = Sprite::create("enemyplayer2.png");
	auto enemy3 = Sprite::create("enemyplayer3.png");
	seeEnemy = MenuItemSprite::create(enemy1, enemy2, enemy3,
		CC_CALLBACK_1(networkScene::seeEnemy_callback, this));
	auto see_enemy = Menu::create(seeEnemy, NULL);
	this->addChild(see_enemy, 4);
	see_enemy->setScale(0.7);
	see_enemy->setPosition(1400, 600);

	/* 返回按键 */
	auto goback1 = Sprite::create("goback1.png");
	auto goback2 = Sprite::create("goback2.png");
	goback = MenuItemSprite::create(goback1, goback2,
		CC_CALLBACK_1(networkScene::goback_callback, this));
	auto go_back = Menu::create(goback, NULL);
	this->addChild(go_back, 4);
	go_back->setScale(0.7);
	go_back->setPosition(1400, 500);
	goback->setVisible(false);

	//商店，是Scene中的私有成员
	store = storeLayer::createLayer();
	this->addChild(store, 4);

	//小小英雄的移动
	auto roleMoveListener = EventListenerTouchOneByOne::create();
	roleMoveListener->setSwallowTouches(true);    //事件吞没
	roleMoveListener->onTouchBegan = [background, this](Touch* t, Event* e)-> bool {
		Vec2 pos = background->convertTouchToNodeSpace(t);
		if (pos.x > 323 && pos.x < 1247 && pos.y>327 && pos.y < 839)  //小小英雄移动范围
		{
			myrole_->cur_position = Vec2(pos.x + 70, pos.y + 50);
			auto role = myrole_->getChildByTag(ROLETAG);
			role->stopAllActions();
			role->runAction(MoveTo::create(0.3, Vec2(pos.x + 55.25, pos.y + 46.875)));
			return true;   //事件不再传递给其他监听器
		}
		else {
			return false;  //事件可以继续传递
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(roleMoveListener, this);

	//检测敌方英雄的移动
	this->schedule([this](float dt) {
		enemyrole_->getChildByTag(ROLETAG)->stopAllActions();
	enemyrole_->getChildByTag(ROLETAG)->runAction(MoveTo::create(0.3f, Vec2(enemyrole_->cur_position.x - 14.75, enemyrole_->cur_position.y - 3.125)));
		}, 0.3, "enemymove_");

	return 1;
}


//显示所有英雄
void networkScene::ShowHeroes(int IsMine) {
	if (IsMine) {
		for (Hero* hero : allMyHeroes) {
			if (hero->isonboard()) {  //在战场上
				hero->setPosition(seat1.seats[hero->getindex()].x + 70, seat1.seats[hero->getindex()].y + 50);
			}
			else {  //在备战席上
				hero->setPosition(seat2.seats[hero->getindex()].x + 70, seat2.seats[hero->getindex()].y + 50);
			}
			hero->sethp(hero->gethpmax());   //设置初始血量、满血
			hero->setmp(hero->getmpstart());  //设置初始蓝量
			hero->setVisible(true);   //重新显示
			if (hero->getdie()) {   //重置Die标志
				hero->setdie(0);
			}
		}
	}
	else {  //用于联机模式，直接进行显示
		
		//通过Vector容器来显示敌方英雄
		for (Hero* hero : allEnemyHeroes) {
			if (hero->isonboard()) {  //在战场上
				hero->setPosition(seat3.seats[hero->getindex()].x + 70, seat3.seats[hero->getindex()].y + 50);
			}
			else {  //在备战席上
				hero->setPosition(seat4.seats[hero->getindex()].x + 70, seat4.seats[hero->getindex()].y + 50);
			}
			hero->sethp(hero->gethpmax());   //设置初始血量、满血
			hero->setmp(hero->getmpstart());  //设置初始蓝量
			hero->setVisible(true);   //重新显示
			if (hero->getdie()) {   //重置Die标志
				hero->setdie(0);
			}
		}
	}
}

//覆盖所有英雄
void networkScene::CoverHeroes(int IsMine) {
	if (IsMine) {
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

//观察敌方棋盘
void networkScene::seeEnemy_callback(Ref* pSender) {
	seeEnemy->setEnabled(false);  //禁用
	goback->setVisible(true);  //返回按键

	// 显示我方英雄撤去，我方商店撤去，显示敌方1
	CoverHeroes(1);
	store->setVisible(false);
	ShowHeroes(0);
}

//返回
void networkScene::goback_callback(Ref* pSender) {
	goback->setVisible(false);
	seeEnemy->setEnabled(true);

	//撤去敌方英雄，显示我方英雄和商店
	CoverHeroes(0);
	ShowHeroes(1);
	store->setVisible(true);
}