#ifndef _CONST_H_
#define _CONST_H_

#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "HelloWorldScene.h"
#include "Weapon.h"
#include <map>
#include <utility>
USING_NS_CC;
using namespace std;

const int HERO_TYPES = 6;//英雄总种类
const int cardtypes[3] = { 2,2,2 };//卡池中1费卡至3费卡的分别有2，2，2种
const int cardnums[3] = { 12,12,9 };//其中3费卡每种有9张，其余每种卡有12张

//各种羁绊：射手、战士、恶魔
#define SHOOTER 1
#define SOLDIER 2
#define DEMON 3

//等级经验表
const int exp_level_up[5] = { 0,2,6,15,36};
//exp_level_up[i]表示从i-1级升至i级需要的经验
//每回合结束后经验自动+2，故第一回合后可以升至2级

const int MAX_LEVEL = 5;//最高等级
const int MAX_STORAGE_NUM = 4;//备战席的最大容纳数量

//基础装备：弓，铠甲，金铲铲
#define BOW 1
#define ARMOR 2
#define SPATULA 3
//合成装备：
#define HURRICANE 4 //卢安娜的飓风
#define THORNMAIL 5 //反甲
#define NATUREFORCE 6 //自然之力，加1人口上限（只可拥有1件）
#define SHIELDBOW 7 //盾弓
#define EXTRASHOOTER 8 //额外射手羁绊
#define EXTRASOLDIER 9 //额外战士羁绊

//装备基础属性
const int weapon_ad[10] = { 0,10,0,0,20,0,0,10,10,0 };
const int weapon_def[10] = { 0,0,10,0,0,20,0,10,0,10 };
const float weapon_as[10] = { 0,0.1,0,0,0.2,0,0,0.1,0.1,0 };

//装备合成路线
map<pair<int, int>, int> WeaponCombination = {
	{{BOW,BOW},HURRICANE},{{ARMOR,ARMOR},THORNMAIL},{{SPATULA,SPATULA},NATUREFORCE},{{BOW,ARMOR},SHIELDBOW},{{BOW,SPATULA},EXTRASHOOTER},{{ARMOR,SPATULA},EXTRASOLDIER}
};

//备战席的位置
Vec2 storage_position[MAX_STORAGE_NUM + 1];
#endif

