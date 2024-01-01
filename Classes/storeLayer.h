#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "hero.h"
#define __SHOP_LAYER_H__
USING_NS_CC;

/*
这个层级中共有7个菜单项
第一个用于购买经验和升级
第二个用于刷新商店
剩下的5个是角色的图片（商店的关键项目）

我们使用一个位置数组来保存4个角色的位置
便于刷新商店和重置角色的照片
*/

class storeLayer : public Layer
{
public:
  int herotype[5]; // 五个按键代表的英雄（每次准备阶段都会自动刷新）
  int herocost[7] = {0, 1, 2, 3, 1, 2, 3};
  static storeLayer *createLayer();
  CREATE_FUNC(storeLayer);

  bool init() override;
  int gold;  // 金币数量
  int exp;   // 经验值
  int level; // 等级

  cocos2d::ui::LoadingBar *expBar; // 经验条
  cocos2d::Label *goldLabel;       // 显示金币数量的标签
  cocos2d::Label *levelLabel;      // 显示等级的标签

  cocos2d::ui::Button *heroButton1;
  cocos2d::ui::Button *heroButton2;
  cocos2d::ui::Button *heroButton3;
  cocos2d::ui::Button *heroButton4;
  cocos2d::ui::Button *heroButton5;

  MenuItemImage *upgradeButton;

  void updateUI(); // 更新UI显示
  void upgrade();  // 购买经验和升级操作
  void refresh();  // 刷新商店操作

  void onUpgradeButtonClicked(cocos2d::Ref *sender);
  void onRefreshButtonClicked(cocos2d::Ref *sender);
  void createHeroButtons();                                      // 创建英雄按钮
  void onHeroButtonClicked(cocos2d::Ref *sender, int heroIndex); // 英雄按钮点击事件

  ui::Button *createButton(const std::string &normalImage, const std::string &selectedImage, const Vec2 &position,
                           const float &scale, const std::function<void(Ref *, ui::Widget::TouchEventType)> &callback);
};
