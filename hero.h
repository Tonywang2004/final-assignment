#ifndef _HERO_H_
#define _HERO_H_

#pragma once
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "bank.h"
#include "weapon.h"
#include "const.h"
USING_NS_CC;
using namespace std;

class Card;

class Hero :public Sprite {
	friend class Card;
	friend class Shop;
	friend class Player;
	friend class Role;
	friend class ImageSwitcher;
protected:
	int ad;//attack damage攻击力
	int ap;//ability power法强
	int def;//物理防御力
	int mr;//magic resistance 魔抗
	int hp_max;//最大生命值
	int hp_now;//当前生命值
	int mp_max = 5;//蓝条
	int mp_now = 2;//当前法力值
	int mp_per_second = 1;//每秒获得的蓝量
	float as = 1;//attack speed 攻速
	float ch_rate = 0;//critical hit rate暴击率
	float ch_ma = 2.0;//magnification 暴击伤害倍率
	float ran;//range 射程
	Vec2 postion;//英雄在场上的位置
	vector<int>kind;//羁绊：射手、法师、战士、刺客、恶魔、天使、亡灵
	int level = 1;//当前英雄的等级，即星数
	Weapon weapon[3];//英雄的装备栏
	bool is_on_board;//记录英雄是否在场上
	int No;//英雄的序号
public:
	//virtual void ultimate() = 0;
	Hero() {
		No = pow(100, level) * No;
	}//带默认参数的构造函数
	bool operator==(const Hero& other) const {
		return No == other.No;
	}
};

//卡牌
class Card {
	friend class Player;
private:
	int price;//价格
	string image;//卡牌图片
	Hero hero;//卡牌对应的英雄
public:
	Card(int p, string s, int x = 0, int y = 0, int length = 40, int width = 40) :price(p), image(s) {
		// 加载卡牌图片作为精灵
		// 默认位置为(0,0)，矩形默认长宽分别为40、40
		auto hero = Hero::create(image,Rect(x,y,length,width));
	}
};
#endif 

