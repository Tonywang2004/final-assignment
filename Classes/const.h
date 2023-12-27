#ifndef _CONST_H_
#define _CONST_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "ApplyLittleHero.h"
#include<map>
#include<algorithm>
#include<utility>
#include<string>

USING_NS_CC;
const int cardtypes[4] = { 4,3,3,2 };//卡池中1费卡至4费卡的分别有4，3，3，2种
const int cardnums[4] = { 12,12,12,9 };//其中4费卡每种有9张，其余每种卡有12张

//各种羁绊：射手、法师、战士、刺客、恶魔、天使、亡灵
#define SHOOTER 0
#define MAGICIAN 1
#define SOLDIER 2
#define ASSASSIN 3
#define DEMON 4
#define ANGEL 5
#define GHOST 6
#define Demonsoldier 1
//基础装备：魔杖，剑，铠甲，金铲铲
#define WAND 1
#define SWORD 2
#define ARMOR 3
#define SPATULA 4
//合成装备：
#define TECHGUN 5 //科技枪
#define HOURGLASS 6 //沙漏
#define EXTRAMAGICIAN 7 //额外法师羁绊
#define MALMORTIUS 8 //饮魔刀
#define EXTRASHOOTER 9 //额外射手羁绊
#define EXTRASOLDIER 10 //额外战士羁绊
#define DEATHCAP 11 //法帽
#define INFINITYEDGE 12 //无尽之刃
#define MERCURYCLOAK 13 //水银斗篷
#define NATUREFORCE 14 //自然之力，加1人口上限（只可拥有1件）

const Vec2 storage_position[5] = { {0,0}, {50,50},{50,100},{50,150} ,{50,200} };
//等级经验表
const int exp_level_up[9] = { 0,0,2,6,10,20,36,56,80 };
//exp_level_up[i]表示从i-1级升至i级需要的经验
//每回合结束后经验自动+2，故第一回合后可以升至2级
const int MAX_LEVEL = 8;//最高等级
const int MAX_STORAGE_NUM = 4;//备战席的最大容纳数量
#endif

