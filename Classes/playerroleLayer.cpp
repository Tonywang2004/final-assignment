#include "playerroleLayer.h"

// 创建小小英雄
playerroleLayer* playerroleLayer::createLayer(int turn) {
	playerroleLayer* role = new playerroleLayer;
	if (role) {  
		role->autorelease();
		role->camp = turn;
		if (turn == 0) //我方小小英雄
		{
			//设置小小英雄状态
			auto sprite = Sprite::create("LittlePlayer_2_0.png");
			role->addChild(sprite, 0, ROLETAG);
			sprite->setPosition(471 + 70, 362 + 50);
			sprite->setScale(0.6);
			role->cur_position = Vec2(471 + 70, 362 + 50);
			//创建血条
			auto health_1 = Sprite::create("bloodbar1.png");
			auto health_2 = Sprite::create("bloodbar0.png");

			role->healthBar = ProgressTimer::create(health_1);
			role->healthBar->setType(ProgressTimer::Type::BAR);
			role->healthBar->setMidpoint(Vec2(0, 0.5));
			role->healthBar->setBarChangeRate(Vec2(1, 0));
			// 将 healthBar 添加到 mySprite 中
			sprite->addChild(role->healthBar, 1);
			sprite->addChild(health_2, 0);
			role->healthBar->setPosition(200, 400);
			health_2->setPosition(200, 400);
			// 初始满血
			role->healthBar->setPercentage(100);  
		}
		else if (turn == 1) {  //敌方小小英雄
			//同理
			auto sprite = Sprite::create("LittlePlayer_3_0.png");
			sprite->setColor(Color3B::BLUE);
			role->addChild(sprite, 0, ROLETAG);
			sprite->setPosition(1214 + 70, 800 + 50);
			sprite->setScale(0.6);
			role->cur_position = Vec2(1214 + 70, 800 + 50);

			auto health_1 = Sprite::create("bloodbar11.png");
			auto health_2 = Sprite::create("bloodbar0.png");
			health_1->setColor(Color3B::RED);
			role->healthBar = ProgressTimer::create(health_1);
			role->healthBar->setType(ProgressTimer::Type::BAR);
			role->healthBar->setMidpoint(Vec2(0, 0.5));
			role->healthBar->setBarChangeRate(Vec2(1, 0));
			// 将 healthBar 添加到 mySprite 中
			sprite->addChild(role->healthBar, 1);
			sprite->addChild(health_2, 0);
			role->healthBar->setPosition(200, 400);
			health_2->setPosition(200, 400);
			// 血条初始满血
			role->healthBar->setPercentage(100);  
		}
		else {
			auto sprite = Sprite::create("LittlePlayer_4_0.png");
			sprite->setColor(Color3B::GREEN);
			role->addChild(sprite, 0, ROLETAG);
			sprite->setPosition(511 + 70, 812 + 50);
			sprite->setScale(0.6);
			role->cur_position = Vec2(511 + 70, 812 + 50);

			auto health_1 = Sprite::create("bloodbar11.png");
			auto health_2 = Sprite::create("bloodbar0.png");
			health_1->setColor(Color3B::RED);
			role->healthBar = ProgressTimer::create(health_1);
			role->healthBar->setType(ProgressTimer::Type::BAR);
			role->healthBar->setMidpoint(Vec2(0, 0.5));
			role->healthBar->setBarChangeRate(Vec2(1, 0));
			// 将 healthBar 添加到 mySprite 中
			sprite->addChild(role->healthBar, 1);
			sprite->addChild(health_2, 0);
			role->healthBar->setPosition(200, 400);
			health_2->setPosition(200, 400);
			// 血条初始满血
			role->healthBar->setPercentage(100);  
		}
		return role;
	}

	CC_SAFE_DELETE(role);
	return nullptr;
}

// 进攻
void playerroleLayer::attack(playerroleLayer* target) {
	//设置攻击状态
	auto arrow = Sprite::create("role_arrow.png");
	arrow->setScale(0.15);
	this->getParent()->addChild(arrow, 4);
	arrow->setPosition(cur_position);

	//创建动作序列
	auto moveToTarget = MoveTo::create(1.0f, target->cur_position);

	auto bomb = CallFunc::create([arrow,target]() {
		arrow->setTexture("role_bomb.png");
	    arrow->setScale(0.15);
		target->cur_blood--;
	});

	auto scale = ScaleTo::create(0.5f, 0.5f);

	auto toArrow = CallFunc::create([arrow]() {
		arrow->removeFromParentAndCleanup(true);
	});

	auto sequence = Sequence::create(moveToTarget, bomb, scale, toArrow, nullptr);
	arrow->runAction(sequence);
}