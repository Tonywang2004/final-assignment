#ifndef _HERO_H_
#define _HERO_H_

#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Bank.h"
#include "Weapon.h"
#include "Const.h"
USING_NS_CC;
using namespace std;

class Hero :public Sprite {
	friend class Player;
protected:
	int ad;//攻击力
	int def;//防御力
	int hp_max;//最大生命值
	int hp_now;//当前生命值
	int mp_max = 5;//蓝条
	int mp_now = 2;//当前法力值
	int mp_per_second = 1;//每秒获得的蓝量
	float as = 1;//attack speed 攻速
	float ch_rate = 0;//critical hit rate暴击率
	float ch_ma = 2.0;//magnification 暴击伤害倍率
	float ran;//range 射程
	Vec2 hero_postion;//英雄在场上的位置
	int seat = 0;//英雄在备战席上的序号,范围为1~MAX_STORAGE_NUM，即1~4
	int kind[4] = { 0 };//羁绊：射手、战士、恶魔
	int level = 1;//当前英雄的等级，即星数
	int price = 0;//价格
	Weapon weapon = NULL;//英雄的装备
	bool is_on_board = false;//记录英雄是否在场上
	bool click = false;//标志英雄是否被鼠标选中
	int No;//英雄的序号
public:
	//virtual void ultimate() = 0;
	Hero() {
		ad = 0;
		def = 0;
		hp_max = 0;
		hp_now = 0;
		mp_max = 0;
		mp_now = 0;
		mp_per_second = 1;
		as = 1;
		ch_rate = 0;
		ch_ma = 2.0;
		ran = 1;
		hero_postion = Vec2(0, 0);
		seat = 0;
		for (int i = 0; i < 4; i++)
			kind[i] = 0;
		level = 1;
		price = 0;
		weapon = NULL;
		is_on_board = false;
		click = false;
		No = 0;
	}
	Hero(int index) {
		No = index;
	}
	//带默认参数的构造函数
	bool operator==(const Hero& other) const {
		return No == other.No;
	}
	Hero& operator=(const Hero& other) {
		return Hero(other.No);
	}
};

#endif 

