#ifndef HERO_H
#define HERO_H
#pragma once
#include "cocos2d.h"
#include"player.h"
#include"heroAction.h"
#include"const.h"
#include"ApplyLittleHero.h"
#include"weapon.h";
using namespace std;
using namespace cocos2d;
class Hero :public cocos2d::Node{
	friend class Player;
	friend class Weapon;
	friend class ImageSwitcher;
	friend class ApplyLittleHero;
protected:
public:
	float atn;//物理攻击力
	float def;//物理防御力
	float hp_max;//生命值
	float hp_now;
	float mp_max;//蓝条
	float mp_now;
	float as=1;//attack speed 攻速
	float ch=0.1;//critical hit 暴击
	float ch_ma=1.5;//magnification 倍率
	float ran;//range 射程
	int price;
	int seat=0;
	float mp_increment=10;
	bool is_on_board=1;//是否上场	
	double target_distance;
	bool islive=1;
	Sprite* mine = nullptr;//自己
	Vec2 hero_position;
	int kind[4] = {0};
	int level = 1;
	Weapon* wea=nullptr;
	void updateposition();
	ProgressTimer* hp = ProgressTimer::create(Sprite::create("hp_progress_bar.png"));
	ProgressTimer* mp = ProgressTimer::create(Sprite::create("mp_progress_bar.png"));
	Sprite* isdie;
	Sprite* getmine() const
	{ 
		return mine;
	}
	Hero* gettarget(Player enemy) const {
		return enemy.target;
	}
	Vec2 getposition() const {
		return mine->getPosition();
	}
	void setclick(int num)
	{
		click = num;
	}
	int getclick() const
	{
		return click;
	}
	int click = 0;
	int No;
	ApplyLittleHero* the;
	void enableMouseControl(bool enabled,ApplyLittleHero* the);
	cocos2d::EventListenerMouse* _Listener=nullptr; 
	bool listenerinit(); //鼠标点击监听器
	Hero::Hero(int num,int lv, ApplyLittleHero* ApplyLittleHero){
		level = lv;
		isdie = Sprite::create("die.png");
		switch (num)
		{
			case 1:
				sprite = Sprite::create("soldier.png");
				break;
			case 2:
				sprite = Sprite::create("supersoldier.png");
				break;
			case 3:
				sprite = Sprite::create("Demonsoldier.png");
				break;
			case 4:
				sprite = Sprite::create("shooter.png");
				break;
			case 5:
				sprite = Sprite::create("supershooter.png");
				break;
			case 6:
				sprite = Sprite::create("demonshooter.png");
				break;
		}
		mine = sprite;
		mine->setContentSize(Size(50, 50));
		//更新位置
		hp->setType(ProgressTimer::Type::BAR);
		hp->setScaleX(0.25); // 宽度缩小为原来的一半
		hp->setScaleY(0.5); // 高度放大为原来的两倍
		hp->setPercentage(100);
		hp->setMidpoint(Vec2(20, 30)); // 进度条起点位置
		hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		hp->setPosition(Vec2(20, 30)); // 进度条位置
		if (hp->getParent() == nullptr)
			mine->addChild(hp);
		mp->setType(ProgressTimer::Type::BAR);
		mp->setScaleX(0.25); // 宽度缩小为原来的一半
		mp->setScaleY(0.5); // 高度放大为原来的两倍
		mp->setPercentage(40);
		mp->setMidpoint(Vec2(20, 40)); // 进度条起点位置
		mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		mp->setPosition(Vec2(20, 40)); // 进度条位置
		if (mp->getParent() == nullptr)
			mine->addChild(mp);
		isdie->setContentSize(Size(20, 20));
		isdie->setPosition(Vec2(10, 10));
		isdie->setVisible(false);
		mine->addChild(isdie);
		//以上为血条蓝条是否死亡三点的初始化
		the = ApplyLittleHero;
		atn = 20 * level;
		def = 10 * level;
		as = 1;
		is_on_board = 0;
		ran = 10 * level;
		hp_max = 150 * level;
		hp_now = 150 * level;
		mp_max = 10;
		mp_increment = 10;
		mp_now = 4;
	}
	Sprite* sprite = nullptr;
	void hpsetmax() {
		hp->setPercentage(100);
	}
	void move_to_target(Player enemy_hero);
	void attack(Hero* enemy, ApplyLittleHero* the, Player enemy_hero);
	void skill_add(ApplyLittleHero* the, Player enemy_hero, ProgressTimer* hp);//根据时间增加蓝条
	void skill(Hero* target, ApplyLittleHero* the, Vec2 fromposition, Vec2 toposition,ProgressTimer* myhp) const;//蓝条封顶放技能
};
#endif