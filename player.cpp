#include "cocos2d.h"
#include "hero.h"
#include "bank.h"
#include "weapon.h"
#include "player.h"
#include <vector>
#include <set>
USING_NS_CC;
using namespace std;

void Player::switch_lock() {
	lock = 1 - lock;
}

void Player::level_up() {
	exp -= exp_level_up[level];
	if (level < MAX_LEVEL)
		level++;
}

void Player::buy_exp() {
	if (money >= 4) {
		money -= 4;
		exp += 4;
		if (exp >= exp_level_up[level] && level < MAX_LEVEL)
			level_up();
	}
}

void Player::buy_card(int index) {
	if (index >= 0 && index < shop_for_player.size()) {
		// 将已购买的卡牌从在售列表中移除
		shop_for_player.erase(shop_for_player.begin() + index);
		money -= shop_for_player[index].price;
	}
}

void Player::sell_card(Card card) {
	
}

void Player::refreshshop() {
	//先将玩家商店里面的卡牌返回总卡池
	bank.insert(bank.end(), shop_for_player.begin(), shop_for_player.end());
	shop_for_player.clear();

	//商店一次刷新只有5张卡牌
	random_shuffle(bank.begin(), bank.end());
	for (int i = 0; i < 5 && !bank.empty(); ++i) {
		shop_for_player.push_back(bank.back());
		bank.pop_back();
	}
}

void Player::syn_hero() {
	multiset<int>myset;
	for (int i = 0; i < hero_on_board.size(); ++i)
		myset.insert(hero_on_board[i].No);
	for (int i = 0; i < storage.size(); ++i)
		myset.insert(storage[i].No);
	for (const auto& num : myset) {
		if (myset.count(num) >= 3) {

		}
	}
}

int Player::damage(Player winner, bool iswin) {
	if (iswin)
		return 0;
	return winner.hero_num * 2 + winner.stage;//输掉每局游戏的伤害由敌方存活英雄数量和当前阶段决定
}

void Role::move() {
	auto listener = EventListenerMouse::create();

}