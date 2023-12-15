#ifndef _WEAPON_H_
#define _WEAPON_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "player.h"
#include "const.h"
USING_NS_CC;

class Weapon :public Sprite {
	friend class Player;
	friend class Role;
	friend class Hero;
private:
	string image;
	int ad = 0;//attack damage攻击力
	int ap = 0;//ability power法强
	int def = 0;//物理防御力
	int mr = 0;//magic resistance 魔抗
	int hp_max = 0;//最大生命值
	int mp_per_second = 0;//每秒获得的蓝量
	float as = 0;//attack speed 攻速
	float ch_rate = 0;//critical hit rate暴击率
	float ch_ma = 0;//critical hit magnification 暴击伤害倍率
public:
	Weapon() {};//带默认参数的构造函数
	Weapon(string s, int AD, int AP, int DEF, int MR, int HP_MAX, int MP_PER_SECOND, float AS, float CH_RATE, float CH_MA) {
		auto weapon = Weapon::create(image);
		ad = AD;
		ap = AP;
		def = DEF;
		mr = MR;
		hp_max = HP_MAX;
		mp_per_second = MP_PER_SECOND;
		as = AS;
		ch_rate = CH_RATE;
		ch_ma = CH_MA;
	}
};
#endif
