#include<iostream>
#include"ApplyLittleHero.h"
#include "hero.h"
#include"const.h"
using namespace std;
using namespace cocos2d;
extern Player my_hero;
extern Player enemy_hero;
void Hero::skill_add(ApplyLittleHero* the, Player enemy_hero, ProgressTimer* hp) {
	//创建进度条
	updateposition();
	ProgressTimer* mp = this->mp;
	ProgressTimer* myhp = this->hp;
	get_target(this, enemy_hero);
	if (No >= 4) {
		float mp_up = mp_increment;
		Vec2 fromposition = hero_position;
		auto target_hero = target->mine;
		string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
		float newMpPercentage = mp->getPercentage() + mp_up;
		float MyHpPercentage = myhp->getPercentage();
		if (mp->isVisible() == true) {
			if (hp->getPercentage() == 0) {
				mp->setVisible(false);
			}
			if (newMpPercentage >= 100.0f) {
				// MP达到100%，重置MP并减少HP
				newMpPercentage = 0.0f;
				// 减少HP的当前值的20%
				if (hp->getPercentage() != 0 && MyHpPercentage != 0) {
					skill(target, the, fromposition, target_hero->getPosition(), myhp);
				}
				else
					mp->setVisible(false);
				// 更新HP进度条
				float newHpPercentage = hp->getPercentage() - No * 5;
				hp->setPercentage(newHpPercentage);
			}
		}
		mp->setPercentage(newMpPercentage);
	}
	else
	{
		float mp_up = mp_increment;
		Vec2 fromposition = hero_position;
		auto target_hero = target->mine;
		string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
		float newMpPercentage = mp->getPercentage() + mp_up;
		float MyHpPercentage = myhp->getPercentage();
		if (mp->isVisible() == true) {
			if (hp->getPercentage() == 0) {
				mp->setVisible(false);
			}
			if (newMpPercentage >= 100.0f) {
				// MP达到100%，重置MP并减少HP
				newMpPercentage = 0.0f;
				// 减少HP的当前值的20%
				if (hp->getPercentage() != 0 && MyHpPercentage != 0) {
					skill(target, the, fromposition, target_hero->getPosition(), myhp);
				}
				// 更新HP进度条
				float newHpPercentage = hp->getPercentage() - 10;
				hp->setPercentage(newHpPercentage);
			}
		}
		mp->setPercentage(newMpPercentage);
	}
}
void Hero::skill(Hero* target, ApplyLittleHero* the, Vec2 fromposition, Vec2 toposition,ProgressTimer* myhp) {
	if (No >= 4) {
		auto sprite = Sprite::create("bigbullet.png");//建立一个强化攻击的精灵图像
		if (sprite != nullptr) {
			sprite->setContentSize(Size(40, 40));
			sprite->setPosition(fromposition);
			the->addChild(sprite);
			auto moveto = MoveTo::create(0.1f, toposition);//移动到目标位置
			Hide* hideAction = Hide::create();
			Sequence* sequence = Sequence::create(moveto, hideAction, nullptr);
			sprite->runAction(sequence);
		}
	}
	else
	{
		float newHpPercentage = myhp->getPercentage() + 20 + No * 10;
		if (newHpPercentage > 100)
			newHpPercentage = 100;
		myhp->setPercentage(newHpPercentage);
	}
}
void Hero::attack(Hero* enemy, ApplyLittleHero* the, Player enemy_hero)
{
	//以敌方为中心展开
	//ImageSwitcher imageswitch("DemonSoldier.png", "player.png", this);
	ProgressTimer* myhp = hp;
	ProgressTimer* hp = enemy->hp;
	get_target(this, enemy_hero);
	//change the key word
	float hp_maxmax = hp_max;
	srand((time(0)));
	// 生成随机数
	int random_number = rand() % 100;
	float damage = atn - target->def;
	updateposition();
	auto nowposition = hero_position;
	auto toposition = target_position;
	auto target_hero = target->mine;
	auto mine_hero=mine;
	int ch_rate = ch;
	int ch_ms = ch_ma;
	if (No >= 3) {
		if (myhp->getPercentage() != 0) {
			//子弹执行运动
			auto sprite = Sprite::create("bullet.png");
			sprite->setPosition(nowposition);
			sprite->setContentSize(Size(10, 10));
			auto moveto = MoveTo::create(0.5f, mine->getPosition() + target_hero->getPosition());
			auto hide = Hide::create();
			auto delay = DelayTime::create(0.5f);
			auto sequence = Sequence::create(moveto, hide, nullptr);
			the->addChild(sprite);
			sprite->runAction(sequence);
		}
		float MyHpPercentage = myhp->getPercentage();
		srand((time(0)));
		// 生成随机数
		int isch = rand() % 10;
		int extra = 0;
		if (isch < ch_rate * 10)
			extra += damage * ch_ms;
		float hp_nownow = hp->getPercentage() / 100 * hp_maxmax - damage - extra;//damage;
		if (hp_nownow < 0) {
			hp_nownow = 0;
			hp->setVisible(false);
		}
		// 更新HP进度条
		if (MyHpPercentage != 0) {
			float newHpPercentage = static_cast<float>(hp_nownow) / hp_maxmax * 100.0f;
			hp->setPercentage(newHpPercentage);
		}
		skill_add(the, enemy_hero, hp);
	}
	else
	{
		get_target(this, enemy_hero);
		//移动到目标位置
		move_to_target(the, target);
		updateposition();
		auto moveAction = MoveTo::create(0.5f, target_position);
		string scheduleKey1 = "progress_update_hp" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
		float hp_maxmax = hp_max;
		// 生成随机数
		srand(time(0));
		int random_number = rand() % 100;
		float internal = (float)random_number / 1000 + as;
		float damage = atn - target->def;
		float moveDuration = 1.0f; // 移动持续时间，根据需要调整
		updateposition();
		auto nowposition = hero_position;
		auto target_hero = target->mine;
		auto my_hero = mine;
		int nums = 0;
		ProgressTimer* hp = target->hp;
		Sprite* show_isdie = isdie;
		float MyHpPercentage = myhp->getPercentage();
		// 生成随机数
		int isch = rand() % 10;
		int extra = 0;
		if (isch < ch_rate * 10)
			extra += damage * ch_ms;
		float hp_nownow = hp->getPercentage() / 100 * hp_maxmax - damage - extra;//damage;
		auto rotateRight = RotateBy::create(0.5f, 30.0f); // 0.5秒内旋转30度
		auto rotateBack = RotateBy::create(0.5f, -30.0f); // 再次旋转-30度以返回原位
		auto sequence = Sequence::create(rotateRight, rotateBack, nullptr);
		my_hero->runAction(sequence);
		if (hp_nownow < 0) {
			hp_nownow = 0;
			hp->setVisible(false);
		}
		// 更新HP进度条
		if (MyHpPercentage != 0) {
			float newHpPercentage = static_cast<float>(hp_nownow) / hp_maxmax * 100.0f;
			hp->setPercentage(newHpPercentage);
		}
		else {
			show_isdie->setVisible(true);
		}
		skill_add(the, enemy_hero, hp);
	}
}
void Hero::updateposition()
{
	hero_position = mine->getPosition();
}
void Hero::move_to_target(ApplyLittleHero* the,Hero* enemy)
{
	auto moveto = MoveTo::create(1.0f, Vec2(mine->getPosition() * 1.5 + target->mine->getPosition()) / 2.5);
	mine->runAction(moveto);
	if(mine->getBoundingBox().intersectsRect(enemy->mine->getBoundingBox()))
		mine->stopAllActions();
}
void Hero::get_target(Hero* hero, Player enemy)
{
	double minDistance = 99999999;
	int index = -1;
	//获取距离最近的英雄
	if (enemy.hero_on_board.size() != 0) {
		for (int i = 0; i < enemy.hero_on_board.size(); i++)
		{
			if (enemy.hero_on_board[i]->islive != 0) {
				double delta_position_square = (enemy.hero_on_board[i]->mine->getPosition().x - hero->mine->getPosition().x) * (enemy.hero_on_board[i]->mine->getPosition().x - hero->mine->getPosition().x) + (enemy.hero_on_board[i]->mine->getPosition().y - hero->mine->getPosition().y) * (enemy.hero_on_board[i]->mine->getPosition().y - hero->mine->getPosition().y);
				if (minDistance > delta_position_square) {
					minDistance = delta_position_square;
					index = i;
				}
			}
		}
		//目标变化
		if (index != -1) {
			target = enemy.hero_on_board[index];
			target_position = target->mine->getPosition();
			target_distance = sqrt(minDistance);
		}
		else
			target = nullptr;
	}
	else
		target = nullptr;
}

