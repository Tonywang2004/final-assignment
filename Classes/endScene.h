#pragma once
#include "cocos2d.h"
USING_NS_CC;
class endScene :public Scene
{
public:
	static endScene* createScene(int c);  //0——失败  1——胜利  2——平局
	void exitCallBack(Ref* pSender);   //退出游戏
};

