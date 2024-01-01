#pragma once
#include"cocos2d.h"
USING_NS_CC;

#define ROLETAG 111

class playerroleLayer : public Layer
{
public:
	int camp = 1;  // 1代表我方  0代表敌方
	float max_blood = 10;
	float cur_blood = 10;
	Vec2 cur_position;

	ProgressTimer* healthBar;//血条类
	static playerroleLayer* createLayer(int tag);
	void attack(playerroleLayer* target);   //小小英雄发起进攻

	int getCamp() {
		return camp;
	}

	float getMaxBlood() {
		return max_blood;
	}

	float getCurBlood() {
		return cur_blood;
	}

	Vec2 getCurPos() {
		return cur_position;
	}
	
};