//监听单击或双击，双击移动到固定位置（要修改），单击移动位置
bool Hero::listenerinit() {
	// 创建鼠标事件监听器
	_Listener = EventListenerMouse::create();
	auto mouseListener = _Listener;
	// 初始化点击计数器和时间戳
	int clickCount = 0;
	float lastClickTime = 0;
	bool isSpriteClicked = false;
	const float doubleClickThreshold = 0.25f; // 双击阈值，单位秒
	Sprite* mySprite = mine;
	int isonboard=this->is_on_board;
	// 鼠标按下事件
	mouseListener->onMouseDown = [this,&isonboard, mySprite, &isSpriteClicked, &lastClickTime, doubleClickThreshold](Event* event) {
		EventMouse* e = dynamic_cast<cocos2d::EventMouse*>(event);
		Vec2 location = e->getLocationInView();
		location = cocos2d::Director::getInstance()->convertToGL(location);
		//y轴坐标反了，手动修改
		auto refreshSize = cocos2d::Director::getInstance()->getWinSize();
		location.y = refreshSize.height - location.y;
		//mySprite->setPosition(location);
		float currentTime = Director::getInstance()->getRunningScene()->getScheduler()->getTimeScale();
		if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
			if (mySprite->getBoundingBox().containsPoint(location)) {
					isSpriteClicked = true;
			}
			else if (isSpriteClicked) {
				// 如果精灵被单击且点击了其他位置，则移动精灵
				auto moveto = MoveTo::create(0.5f, location);
				mySprite->runAction(moveto);
				//mySprite->setPosition(location);
				isSpriteClicked = false;
			}
		}
		};
	return true;
}


//enable：是否将监听器添加到事件分发器
void Hero::enableMouseControl(bool enabled,ApplyLittleHero* the) {
	if (enabled) {
		if (!_Listener)
			listenerinit();
		// 将监听器添加到事件分发器
		_eventDispatcher->addEventListenerWithSceneGraphPriority(_Listener, the);
	}
	else {
		if (_Listener) {
			// 移除监听器
			_eventDispatcher->removeEventListener(_Listener);
		}
	}
}