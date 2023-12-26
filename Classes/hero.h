#ifndef HERO_H
#define HERO_H
#include "cocos2d.h"
#include"player.h"
#include"heroAction.h"
#include"const.h"
#include"HelloWorldScene.h"
#include"weapon.h";
using namespace std;
using namespace cocos2d;
class Hero;
class Hero :public cocos2d::Node{
	friend class player;
	friend class ImageSwitcher;

protected:
public:
	float atn;//物理攻击力
	float def;//物理防御力
	float hp_max=100;//生命值
	float hp_now=hp_max;
	float mp_max;//蓝条
	float mp_now;
	float as=1;//attack speed 攻速
	float ch=0.1;//critical hit 暴击
	float ch_ma=1.5;//magnification 倍率
	float ran;//range 射程
	int kind1;//基础分类 射手、法师、战士、刺客
	int kind2 = 0;//额外分类  恶魔、天使、龙、亡灵
	int price;
	int seat;
	float mp_increment=10;
	bool is_onboard;//是否上场	
	double target_distance;
	bool islive=1;
	Hero* target=nullptr;//目标
	Sprite* mine = nullptr;//自己
	Vec2 hero_position;
	vector<int> kind;
	int level = 1;
	Weapon* wea[3];
	Vec2 target_position;
	void updateposition();
	void get_target(Hero* hero, Player enemy);
	ProgressTimer* hp = ProgressTimer::create(Sprite::create("hp_progress_bar.png"));
	ProgressTimer* mp = ProgressTimer::create(Sprite::create("mp_progress_bar.png"));
	Sprite* isdie= Sprite::create("die.png");
	Sprite* getmine() 
	{ 
		return mine;
	}
	Hero* gettarget(Player enemy) {
		get_target(this,enemy);
		return target;
	}
	Vec2 getposition() {
		return mine->getPosition();
	}
	bool getclink() {
		return clink;
	}
	void move_to_target(HelloWorld*the,Hero* enemy);
	bool isTouch(Touch* touch, Event* event);
	bool clink=0;
	int No;
};
//class Hero {
//public:
//	cocos2d::ProgressTimer* mp; // MP进度条
//	cocos2d::ProgressTimer* hp; // HP进度条
//	float mp_increment;         // MP增长速率
//	int hp_max;                 // 最大HP
//	int hp_current;             // 当前HP
//
//	Hero() {
//		// 初始化MP和HP进度条
//		mp = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("mp_bar.png"));
//		mp->setType(cocos2d::ProgressTimer::Type::BAR);
//		mp->setPercentage(0); // 初始MP为0
//
//		hp = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("hp_bar.png"));
//		hp->setType(cocos2d::ProgressTimer::Type::BAR);
//		hp->setPercentage(100); // 假设初始HP为100%
//
//		mp_increment = 0.5f; // 每秒增长0.5%
//		hp_max = 100;        // 假设最大HP为100
//		hp_current = 100;    // 初始HP为100
//	}
//
//	void update(float dt) {
//		// 增加MP
//		float newMpPercentage = mp->getPercentage() + mp_increment;
//		if (newMpPercentage >= 100.0f) {
//			// MP达到100%，重置MP并减少HP
//			newMpPercentage = 0.0f;
//
//			// 减少HP的当前值的20%
//			hp_current -= hp_max * 0.2;
//			if (hp_current < 0) hp_current = 0;
//
//			// 更新HP进度条
//			float newHpPercentage = static_cast<float>(hp_current) / hp_max * 100.0f;
//			hp->setPercentage(newHpPercentage);
//		}
//		mp->setPercentage(newMpPercentage);
//	}
//
//	void startMpRegeneration() {
//		// 每帧调用update函数更新MP和HP
//		cocos2d::Director::getInstance()->getScheduler()->schedule(
//			CC_SCHEDULE_SELECTOR(Hero::update), this, 0, false);
//	}
//};
class Soldier :public Hero {
public:
	Soldier(HelloWorld* helloworld) {
		No = pow(100, level) * Demonsoldier;
		the = helloworld;
		atn = 20;
		def = 10;
		as = 1;
		ran = 10;
		hp_max = 150;
		hp_now = 150;
		mp_max = 10;
		mp_increment = 10;
		mp_now = 4;
		mine = so;
		so->setContentSize(Size(100, 100));
		updateposition();
		hp->setType(ProgressTimer::Type::BAR);
		hp->setScaleX(0.25); // 宽度缩小为原来的一半
		hp->setScaleY(0.5); // 高度放大为原来的两倍
		hp->setPercentage(100);
		hp->setMidpoint(Vec2(50, 30)); // 进度条起点位置
		hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		hp->setPosition(Vec2(50, 30)); // 进度条位置
		if (hp->getParent() == nullptr)
			mine->addChild(hp);
		mp->setType(ProgressTimer::Type::BAR);
		mp->setScaleX(0.25); // 宽度缩小为原来的一半
		mp->setScaleY(0.5); // 高度放大为原来的两倍
		mp->setPercentage(40);
		mp->setMidpoint(Vec2(50, 40)); // 进度条起点位置
		mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		mp->setPosition(Vec2(50, 40)); // 进度条位置
		if (mp->getParent() == nullptr)
			mine->addChild(mp);
		isdie->setContentSize(Size(100, 50));
		isdie->setPosition(Vec2(50, 50));
		isdie->setVisible(false);
		mine->addChild(isdie);
	}
	HelloWorld* the;
	Sprite* so = Sprite::create("soldier.png");
	void attack(Hero* enemy, HelloWorld* the, Player enemy_hero);
	void skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp);//根据时间增加蓝条
	void skill(ProgressTimer* myhp);//蓝条封顶放技能:额外造成敌方最大生命值百分之十的血量
};
class SuperSoldier :public Hero {
public:
	SuperSoldier(HelloWorld* helloworld) {
		No = pow(100, level) * Demonsoldier;
		the = helloworld;
		atn = 20;
		def = 10;
		as = 1;
		ran = 10;
		hp_max = 150;
		hp_now = 150;
		mp_max = 10;
		mp_increment = 10;
		mp_now = 4;
		mine = ss;
		ss->setContentSize(Size(100, 100));
		updateposition();
		hp->setType(ProgressTimer::Type::BAR);
		hp->setScaleX(0.25); // 宽度缩小为原来的一半
		hp->setScaleY(0.5); // 高度放大为原来的两倍
		hp->setPercentage(100);
		hp->setMidpoint(Vec2(50, 30)); // 进度条起点位置
		hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		hp->setPosition(Vec2(50, 30)); // 进度条位置
		if (hp->getParent() == nullptr)
			mine->addChild(hp);
		mp->setType(ProgressTimer::Type::BAR);
		mp->setScaleX(0.25); // 宽度缩小为原来的一半
		mp->setScaleY(0.5); // 高度放大为原来的两倍
		mp->setPercentage(40);
		mp->setMidpoint(Vec2(50, 40)); // 进度条起点位置
		mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		mp->setPosition(Vec2(50, 40)); // 进度条位置
		if (mp->getParent() == nullptr)
			mine->addChild(mp);
		isdie->setContentSize(Size(100, 50));
		isdie->setPosition(Vec2(50, 50));
		isdie->setVisible(false);
		mine->addChild(isdie);
	}
	HelloWorld* the;
	Sprite* ss = Sprite::create("supersoldier.png");
	void attack(Hero* enemy, HelloWorld* the, Player enemy_hero);
	void skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp);//根据时间增加蓝条
	void skill(ProgressTimer* myhp);//蓝条封顶放技能:额外造成敌方最大生命值百分之十的血量
};
class DemonSoldier :public Hero {
public:
	DemonSoldier(HelloWorld* helloworld){
		No = pow(100,level)* Demonsoldier;
		the = helloworld;
		atn = 30;
		def = 10;
		as = 1;
		ran = 10;
		hp_max = 150;
		hp_now = 150;
		mp_max = 10;
		mp_increment = 10;
		mp_now = 4;
		mine = ds;
		ds->setContentSize(Size(100, 100));
		updateposition();
		hp->setType(ProgressTimer::Type::BAR);
		hp->setScaleX(0.25); // 宽度缩小为原来的一半
		hp->setScaleY(0.5); // 高度放大为原来的两倍
		hp->setPercentage(100);
		hp->setMidpoint(Vec2(50, 30)); // 进度条起点位置
		hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		hp->setPosition(Vec2(50, 30)); // 进度条位置
		if (hp->getParent() == nullptr)
			mine->addChild(hp);
		mp->setType(ProgressTimer::Type::BAR);
		mp->setScaleX(0.25); // 宽度缩小为原来的一半
		mp->setScaleY(0.5); // 高度放大为原来的两倍
		mp->setPercentage(40);
		mp->setMidpoint(Vec2(50, 40)); // 进度条起点位置
		mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		mp->setPosition(Vec2(50, 40)); // 进度条位置
		if (mp->getParent() == nullptr)
			mine->addChild(mp);
		isdie->setContentSize(Size(100, 50));
		isdie->setPosition(Vec2(50, 50));
		isdie->setVisible(false);
		mine->addChild(isdie);
	}
	HelloWorld* the;
	Sprite* ds = Sprite::create("Demonsoldier.png");
	void attack(Hero* enemy, HelloWorld* the, Player enemy_hero);
	void skill_add(HelloWorld* the,Player enemy_hero,ProgressTimer* hp);//根据时间增加蓝条
	void skill(ProgressTimer *myhp) ;//蓝条封顶放技能:额外造成敌方最大生命值百分之十的血量
};
class Shooter :public Hero {
public:
	Shooter(HelloWorld* helloworld) {
		the = helloworld;
		atn = 20;
		def = 5;
		as = 0.5;
		hp_max = 100;
		hp_now = 100;
		mp_max = 10;
		mp_now = 4;
		mine = st;
		mp_increment = 20;
		st->setContentSize(Size(100, 100));
		updateposition();
		hp->setType(ProgressTimer::Type::BAR);
		hp->setScaleX(0.25); // 宽度缩小为原来的一半
		hp->setScaleY(0.5); // 高度放大为原来的两倍
		hp->setPercentage(100);
		hp->setMidpoint(Vec2(50, 30)); // 进度条起点位置
		hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		hp->setPosition(Vec2(50, 30)); // 进度条位置
		if (hp->getParent() == nullptr)
			mine->addChild(hp);
		mp->setType(ProgressTimer::Type::BAR);
		mp->setScaleX(0.25); // 宽度缩小为原来的一半
		mp->setScaleY(0.5); // 高度放大为原来的两倍
		mp->setPercentage(40);
		mp->setMidpoint(Vec2(50, 40)); // 进度条起点位置
		mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		mp->setPosition(Vec2(50, 40)); // 进度条位置
		if (mp->getParent() == nullptr)
			mine->addChild(mp);
		isdie->setContentSize(Size(100, 50));
		isdie->setPosition(Vec2(50, 50));
		isdie->setVisible(false);
		mine->addChild(isdie);
	}
	HelloWorld* the;
	Sprite* st = Sprite::create("shooter.png");
	void attack(Hero* enemy, HelloWorld* the, Player enemy_hero);
	void skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp);//根据时间增加蓝条
	void skill(Hero* target, HelloWorld* the, Vec2 fromposition, Vec2 toposition);//蓝条封顶放技能:额外造成敌方最大生命值百分之十的血量
};
class SuperShooter :public Hero {
public:
	SuperShooter(HelloWorld* helloworld) {
		the = helloworld;
		atn = 30;
		def = 5;
		as = 0.5;
		hp_max = 100;
		hp_now = 100;
		mp_max = 10;
		mp_now = 4;
		mine = sst;
		mp_increment = 20;
		sst->setContentSize(Size(100, 100));
		updateposition();
		hp->setType(ProgressTimer::Type::BAR);
		hp->setScaleX(0.25); // 宽度缩小为原来的一半
		hp->setScaleY(0.5); // 高度放大为原来的两倍
		hp->setPercentage(100);
		hp->setMidpoint(Vec2(50, 30)); // 进度条起点位置
		hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		hp->setPosition(Vec2(50, 30)); // 进度条位置
		if (hp->getParent() == nullptr)
			mine->addChild(hp);
		mp->setType(ProgressTimer::Type::BAR);
		mp->setScaleX(0.25); // 宽度缩小为原来的一半
		mp->setScaleY(0.5); // 高度放大为原来的两倍
		mp->setPercentage(40);
		mp->setMidpoint(Vec2(50, 40)); // 进度条起点位置
		mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		mp->setPosition(Vec2(50, 40)); // 进度条位置
		if (mp->getParent() == nullptr)
			mine->addChild(mp);
		isdie->setContentSize(Size(100, 50));
		isdie->setPosition(Vec2(50, 50));
		isdie->setVisible(false);
		mine->addChild(isdie);
	}
	HelloWorld* the;
	Sprite* sst = Sprite::create("supershooter.png");
	void attack(Hero* enemy, HelloWorld* the, Player enemy_hero);
	void skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp);//根据时间增加蓝条
	void skill(Hero* target, HelloWorld* the, Vec2 fromposition, Vec2 toposition);//蓝条封顶放技能:额外造成敌方最大生命值百分之十的血量
};
class DemonShooter :public Hero {
public:
	DemonShooter(HelloWorld* helloworld) {
		the = helloworld;
		atn = 30;
		def = 5;
		as = 0.5;
		hp_max = 100;
		hp_now = 100;
		mp_max = 10;
		mp_now = 4;
		mine = dst;
		mp_increment = 20;
		dst->setContentSize(Size(100, 100));
		updateposition();
		hp->setType(ProgressTimer::Type::BAR);
		hp->setScaleX(0.25); // 宽度缩小为原来的一半
		hp->setScaleY(0.5); // 高度放大为原来的两倍
		hp->setPercentage(100);
		hp->setMidpoint(Vec2(50, 30)); // 进度条起点位置
		hp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		hp->setPosition(Vec2(50, 30)); // 进度条位置
		if (hp->getParent() == nullptr)
			mine->addChild(hp);
		mp->setType(ProgressTimer::Type::BAR);
		mp->setScaleX(0.25); // 宽度缩小为原来的一半
		mp->setScaleY(0.5); // 高度放大为原来的两倍
		mp->setPercentage(40);
		mp->setMidpoint(Vec2(50, 40)); // 进度条起点位置
		mp->setBarChangeRate(cocos2d::Vec2(1, 0)); // 进度条方向
		mp->setPosition(Vec2(50, 40)); // 进度条位置
		if (mp->getParent() == nullptr)
			mine->addChild(mp);
		isdie->setContentSize(Size(100, 50));
		isdie->setPosition(Vec2(50, 50));
		isdie->setVisible(false);
		mine->addChild(isdie);
	}
	HelloWorld* the;
	Sprite* dst = Sprite::create("demonshooter.png");
	void attack(Hero* enemy, HelloWorld* the, Player enemy_hero);
	void skill_add(HelloWorld* the, Player enemy_hero, ProgressTimer* hp);//根据时间增加蓝条
	void skill(Hero* target, HelloWorld* the, Vec2 fromposition, Vec2 toposition);//蓝条封顶放技能:额外造成敌方最大生命值百分之十的血量
};
#endif