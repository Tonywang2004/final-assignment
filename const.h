#ifndef _CONST_H_
#define _CONST_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "HelloWorldScene.h"
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

//等级经验表
const int exp_level_up[9] = { 0,0,2,6,10,20,36,56,80 };
//exp_level_up[i]表示从i-1级升至i级需要的经验
//每回合结束后经验自动+2，故第一回合后可以升至2级

const int MAX_LEVEL = 8;//最高等级
const int MAX_STORAGE_NUM = 6;//备战席的最大容纳数量
#endif

