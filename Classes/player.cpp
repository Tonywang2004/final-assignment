#include "cocos2d.h"
#include "Hero.h"
#include "weapon.h"
#include "Player.h"
#include "ApplyLittleHero.h"
#include "const.h"
#include <vector>
#include <set>
#include <map>
#include <utility>
USING_NS_CC;
using namespace std;

void Player::cal_kind() {
	memset(kind, 0, sizeof(kind));
	for (int i = 0; i < hero_on_board.size(); i++) {
		for (int j = 1; j <= 3; j++)
			kind[j] += hero_on_board[i]->kind[j];
	}
}

void Player::use_kind() {
	cal_kind();
	//3战士羁绊
	if (kind[1] >= 3) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->hp_max += 100;
			hero_on_board[i]->def += 20;
		}
	}
	//2战士羁绊
	else if (kind[1] >= 2) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->hp_max += 50;
			hero_on_board[i]->def += 10;
		}
	}

	//3法师羁绊
	if (kind[2] >= 3) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->atn += 10;
			hero_on_board[i]->as += 0.1;
		}
	}
	//2法师羁绊
	else if (kind[2] >= 2) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->atn += 20;
			hero_on_board[i]->as += 0.2;
		}
	}

	//2恶魔羁绊
	if (kind[3] >= 2) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->ch += 0.2;
			hero_on_board[i]->ch_ma += 0.5;
		}
	}
	//1恶魔羁绊
	else if (kind[3] >= 1) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->ch += 0.1;
			hero_on_board[i]->ch_ma += 0.3;
		}
	}
}

void Player::cancel_kind() {
	cal_kind();
	//3战士羁绊
	if (kind[1] >= 3) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->hp_max -= 100;
			hero_on_board[i]->def -= 20;
		}
	}
	//2战士羁绊
	else if (kind[1] >= 2) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->hp_max -= 50;
			hero_on_board[i]->def -= 10;
		}
	}

	//3法师羁绊
	if (kind[2] >= 3) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->atn -= 10;
			hero_on_board[i]->as -= 0.1;
		}
	}
	//2法师羁绊
	else if (kind[2] >= 2) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->atn -= 20;
			hero_on_board[i]->as -= 0.2;
		}
	}

	//2恶魔羁绊
	if (kind[3] >= 2) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->ch -= 0.2;
			hero_on_board[i]->ch_ma -= 0.5;
		}
	}
	//1恶魔羁绊
	else if (kind[3] >= 1) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			hero_on_board[i]->ch -= 0.1;
			hero_on_board[i]->ch_ma -= 0.3;
		}
	}
}

void Player::switch_lock() {
	lock = 1 - lock;
}

void Player::level_up() {
	exp -= exp_level_up[level];
	if (level < MAX_LEVEL)
		level++;
	cal_max_hero_num();
}

void Player::buy_exp() {
	if (money >= 4) {
		money -= 4;
		exp += 4;
		if (exp >= exp_level_up[level] && level < MAX_LEVEL)
			level_up();
	}
}

void Player::weapon_on(Hero* hero, Weapon* weapon) {
	for (int i = 0; i < weapon_for_player.size(); i++) {
		if (weapon_for_player[i]->click) {
			weapon_for_player.erase(weapon_for_player.begin() + i);
			break;
		}
	}
	hero->atn += weapon->atn;
	hero->def += weapon->def;
	hero->as += weapon->as;
	hero->hp_max += weapon->hp_max;
	hero->ch += weapon->ch;
	if (weapon->No == EXTRASHOOTER)
		hero->kind[SHOOTER]++;
	if (weapon->No == EXTRASOLDIER)
		hero->kind[SOLDIER]++;
	Weapon* Newweapon = new Weapon(weapon->No);
	hero->wea = Newweapon;
	cal_kind();
}

void Player::weapon_off(Hero* hero) {
	hero->atn -= hero->wea->atn;
	hero->def -= hero->wea->def;
	hero->as -= hero->wea->as;
	hero->hp_max -= hero->wea->hp_max;
	hero->ch -= hero->wea->ch;
	if (hero->wea->No == EXTRASHOOTER)
		hero->kind[SHOOTER]--;
	if (hero->wea->No == EXTRASOLDIER)
		hero->kind[SOLDIER]--;
	hero->wea = NULL;
	weapon_for_player.push_back(hero->wea);
	cal_kind();
}

bool Player::buy_check(Hero* hero) {
	//判断当前金钱是否足够
	if (money < hero->price)
		return false;
	//如果有空位则可以购买
	if (hero_num < max_hero_num || storage_num < MAX_STORAGE_NUM)
		return true;
	//若没有空位且购买后可以立即进行合成，则也可以购买
	int arr[HERO_TYPES + 1] = { 0 };
	arr[hero->No]++;
	for (int i = 0; i < hero_on_board.size(); i++)
		arr[hero_on_board[i]->No]++;
	for (int i = 1; i <= MAX_STORAGE_NUM; i++)
		arr[storage[i]->No]++;
	for (int i = 1; i <= HERO_TYPES; i++) {
		if (arr[i] >= 3)
			return true;
	}
	return false;
}

