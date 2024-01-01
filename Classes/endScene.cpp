#include "endScene.h"
endScene* endScene::createScene(int c) {
	endScene* scene = new endScene;
	if (scene) {  //如果创建成功
		scene->autorelease();
		Sprite* background;
		// 根据c来为场景换不同的场景图
		if (c == 0) { 
			//失败
			background = Sprite::create("endbackground0.png");
			scene->addChild(background, 0);
			background->setPosition(955, 540);
		}
		else if (c == 1) {  
			//胜利
			background = Sprite::create("endbackground1.png");
			scene->addChild(background, 0);
			background->setPosition(955, 540);
		}
		else if (c == 2) { 
			//平局
			background = Sprite::create("endbackground2.png");
			scene->addChild(background, 0);
			background->setPosition(955, 540);
		}

		// 设置一个menu  用于点击退出程序（游戏）
		auto button1 = Sprite::create("exitmenu1.png");
		auto button2 = Sprite::create("exitmenu2.png");
		auto button = MenuItemSprite::create(button1, button2,
			CC_CALLBACK_1(endScene::exitCallBack, scene));
		auto menu = Menu::create(button, NULL);
		menu->setPosition(960, 400);  //在场景中的布局
		scene->addChild(menu, 1);   //添加到挂件
		return scene;
	}

	CC_SAFE_DELETE(scene);
	return nullptr;
}

void endScene::exitCallBack(Ref* pSender) {
	Director::getInstance()->end();   //退出
}