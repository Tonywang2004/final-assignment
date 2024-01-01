#ifndef _WEAPON_H_
#define _WEAPON_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "player.h"
#include "const.h"
USING_NS_CC;
//装备合成路线
class Weapon {
	friend class Player;
	friend class Role;
	friend class Hero;
private:
	int ad = 0;//attack damage攻击力
	int ap = 0;//ability power法强
	int def = 0;//物理防御力
	int mr = 0;//magic resistance 魔抗
	int hp_max = 0;//最大生命值
	int mp_per_second = 0;//每秒获得的蓝量
	float as = 0;//attack speed 攻速
	float ch_rate = 0;//critical hit rate暴击率
	float ch_ma = 0;//critical hit magnification 暴击伤害倍率
	int No;
	std::map<std::pair<int, int>, int> combination = {
	{{WAND,SWORD},TECHGUN},{{WAND,ARMOR},HOURGLASS},{{WAND,SPATULA},EXTRAMAGICIAN},{{SWORD,ARMOR},MALMORTIUS},{{SWORD,SPATULA},EXTRASHOOTER},
	{{ARMOR,SPATULA},EXTRASOLDIER},{{WAND,WAND},DEATHCAP},{{SWORD,SWORD},INFINITYEDGE},{{ARMOR,ARMOR},MERCURYCLOAK},{{SPATULA,SPATULA},NATUREFORCE}
	};
public:
	Weapon(int number) {
		//weapon = Weapon::create(image[number]);
		//ad = AD[number];
		//ap = AP[number];
		//def = DEF[number];
		//mr = MR[number];
		//hp_max = HP_MAX[number];
		//mp_per_second = MP_PER_SECOND[number];
		//as = AS[number];
		//ch_rate = CH_RATE[number];
		//ch_ma = CH_MA[number];
	}
	Sprite* weapon;
	Weapon* check_combination(Weapon* fir, Weapon* sec);
};
#endif