//在调用此函数之前一定要先调用buy_check()函数判断是否能进行购买
void Player::buy_hero(Hero* hero) {
	// 将已购买的卡牌从在售列表中移除
	for (int i = 0; i < shop_for_player.size(); i++) {
		if (shop_for_player[i]->click) {
			shop_for_player.erase(shop_for_player.begin() + i);
			money -= shop_for_player[i]->price;
			break;
		}
	}

	//购买后立即检查是否能进行英雄合成
	syn_hero(hero);//此函数将购买的英雄放入备战席/场地，并检验是否能进行英雄的合成
	syn_hero();//可能会合成三级英雄，所以需要调用第二次

	cal_kind();
}

void Player::sell_hero(Hero* hero) {
	weapon_off(hero);
	if (hero->is_on_board) {
		for (int i = 0; i < hero_on_board.size(); i++) {
			if (hero_on_board[i]->click) {
				hero_on_board.erase(hero_on_board.begin() + i);
				hero_num--;
			}
		}
	}
	else {
		for (int i = 1; i <= MAX_STORAGE_NUM; i++) {
			if (storage[i]->click) {
				storage[i] = NULL;
				storage_num--;
			}
		}
	}
	//将高级英雄拆分成1级英雄返回至总卡牌库中
	for (int i = 1; i <= hero->level * 3; i++) {
		Hero* Newhero = new Hero(hero->No, hero->level,the);
		bank.push_back(Newhero);
	}
	money += hero->price;
	cal_kind();
}

void Player::refreshshop() {
	//先将玩家商店里面的卡牌返回总卡池
	bank.insert(bank.end(), shop_for_player.begin(), shop_for_player.end());
	shop_for_player.clear();

	//商店一次刷新只有4张卡牌
	random_shuffle(bank.begin(), bank.end());
	for (int i = 0; i < 4 && !bank.empty(); ++i) {
		shop_for_player.push_back(bank.back());
		bank.pop_back();
	}
}

void Player::on_board(Hero* hero) {
	storage[hero->seat] = NULL;
	storage_num--;
	hero_on_board.push_back(hero);
	hero->is_on_board = true;
	hero_num++;
	cal_kind();
}

void Player::off_board(Hero* hero) {
	for (int i = 0; i < hero_on_board.size(); i++) {
		if (hero_on_board[i]->click) {
			hero_on_board.erase(hero_on_board.begin() + i);
			break;
		}
	}
	hero_num--;
	hero->is_on_board = false;
	for (int i = 1; i <= MAX_STORAGE_NUM; i++)
		if (storage[i] == NULL)
			storage[i] = hero;
	storage_num++;
	cal_kind();
}

//由于可能会合成三级英雄，故每次调用该函数时都需要调用两次（第二次无参数）
void Player::syn_hero() {
	bool is_on_board = false;//用于判断合成的英雄在场上还是在备战席，规则是：三个进行合成的英雄中任意一个在场上，则合成的英雄在场上
	int arr[HERO_TYPES + 1] = { 0 };
	for (int i = 0; i < hero_on_board.size(); i++)
		arr[hero_on_board[i]->No]++;
	for (int i = 1; i <= MAX_STORAGE_NUM; i++)
		arr[storage[i]->No]++;
	for (int i = 0; i <= HERO_TYPES; i++) {
		if (arr[i] >= 3) {
			for (int j = 0; j < hero_on_board.size(); j++) {
				if (hero_on_board[j]->No == i) {
					is_on_board = true;
					weapon_off(hero_on_board[j]);
					hero_on_board.erase(hero_on_board.begin() + j);
					hero_num--;
				}
			}
			for (int j = 1; j <= MAX_STORAGE_NUM; j++) {
				if (storage[j]->No == i) {
					weapon_off(storage[j]);
					storage[j] = NULL;
					storage_num--;
				}
			}
			Hero* Newhero = new Hero(i, hero_on_board[i]->level,the);
			if (is_on_board)
				hero_on_board.push_back(Newhero);
			else {
				for (int k = 1; k <= MAX_STORAGE_NUM; k++) {
					if (storage[k] == NULL)
						storage[k] = Newhero;
				}
			}
		}
	}
}

//由于可能会合成三级英雄，故每次调用该函数时都需要调用两次（第二次无参数）
void Player::syn_hero(Hero* hero) {
	//优先将购买的英雄放在备战席
	if (storage_num < MAX_STORAGE_NUM) {
		for (int i = 1; i <= MAX_STORAGE_NUM; i++) {
			if (storage[i] == NULL)
				storage[i] = hero;
		}
		hero->is_on_board = false;
		storage_num++;
	}
	else {
		hero_on_board.push_back(hero);
		hero->is_on_board = true;
		hero_num++;
	}
}

void Player::syn_weapon(Weapon* fir, Weapon* sec) {
	int num1 = min(fir->No, sec->No), num2 = max(fir->No, sec->No);
	pair<int, int>key = { num1,num2 };
	if (WeaponCombination.find(key) != WeaponCombination.end()) {
		for (int i = 0; i < weapon_for_player.size(); i++) {
			if (weapon_for_player[i]->click)
				weapon_for_player.erase(weapon_for_player.begin() + i);
		}
		int newkey = WeaponCombination[key];
		if (newkey == NATUREFORCE) {
			HasNatureForce = true;//标志拥有装备“自然之力”
			cal_max_hero_num();
		}
		Weapon* syn = new Weapon(newkey);
		weapon_for_player.push_back(syn);
	}
}

int Player::damage(Player winner, bool iswin) {
	if (iswin)
		return 0;
	return winner.hero_alive * 4 + winner.stage * 2; //输掉每局游戏的伤害由敌方存活英雄数量和当前阶段决定
}