#ifndef _CONST_H_
#define _CONST_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "Weapon.h"
#include <map>
#include <utility>
USING_NS_CC;
using namespace std;

const int HERO_TYPES = 6;//英雄总种类
const int cardnums[7] = { 0,12,12,12,12,9,9 };//3费卡每种有9张，其余每种卡有12张

//各种英雄
//1费卡
const int _Soldier_ = 1;
const int _Shooter_ = 2;
//2费卡
const int _Supersoldier_ = 3;
const int _Supershooter_ = 4;
//3费卡
const int _Demonsoldier_ = 5;
const int _Demonshooter_ = 6;

//各种羁绊：战士、射手、恶魔
const int SOLDIER = 1;
const int SHOOTER = 2;
const int DEMON = 3;

//等级经验表
const int exp_level_up[5] = { 0,2,6,15,36};
//exp_level_up[i]表示从i-1级升至i级需要的经验
//每回合结束后经验自动+2，故第一回合后可以升至2级

const int MAX_LEVEL = 5;//最高等级
const int MAX_STORAGE_NUM = 4;//备战席的最大容纳数量

//装备种类
const int WEAPON_TYPES = 9;
//基础装备：弓，铠甲，金铲铲
const int BOW = 1;
const int ARMOR = 2;
const int SPATULA = 3;
//合成装备：
const int HURRICANE = 4; //卢安娜的飓风
const int THORNMAIL = 5; //反甲
const int NATUREFORCE = 6; //自然之力，加1人口上限（只可拥有1件）
const int SHIELDBOW = 7; //盾弓
const int EXTRASHOOTER = 8; //额外射手羁绊
const int EXTRASOLDIER = 9; //额外战士羁绊

//装备基础属性
const int weapon_atn[10] = { 0,10,0,0,20,0,0,10,10,0 };
const int weapon_def[10] = { 0,0,10,0,0,20,0,10,0,10 };
const float weapon_as[10] = { 0,0.1,0,0,0.2,0,0,0.1,0.1,0 };


//强化符文 Rune：强化伤害，减免伤害，额外经验，额外金钱，生命回复
const int RUNE_TYPES = 5;
//强化伤害：每次对局获胜后造成伤害+5
const int MOREDAMAGE = 1;
//减免伤害：每次对局失败后收到伤害-3
const int LESSDAMAGE = 2;
//额外经验：每次对局结束后额外获得4经验（不能超过等级上限）
const int EXTRAEXP = 3;
//额外金钱：每次对局结束后额外获得2金钱
const int EXTRAMONEY = 4;
//生命回复：立即回复20点生命值（可超过生命值上限）
const int RECOVERY = 5;
#endif
