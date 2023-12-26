#include<iostream>
#include"HelloWorldScene.h"
#include "hero.h"
using namespace std;
using namespace cocos2d;
extern Player my_hero;
extern Player enemy_hero;
void Soldier::skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp) {
	//创建进度条
	updateposition();
	ProgressTimer* mp = this->mp;
	ProgressTimer* myhp = this->hp;
	get_target(this, enemy_hero);
	float mp_up = mp_increment;
	Vec2 fromposition = hero_position;
	Vec2 toposition = target_position;
	auto target_hero = target->mine;
	auto my_hero = mine;
	string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	the->schedule([=](float dt) {
		float newMpPercentage = mp->getPercentage() + mp_up;
		float MyHpPercentage = myhp->getPercentage();
		if (mp->isVisible() == true) {
			if (hp->getPercentage() == 0) {
				the->unschedule(scheduleKey);
			}
			if (newMpPercentage >= 100.0f) {
				// MP达到100%，重置MP并减少HP
				newMpPercentage = 0.0f;
				// 减少HP的当前值的20%
				if (hp->getPercentage() != 0 && MyHpPercentage != 0) {
					skill(myhp);
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
void Soldier::skill(ProgressTimer* myhp) {
	float newHpPercentage = myhp->getPercentage() + 20;
	if (newHpPercentage > 100)
		newHpPercentage = 100;
	myhp->setPercentage(newHpPercentage);

}
void Soldier::attack(Hero* enemy, HelloWorld* the, Player enemy_hero)
{
	//以敌方为中心展开,下为地方血条
	//ImageSwitcher imageswitch("DemonSoldier.png", "player.png", this);
	ProgressTimer* myhp = hp;
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
	if (target != nullptr) {
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
void SuperSoldier::skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp) {
	//创建进度条
	updateposition();
	ProgressTimer* mp = this->mp;
	ProgressTimer* myhp = this->hp;
	get_target(this, enemy_hero);
	float mp_up = mp_increment;
	Vec2 fromposition = hero_position;
	Vec2 toposition = target_position;
	auto target_hero = target->mine;
	auto my_hero = mine;
	string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	the->schedule([=](float dt) {
		float newMpPercentage = mp->getPercentage() + mp_up;
		float MyHpPercentage = myhp->getPercentage();
		if (mp->isVisible() == true) {
			if (hp->getPercentage() == 0) {
				the->unschedule(scheduleKey);
			}
			if (newMpPercentage >= 100.0f) {
				// MP达到100%，重置MP并减少HP
				newMpPercentage = 0.0f;
				// 减少HP的当前值的20%
				if (hp->getPercentage() != 0 && MyHpPercentage != 0) {
					skill(myhp);
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
void SuperSoldier::skill(ProgressTimer* myhp) {
	float newHpPercentage = myhp->getPercentage() + 30;
	if (newHpPercentage > 100)
		newHpPercentage = 100;
	myhp->setPercentage(newHpPercentage);

}
void SuperSoldier::attack(Hero* enemy, HelloWorld* the, Player enemy_hero)
{
	//以敌方为中心展开,下为地方血条
	//ImageSwitcher imageswitch("DemonSoldier.png", "player.png", this);
	ProgressTimer* myhp = hp;
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
	if (target != nullptr) {
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
void DemonSoldier::skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp) {
	//创建进度条
	updateposition();
	ProgressTimer* mp =	this->mp;
	ProgressTimer* myhp = this->hp;
	get_target(this, enemy_hero);
	float mp_up = mp_increment;
	Vec2 fromposition = hero_position;
	Vec2 toposition = target_position;
	auto target_hero = target->mine;
	auto my_hero = mine;
	string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	the->schedule([=](float dt) {
		float newMpPercentage = mp->getPercentage() + mp_up; 
		float MyHpPercentage = myhp->getPercentage();
		if (mp->isVisible() == true) {
			if (hp->getPercentage() == 0) {
				the->unschedule(scheduleKey);
			}
			if (newMpPercentage >= 100.0f) {
				// MP达到100%，重置MP并减少HP
				newMpPercentage = 0.0f;
				// 减少HP的当前值的20%
				if (hp->getPercentage() != 0 && MyHpPercentage != 0) {
					skill(myhp);
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
void DemonSoldier::skill(ProgressTimer* myhp) {
	float newHpPercentage = myhp->getPercentage() + 50;
	if (newHpPercentage > 100)
		newHpPercentage = 100;
	myhp->setPercentage(newHpPercentage);

}
void DemonSoldier::attack(Hero* enemy, HelloWorld* the, Player enemy_hero)
{
	//以敌方为中心展开,下为地方血条
	//ImageSwitcher imageswitch("DemonSoldier.png", "player.png", this);
	ProgressTimer* myhp = hp;
	get_target(this, enemy_hero);
	move_to_target(the, target);
	updateposition();
	auto moveAction = MoveTo::create(0.5f, target_position);
	string scheduleKey1 = "progress_update_hp" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	float hp_maxmax = hp_max;
	srand((time(0)));
    // 生成随机数
    int random_number = rand()%100;
	float internal = (float)random_number/1000+as;
	float damage = atn - target->def;
	float moveDuration = 1.0f; // 移动持续时间，根据需要调整
	if (target != nullptr) {
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
		skill_add(the, enemy_hero,hp);
	}
}
void Shooter::skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp) {
	//创建进度条
	updateposition();
	ProgressTimer* mp = this->mp;
	ProgressTimer* myhp = this->hp;
	get_target(this, enemy_hero);
	float mp_up = mp_increment;
	Vec2 fromposition = hero_position;
	auto target_hero = target->mine;
	string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	the->schedule([=](float dt) {
		float newMpPercentage = mp->getPercentage() + mp_up;
		float MyHpPercentage = myhp->getPercentage();
		if (mp->isVisible() == true) {
			if (hp->getPercentage() == 0) {
				the->unschedule(scheduleKey);
			}
			if (newMpPercentage >= 100.0f) {
				// MP达到100%，重置MP并减少HP
				newMpPercentage = 0.0f;
				if (hp->getPercentage() != 0 && MyHpPercentage!=0) {
					skill(target, the, fromposition, target_hero->getPosition());
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
void Shooter::skill(Hero* target, HelloWorld* the, Vec2 fromposition, Vec2 toposition) {
	auto sprite = Sprite::create("bigbullet.png");//建立一个强化攻击的精灵图像
	if (sprite != nullptr) {
		sprite->setContentSize(Size(70, 70));
		sprite->setPosition(fromposition);
		the->addChild(sprite);
		auto moveto = MoveTo::create(0.1f, toposition);//移动到目标位置
		Hide* hideAction = Hide::create();
		Sequence* sequence = Sequence::create(moveto, hideAction, nullptr);
		sprite->runAction(sequence);
	}
}
void Shooter::attack(Hero* enemy, HelloWorld* the, Player enemy_hero)
{
	//以敌方为中心展开
	//ImageSwitcher imageswitch("DemonSoldier.png", "player.png", this);
	ProgressTimer* myhp = hp;
	ProgressTimer* hp = enemy->hp;
	get_target(this, enemy_hero);
	if (target != nullptr) {
		string scheduleKey = "progress_update_hp" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
		float hp_maxmax = hp_max;
		// 生成随机数
		srand((time(0)));
		int random_number = rand()%100;
		float internal = (float)random_number / 1000 + as;
		float damage = atn - target->def;
		updateposition();
		auto nowposition = hero_position;
		auto toposition = target_position;
		auto target_hero = target->mine;
		auto my_hero = mine;
		auto show_isdie = isdie;
		the->schedule([=](float dt) {
			if (myhp->getPercentage() != 0) {
				//bullet
				auto sprite = Sprite::create("bullet.png");
				sprite->setPosition(nowposition);
				sprite->setContentSize(Size(10, 10));
				auto moveto = MoveTo::create(0.5f, target_hero->getPosition());
				auto hide = Hide::create();
				auto sequence = Sequence::create(moveto, hide, nullptr);
				the->addChild(sprite);
				sprite->runAction(sequence);
			}
			float MyHpPercentage = myhp->getPercentage();
			float hp_nownow = hp->getPercentage() / 100 * hp_maxmax - damage;//damage;
			if (hp_nownow < 0) {
				hp_nownow = 0;
				hp->setVisible(false);
				the->unschedule(scheduleKey);//目标死了退出
			}
			// 更新HP进度条
			if (MyHpPercentage != 0) {
				float newHpPercentage = static_cast<float>(hp_nownow) / hp_maxmax * 100.0f;
				hp->setPercentage(newHpPercentage);
			}
			else
			{
				show_isdie->setVisible(true);
				the->unschedule(scheduleKey);//自己死了退出
			}}, internal, scheduleKey);
		skill_add(the, enemy_hero, hp);
	}
}
void SuperShooter::skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp) {
	//创建进度条
	updateposition();
	ProgressTimer* mp = this->mp;
	ProgressTimer* myhp = this->hp;
	get_target(this, enemy_hero);
	float mp_up = mp_increment;
	Vec2 fromposition = hero_position;
	auto target_hero = target->mine;
	string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	the->schedule([=](float dt) {
		float newMpPercentage = mp->getPercentage() + mp_up;
		float MyHpPercentage = myhp->getPercentage();
		if (mp->isVisible() == true) {
			if (hp->getPercentage() == 0) {
				the->unschedule(scheduleKey);
			}
			if (newMpPercentage >= 100.0f) {
				// MP达到100%，重置MP并减少HP
				newMpPercentage = 0.0f;
				if (hp->getPercentage() != 0 && MyHpPercentage != 0) {
					skill(target, the, fromposition, target_hero->getPosition());
				}
				else
					the->unschedule(scheduleKey);//自己死了或目标死了退出
				// 更新HP进度条
				float newHpPercentage = hp->getPercentage() - 20;
				hp->setPercentage(newHpPercentage);
			}
		}
		mp->setPercentage(newMpPercentage);
		}, 0.5f, scheduleKey);
}
void SuperShooter::skill(Hero* target, HelloWorld* the, Vec2 fromposition, Vec2 toposition) {
	auto sprite = Sprite::create("bigbullet.png");//建立一个强化攻击的精灵图像
	if (sprite != nullptr) {
		sprite->setContentSize(Size(70, 70));
		sprite->setPosition(fromposition);
		the->addChild(sprite);
		auto moveto = MoveTo::create(0.1f, toposition);//移动到目标位置
		Hide* hideAction = Hide::create();
		Sequence* sequence = Sequence::create(moveto, hideAction, nullptr);
		sprite->runAction(sequence);
	}
}
void SuperShooter::attack(Hero* enemy, HelloWorld* the, Player enemy_hero)
{
	//以敌方为中心展开
	//ImageSwitcher imageswitch("DemonSoldier.png", "player.png", this);
	ProgressTimer* myhp = hp;
	ProgressTimer* hp = enemy->hp;
	get_target(this, enemy_hero);
	if (target != nullptr) {
		string scheduleKey = "progress_update_hp" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
		float hp_maxmax = hp_max;
		// 生成随机数
		srand((time(0)));
		int random_number = rand() % 100;
		float internal = (float)random_number / 1000 + as;
		float damage = atn - target->def;
		updateposition();
		auto nowposition = hero_position;
		auto toposition = target_position;
		auto target_hero = target->mine;
		auto my_hero = mine;
		auto show_isdie = isdie;
		the->schedule([=](float dt) {
			if (myhp->getPercentage() != 0) {
				//bullet
				auto sprite = Sprite::create("bullet.png");
				sprite->setPosition(nowposition);
				sprite->setContentSize(Size(10, 10));
				auto moveto = MoveTo::create(0.5f, target_hero->getPosition());
				auto hide = Hide::create();
				auto sequence = Sequence::create(moveto, hide, nullptr);
				the->addChild(sprite);
				sprite->runAction(sequence);
			}
			float MyHpPercentage = myhp->getPercentage();
			float hp_nownow = hp->getPercentage() / 100 * hp_maxmax - damage;//damage;
			if (hp_nownow < 0) {
				hp_nownow = 0;
				hp->setVisible(false);
				the->unschedule(scheduleKey);//目标死了退出
			}
			// 更新HP进度条
			if (MyHpPercentage != 0) {
				float newHpPercentage = static_cast<float>(hp_nownow) / hp_maxmax * 100.0f;
				hp->setPercentage(newHpPercentage);
			}
			else
			{
				show_isdie->setVisible(true);
				the->unschedule(scheduleKey);//自己死了退出
			}}, internal, scheduleKey);
		skill_add(the, enemy_hero, hp);
	}
}
void DemonShooter::skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp) {
	//创建进度条
	updateposition();
	ProgressTimer* mp = this->mp;
	ProgressTimer* myhp = this->hp;
	get_target(this, enemy_hero);
	float mp_up = mp_increment;
	Vec2 fromposition = hero_position;
	auto target_hero = target->mine;
	string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	the->schedule([=](float dt) {
		float newMpPercentage = mp->getPercentage() + mp_up;
		float MyHpPercentage = myhp->getPercentage();
		if (mp->isVisible() == true) {
			if (hp->getPercentage() == 0) {
				the->unschedule(scheduleKey);
			}
			if (newMpPercentage >= 100.0f) {
				// MP达到100%，重置MP并减少HP
				newMpPercentage = 0.0f;
				if (hp->getPercentage() != 0 && MyHpPercentage != 0) {
					skill(target, the, fromposition, target_hero->getPosition());
				}
				else
					the->unschedule(scheduleKey);//自己死了或目标死了退出
				// 更新HP进度条
				float newHpPercentage = hp->getPercentage() - 50;
				hp->setPercentage(newHpPercentage);
			}
		}
		mp->setPercentage(newMpPercentage);
		}, 0.5f, scheduleKey);
}
void DemonShooter::skill(Hero* target, HelloWorld* the, Vec2 fromposition, Vec2 toposition) {
	auto sprite = Sprite::create("bigbullet.png");//建立一个强化攻击的精灵图像
	if (sprite != nullptr) {
		sprite->setContentSize(Size(70, 70));
		sprite->setPosition(fromposition);
		the->addChild(sprite);
		auto moveto = MoveTo::create(0.1f, toposition);//移动到目标位置
		Hide* hideAction = Hide::create();
		Sequence* sequence = Sequence::create(moveto, hideAction, nullptr);
		sprite->runAction(sequence);
	}
}
void DemonShooter::attack(Hero* enemy, HelloWorld* the, Player enemy_hero)
{
	//以敌方为中心展开
	//ImageSwitcher imageswitch("DemonSoldier.png", "player.png", this);
	ProgressTimer* myhp = hp;
	ProgressTimer* hp = enemy->hp;
	get_target(this, enemy_hero);
	if (target != nullptr) {
		string scheduleKey = "progress_update_hp" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
		float hp_maxmax = hp_max;
		// 生成随机数
		srand((time(0)));
		int random_number = rand() % 100;
		float internal = (float)random_number / 1000 + as;
		float damage = atn - target->def;
		updateposition();
		auto nowposition = hero_position;
		auto toposition = target_position;
		auto target_hero = target->mine;
		auto my_hero = mine;
		auto show_isdie = isdie;
		the->schedule([=](float dt) {
			if (myhp->getPercentage() != 0) {
				//bullet
				auto sprite = Sprite::create("bullet.png");
				sprite->setPosition(nowposition);
				sprite->setContentSize(Size(10, 10));
				auto moveto = MoveTo::create(0.5f, target_hero->getPosition());
				auto hide = Hide::create();
				auto sequence = Sequence::create(moveto, hide, nullptr);
				the->addChild(sprite);
				sprite->runAction(sequence);
			}
			float MyHpPercentage = myhp->getPercentage();
			float hp_nownow = hp->getPercentage() / 100 * hp_maxmax - damage;//damage;
			if (hp_nownow < 0) {
				hp_nownow = 0;
				hp->setVisible(false);
				the->unschedule(scheduleKey);//目标死了退出
			}
			// 更新HP进度条
			if (MyHpPercentage != 0) {
				float newHpPercentage = static_cast<float>(hp_nownow) / hp_maxmax * 100.0f;
				hp->setPercentage(newHpPercentage);
			}
			else
			{
				show_isdie->setVisible(true);
				the->unschedule(scheduleKey);//自己死了退出
			}}, internal, scheduleKey);
		skill_add(the, enemy_hero, hp);
	}
}
void Hero::updateposition()
{
	hero_position = mine->getPosition();
}
void Hero::move_to_target(HelloWorld* the,Hero* enemy)
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