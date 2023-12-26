#include<iostream>
#include "HelloWorldScene.h"
#include "Hero.h"
using namespace std;
using namespace cocos2d;
extern Player my_hero;
extern Player enemy_hero;
void Ghostride::skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp) {
	//创建进度条
	updateposition();
	ProgressTimer* mp = nullptr;
	mp = ProgressTimer::create(Sprite::create("mp_progress_bar.png"));
	mp->setType(ProgressTimer::Type::BAR);
	mp->setScaleX(0.25); // 宽度缩小为原来的一半
	mp->setScaleY(0.5); // 高度放大为原来的两倍
	mp->setMidpoint(Vec2(hero_position.x, hero_position.y - 20)); // 进度条起点位置
	mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
	mp->setPosition(hero_position.x, hero_position.y - 20); // 进度条位置
	mp->setPercentage(mp_now * 100 / mp_max);
	the->addChild(mp); // 将进度条添加到场景中
	get_target(this, enemy_hero);
	float mp_up = mp_increment;
	Vec2 fromposition = hero_position;
	Vec2 toposition = target_position;
	string scheduleKey = "progress_update_" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	the->schedule([=](float dt) {
		float newMpPercentage = mp->getPercentage() + mp_up;
		if (newMpPercentage >= 100.0f) {
			// MP达到100%，重置MP并减少HP
			newMpPercentage = 0.0f;
			// 减少HP的当前值的20%
			skill(target, the, fromposition, toposition);
			// 更新HP进度条
			float newHpPercentage = hp->getPercentage() - 10;
			hp->setPercentage(newHpPercentage);
		}
		mp->setPercentage(newMpPercentage);
		}, 0.5f, scheduleKey);
}
void Ghostride::skill(Hero* target, HelloWorld* the, Vec2 fromposition, Vec2 toposition) {
	auto sprite = Sprite::create("ghostride.png");//建立一个强化攻击的精灵图像
	sprite->setContentSize(Size(100, 100));
	sprite->setPosition(fromposition);
	the->addChild(sprite);
	auto moveto = MoveTo::create(0.1f, toposition);//移动到目标位置
	Hide* hideAction = Hide::create();
	Sequence* sequence = Sequence::create(moveto, hideAction, nullptr);
	sprite->runAction(sequence);
}
void Hero::updateposition()
{
	hero_position = mine->getPosition();
}
void Ghostride::attack(Hero* enemy, HelloWorld* the, Player enemy_hero)
{
	//以敌方为中心展开
	ImageSwitcher imageswitch("ghostride.png", "player.png", this);
	get_target(this, enemy_hero);
	ProgressTimer* hp = nullptr;
	hp = ProgressTimer::create(Sprite::create("hp_progress_bar.png"));
	hp->setType(ProgressTimer::Type::BAR);
	hp->setScaleX(0.25); // 宽度缩小为原来的一半
	hp->setScaleY(0.5); // 高度放大为原来的两倍
	hp->setPercentage(100);
	hp->setMidpoint(Vec2(target_position.x, target_position.y - 30)); // 进度条起点位置
	hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
	hp->setPosition(target_position.x, target_position.y - 30); // 进度条位置
	the->addChild(hp);
	string scheduleKey = "progress_update_hp" + std::to_string(reinterpret_cast<std::uintptr_t>(this));//change the key word
	float hp_maxmax = hp_max;
	float internal = as;
	float danmage = atn - enemy->def + matk - enemy->mr;
	the->schedule([=](float dt) {
		float hp_nownow = hp->getPercentage() - danmage;
		if (hp_nownow < 0)
			hp_nownow = 0;
		// 更新HP进度条
		float newHpPercentage = static_cast<float>(hp_nownow) / hp_maxmax * 100.0f;
		hp->setPercentage(newHpPercentage);
		}, internal, scheduleKey);
	skill_add(the, enemy_hero, hp);
}
void Hero::get_target(Hero* hero, Player enemy)
{
	double minDistance = 99999999;
	int index = 0;
	//获取距离最近的英雄
	if (enemy.hero_for_player.size() != 0) {
		for (int i = 0; i < enemy.hero_for_player.size(); i++)
		{
			double delta_position_square = (enemy.hero_for_player[i]->mine->getPosition().x - hero->mine->getPosition().x) * (enemy.hero_for_player[i]->mine->getPosition().x - hero->mine->getPosition().x) + (enemy.hero_for_player[i]->mine->getPosition().y - hero->mine->getPosition().y) * (enemy.hero_for_player[i]->mine->getPosition().y - hero->mine->getPosition().y);
			if (minDistance > delta_position_square) {
				minDistance = delta_position_square;
				index = i;
			}
		}
		//目标变化
		target = enemy.hero_for_player[index];
		target_position = target->mine->getPosition();
		target_distance = sqrt(minDistance);
	}
	else
		target = nullptr;
}
