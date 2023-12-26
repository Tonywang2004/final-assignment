#ifndef _PLAYER_H_
#define _PLAYER_H_

#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "HelloWorldScene.h"
#include "Bank.h"
#include "Weapon.h"
#include "Const.h"
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
	int level = 1;//等级
	int max_hero_num = 0;//可上场的英雄最大数量
	int hero_alive = 0;//每局对弈后存活的英雄数量
	int hero_num = 0;//场上的英雄数量
	int storage_num = 0;//备战席的英雄数量
	int kind[4] = { 0 };//羁绊：射手、战士、恶魔
	bool lock = false;//用于锁定商店
	Hero storage[MAX_STORAGE_NUM + 1];//观众席，用于存放玩家已经购买但未上场的英雄
	vector<Hero> hero_on_board;//上场的英雄
	vector<Weapon> weapon_for_player;//玩家已获得且未给英雄装上的装备
	vector<Hero> shop_for_player;//玩家的商店
	bool HasNatureForce = false;//标志是否拥有装备“自然之力”，拥有则加1人口上限
public:
	Player(){}//构造函数
	void switch_lock();//锁定/解锁商店
	void level_up();//升级
	void cal_max_hero_num() { max_hero_num = level + HasNatureForce; }//可上场的最大英雄数量等于等级，拥有装备“自然之力”则加1人口上限
	void buy_exp();//购买经验
	void weapon_on(Hero *hero, Weapon *weapon);//英雄装上装备
	void weapon_off(Hero *hero);//英雄卸下装备
	bool buy_check(Hero *hero);//判断是否能够购买英雄
	void buy_hero(Hero *hero);// 购买英雄
	void sell_hero(Hero *hero);//售卖英雄
	void refreshshop();//刷新商店
	void on_board(Hero *hero);//将备战席上的英雄移上场
	void off_board(Hero *hero);//将场上的英雄移到备战席中
	void syn_hero();//将3个低星英雄自动合成1个高星英雄
	void syn_hero(Hero *hero);//将3个低星英雄自动合成1个高星英雄（重载）
	void syn_weapon(Weapon *fir, Weapon *sec);//合成装备
	bool islose() const { return hp <= 0; }//判断是否输掉游戏
	int damage(Player winner, bool iswin);//计算每小局的伤害
};

#endif
