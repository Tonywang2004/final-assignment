#ifndef _WEAPON_H_
#define _WEAPON_H_

#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "Player.h"
#include "Const.h"
USING_NS_CC;

class Weapon :public Sprite {
	friend class Player;
	friend class Hero;
private:
	Sprite* weapon;
	string image;
	int ad = 0;//攻击力
	int def = 0;//防御力
	int hp_max = 0;//最大生命值
	float as = 0;//attack speed 攻速
	float ch_rate = 0;//critical hit rate暴击率
	bool click = false;//标志装备是否被鼠标选中
	int No;//标志
public:
	Weapon(int index) {
		weapon = Weapon::create(image);
		No = index;
		ad = weapon_ad[No];
		def = weapon_def[No];
		as = weapon_as[No];
		hp_max = 0;
		ch_rate = 0;
		if (No == HURRICANE)
			ch_rate = 0.2, as += 0.1, ad += 10;
		if (No == THORNMAIL)
			hp_max = 200, def += 15;
		if (No == SHIELDBOW)
			hp_max = 100, ad += 10, def += 5;
	}
	bool operator<(const Weapon& other) {
		return No < other.No;
	}
	bool operator==(const Weapon& other) {
		return No == other.No;
	}
	Weapon& operator=(const Weapon& other) {
		return Weapon(other.No);
	}
};
#endif
