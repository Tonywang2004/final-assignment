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
		the->schedule([=](float dt) {
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
						skill(target, the, fromposition, target_hero->getPosition(),myhp);
					}
					else
						mp->setVisible(false);
					// 更新HP进度条
					float newHpPercentage = hp->getPercentage() - No * 5;
					hp->setPercentage(newHpPercentage);
				}
			}
			mp->setPercentage(newMpPercentage);
			}, 0.5f, scheduleKey);
	}
	else
	{
		float mp_up = mp_increment;
		Vec2 fromposition = hero_position;
		auto target_hero = target->mine;
		string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
		the->schedule([=](float dt) {
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
						skill(target, the, fromposition, target_hero->getPosition(),myhp);
					}
					else
						the->unschedule(scheduleKey);//自己死了或目标死了退出
					// 更新HP进度条
					float newHpPercentage = hp->getPercentage() - 10;
					hp->setPercentage(newHpPercentage);
				}
			}
			mp->setPercentage(newMpPercentage);
			}, 0.5f, scheduleKey);
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
	string scheduleKey = "progress_update_hp" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	float hp_maxmax = hp_max;
	srand((time(0)));
	// 生成随机数
	int random_number = rand() % 100;
	float internal = (float)random_number / 1000 + as;
	float damage = atn - target->def;
	updateposition();
	auto nowposition = hero_position;
	auto toposition = target_position;
	auto target_hero = target->mine;
	if (No <= 3) {
		the->schedule([=](float dt) {
			//bullet
			hp->setMidpoint(Vec2(target_hero->getPosition().x, target_hero->getPosition().y - 30)); // 进度条起点位置
			hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
			hp->setPosition(target_hero->getPosition().x, target_hero->getPosition().y - 30); // 进度条位置
			if (hp->getParent() == nullptr)
				the->addChild(hp);
			if (myhp->getPercentage() != 0) {
				auto sprite = Sprite::create("bullet.png");
				sprite->setPosition(nowposition);
				sprite->setContentSize(Size(10, 10));
				auto moveto = MoveTo::create(0.5f, target_hero->getPosition());
				auto hide = Hide::create();
				auto delay = DelayTime::create(0.5f);
				auto sequence = Sequence::create(moveto, hide, nullptr);
				the->addChild(sprite);
				sprite->runAction(sequence);
			}
			float MyHpPercentage = myhp->getPercentage();
			float hp_nownow = hp->getPercentage() / 100 * hp_maxmax - damage;//damage;
			if (hp_nownow < 0) {
				hp_nownow = 0;
				hp->setVisible(false);
				the->unschedule(scheduleKey);
			}
			// 更新HP进度条
			if (MyHpPercentage != 0) {
				float newHpPercentage = static_cast<float>(hp_nownow) / hp_maxmax * 100.0f;
				hp->setPercentage(newHpPercentage);
			}
			}, internal, scheduleKey);
		skill_add(the, enemy_hero, hp);
	}
	else
	{
		get_target(this, enemy_hero);
		move_to_target(the, target);
		updateposition();
		auto moveAction = MoveTo::create(0.5f, target_position);
		string scheduleKey1 = "progress_update_hp" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
		float hp_maxmax = hp_max;
		srand((time(0)));
		// 生成随机数
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
		the->schedule([=](float dt) {
			float MyHpPercentage = myhp->getPercentage();
			float hp_nownow = hp->getPercentage() / 100 * hp_maxmax - damage;//damage;
			auto rotateRight = RotateBy::create(0.5f, 30.0f); // 0.5秒内旋转30度
			auto rotateBack = RotateBy::create(0.5f, -30.0f); // 再次旋转-30度以返回原位
			auto sequence = Sequence::create(rotateRight, rotateBack, nullptr);
			my_hero->runAction(sequence);
			if (hp_nownow < 0) {
				hp_nownow = 0;
				hp->setVisible(false);
				the->unschedule(scheduleKey1);//目标死了退出
			}
			// 更新HP进度条
			if (MyHpPercentage != 0) {
				float newHpPercentage = static_cast<float>(hp_nownow) / hp_maxmax * 100.0f;
				hp->setPercentage(newHpPercentage);
			}
			else {
				show_isdie->setVisible(true);
				the->unschedule(scheduleKey1);//自己死了退出循环
			}
			}, internal, scheduleKey1);
		skill_add(the, enemy_hero, hp);
	}
}
void Hero::updateposition()
{
	hero_position = mine->getPosition();
}
void Hero::move_to_target(ApplyLittleHero* the,Hero* enemy)
{
	auto moveto = MoveTo::create(1.0f, Vec2(target_position.x-10,target_position.y-10));
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
bool Hero::isTouch(Touch* touch, Event* event) {
	static float lastTouchTime = 0;
	float currentTime = Director::getInstance()->getTotalFrames();
	Vec2 location = touch->getLocation();

	if (mine->getBoundingBox().containsPoint(location)) {
		if (currentTime - lastTouchTime < 15) { // 检查双击，这里假设每帧间隔1/60秒
			// 双击了mine精灵
			if (this->is_onboard == 1) {
				int index=0;
				for (int i = 1; i <= MAX_STORAGE_NUM; i++)
					if ( seat[i] != 1 ) {
						index = i;
						break;
					}
				mine->setPosition(storage_position[index]);//双击后在场直接跳到0，0
				this->is_onboard = 0;
			}
			else {
				mine->setPosition(200,200);//双击后不在场跳到200，200
				this->is_onboard = 1;
			}
			clink = 0;
		}
		else {
			// 单击
			clink = !clink;
		}
		lastTouchTime = currentTime;
	}
	else if (clink) {
		// 如果已经点击了mine，再次点击其他位置
		mine->setPosition(location);
		clink = 0;
	}

	return true;
}