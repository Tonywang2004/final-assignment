/*
Position is used to save a coordinate of the scene and the
state(whether there is a sprite or not) of the saved coordinate
*/


#pragma once
#include"cocos2d.h"
USING_NS_CC;
class myPosition
{
public:
	int x;//横坐标
	int y;//纵坐标
	int state;//表示当前位置是否为空
	myPosition();//构造函数，无参数
	myPosition(int tx, int ty);//构造函数，有tx和ty两个参数
	void Setsprite();//设置背景
	void Removesprite();//移除背景
	bool IsEmpty();//判断是否为空
	void operator=(myPosition p);//重载等于号
};

