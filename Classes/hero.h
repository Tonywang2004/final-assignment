#ifndef HERO_H
#define HERO_H
#include "cocos2d.h"
#include"player.h"
#include"heroAction.h"
#include"HelloWorldScene.h"
using namespace std;
using namespace cocos2d;
class Hero :public cocos2d::Node{
	friend class player;
	friend class ImageSwitcher;
protected:

public:
	float atn;//物理攻击力
	float matk;//magic attack 魔法攻击力
	float def;//物理防御力
	float mr;//magic resistance 魔抗
	float hp_max=100;//生命值
	float hp_now=hp_max;
	float mp_max;//蓝条
	float mp_now;
	float as=1;//attack speed 攻速
	float ch;//critical hit 暴击
	float ch_ma;//magnification 倍率
	float ran;//range 射程
	int kind1;//基础分类 射手、法师、战士、刺客
	int kind2 = 0;//额外分类  恶魔、天使、龙、亡灵
	int prize;
	float mp_increment=10;
	bool is_ontheboard;//是否上场	
	double target_distance;
	Hero* target = nullptr;//目标
	Sprite* mine = nullptr;//自己
	Vec2 hero_position;
	Vec2 target_position;
	void updateposition();
	void take_danmage(Hero* enemy,HelloWorld* the,int danmage=0);
	void get_target(Hero* hero, Player enermy);
	Sprite* getmine() { return mine; }
	Hero* gettarget() { return target; }
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
class Ghostride :public Hero {
public:
	Ghostride(HelloWorld* helloworld){
		the = helloworld;
		atn = 20;
		matk = 0;
		def = 10;
		as = 1;
		hp_max = 100;
		hp_now = 100;
		mp_max = 10;
		mp_now = 4;
		mine = gr;
		gr->setContentSize(Size(100, 100));
		updateposition();
	}
	HelloWorld* the;
	Sprite* gr = Sprite::create("player.png");
	void attack(Hero* enemy, HelloWorld* the, Player enemy_hero);
	void skill_add(HelloWorld* the,Player enemy_hero,ProgressTimer* hp);//根据时间增加蓝条
	void skill(Hero* target,HelloWorld* the,Vec2 fromposition,Vec2 toposition) ;//蓝条封顶放技能:额外造成敌方最大生命值百分之十的血量
};
#endif