#ifndef _PLAYER_H_
#define _PLAYER_H_

#pragma once
#include "cocos2d.h"
#include "hero.h"
#include "HelloWorldScene.h"
#include "bank.h"
#include "weapon.h"
#include "const.h"
#include <vector>
USING_NS_CC;
using namespace std;

//设置一个玩家类，包含玩家的金钱，经验，等级，英雄数，羁绊
class Player {
private:
	int stage = 0;//记录当前游戏阶段
	int hp = 100;//玩家生命值
	int money = 0;//金钱
	int exp = 0;//经验
	int level = 0;//等级
	int max_hero_num = 0;//可上场的英雄最大数量
	int hero_num = 0;//存活的英雄数量
	int storage_num = 0;//备战席的英雄数量
	int kind[7] = { 0 };//羁绊：射手、法师、战士、刺客、恶魔、天使、亡灵
	bool lock;//用于锁定商店
	vector<Hero> storage;//观众席，用于存放玩家已经购买但未上场的英雄
	vector<Hero> hero_on_board;//上场的英雄
	vector<Weapon> weapon_for_player;//玩家已获得且未给英雄装上的装备
	vector<Card>shop_for_player;//玩家的商店
public:
	void switch_lock();//锁定/解锁商店
	void level_up();//升级
	void cal_max_hero_num() { max_hero_num = level; }//可上场的最大英雄数量等于等级
	void buy_exp();//购买经验
	void buy_card(int index);// 购买卡牌，index为商店中5张卡牌的标记
	void sell_card(Card card);//售卖卡牌
	void refreshshop();//刷新商店
	void on_board(Card card);//将备战席上的英雄移上场
	void off_board(Card card);//将场上的英雄移到备战席中
	void syn_hero();//将3个低星英雄自动合成1个高星英雄
	bool islose() const { return hp <= 0; }//判断是否输掉游戏
	int damage(Player winner, bool iswin);//计算每小局的伤害

};

//小小英雄
class Role :public Sprite {
private:
	string image;
	Vec2 position;
public:
	Role(string s, int x = 0, int y = 0, int length = 40, int width = 40) :image(s), position(Vec2(x, y)) {
		auto role = Role::create(image, Rect(x, y, length, width));
		//默认位置为(0,0)，矩形默认长宽分别为40、40
	}
	void move();
};

#endif
