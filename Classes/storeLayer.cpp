#include <random>
#include "cocos2d.h"
#include <string>
#include "playerScene.h"

extern chessboardSeat seat1;
extern preparationSeat seat2;
extern Vector<Hero *> allMyHeroes;    // 我方所有英雄
extern Vector<Hero *> allEnemyHeroes; // 敌方所有英雄

// 等级经验表
const int exp_level_up[6] = {0, 0, 4, 8, 16, 36};
// exp_level_up[i]表示从i-1级升至i级需要的经验
const int MAX_LEVEL = 5; // 最高等级

storeLayer *storeLayer::createLayer()
{
    return storeLayer::create();
}

bool storeLayer::init()
{
    // 若父类未初始化
    if (!Layer::init())
    {
        return false;
    }

    gold = 50; // 初始金币数量
    exp = 0;   // 初始经验值
    level = 1; // 初始等级

    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建商店
    auto store = Sprite::create("store.jpg");
    if (store != NULL)
    {
        // 设置背景精灵的位置
        store->setPosition(Vec2(visibleSize.width * 0.5 + origin.x, visibleSize.height * 0.05 + origin.y));
        store->setScale(0.4);

        // 将背景精灵添加到场景中
        this->addChild(store, 0);
        /*以上场景仅为示例，需更改*/
    }

    // 商店锁定按钮
    auto lockStore = ui::CheckBox::create("lockStore.jpg", "lockStore_click.jpg");
    lockStore->setPosition(Vec2(origin.x + visibleSize.width * 0.715, origin.y + visibleSize.height * 0.09));
    lockStore->setScale(0.6f);

    // 设置复选框状态改变
    lockStore->addEventListener([=](Ref *sender, ui::CheckBox::EventType type)
                                {
        if (type == ui::CheckBox::EventType::SELECTED) {

        }
        else if (type == ui::CheckBox::EventType::UNSELECTED) {

        } });
    this->addChild(lockStore);

    // 创建金币、等级标签
    goldLabel = Label::createWithTTF("Gold: " + std::to_string(gold), "fonts/arial.ttf", 30);
    levelLabel = Label::createWithTTF("Degree: " + std::to_string(level), "fonts/arial.ttf", 30);
    goldLabel->setPosition(origin.x + visibleSize.width * 0.25, origin.y + visibleSize.height * 0.03);
    levelLabel->setPosition(origin.x + visibleSize.width * 0.25, origin.y + visibleSize.height * 0.09);
    this->addChild(goldLabel, 3);
    this->addChild(levelLabel, 3);

    // 创建经验条
    expBar = ui::LoadingBar::create("LoadingBarFile.png");
    expBar->setDirection(ui::LoadingBar::Direction::LEFT);
    expBar->setPosition(Point(0, 0));
    this->addChild(expBar);

    // 创建升级按钮
    upgradeButton = MenuItemImage::create("refreshExperience.jpg", "refreshExperience_click.jpg",
                                          CC_CALLBACK_1(storeLayer::onUpgradeButtonClicked, this));

    // 最高5级
    this->schedule([this](float dt)
                   {
        if (level == 5) {
            upgradeButton->setEnabled(false);  //禁用升级按键
            this->unschedule("cutupgrade");
        } },
                   "cutupgrade");

    // 创建刷新按钮
    auto refreshButton = MenuItemImage::create("buyGold.jpg", "buyGold_click.jpg",
                                               CC_CALLBACK_1(storeLayer::onRefreshButtonClicked, this));
    auto storeMenu = Menu::create(upgradeButton, refreshButton, nullptr);
    storeMenu->setPosition(origin.x + visibleSize.width * 0.09, origin.y - visibleSize.height * 0.188); // 在场景中的布局
    storeMenu->alignItemsVerticallyWithPadding(0);                                                      // 设置垂直布局
    storeMenu->setScale(0.53);
    this->addChild(storeMenu);

    createHeroButtons();

    updateUI(); // 初始化UI显示

    return true;
}

void storeLayer::updateUI()
{
    // 更新金币、等级标签和经验条显示
    goldLabel->setString("Gold: " + std::to_string(gold));
    levelLabel->setString("Level: " + std::to_string(level));
    if (level < MAX_LEVEL)
        expBar->setPercent(100 * (double(exp) / exp_level_up[level + 1]));
    else
        expBar->setPercent(100);
}

void storeLayer::upgrade()
{
    // 购买经验和升级
    if (gold >= 4)
    {
        gold -= 4;
        exp += 4;
        if (level < MAX_LEVEL && exp >= exp_level_up[level + 1])
        {
            exp -= exp_level_up[level + 1];
            level++;
        }
        updateUI(); // 更新UI显示
    }
}

void storeLayer::refresh()
{
    // 刷新操作
    if (gold >= 2)
    {
        gold -= 2;
        // 实现刷新逻辑，这里简化为将经验条清零
        createHeroButtons();
        updateUI(); // 更新UI显示
    }
}

void storeLayer::onUpgradeButtonClicked(Ref *sender)
{
    // 升级按钮点击事件
    upgrade();
}

void storeLayer::onRefreshButtonClicked(Ref *sender)
{
    // 刷新按钮点击事件
    refresh();
}

// 五个英雄按键
void storeLayer::createHeroButtons()
{

    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    srand(std::time(0));

    // 第一个按钮
    if (heroButton1 != nullptr)
        heroButton1->removeFromParent();
    int randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton1->setPosition(Point(origin.x + visibleSize.width * 0.39, origin.y + visibleSize.height * 0.05));
    // 设置标准尺寸
    auto originalSize = heroButton1->getContentSize();

    // 计算缩放因子以使精灵大小变为20x20像素
    float scaleX = 150.0f / originalSize.width;
    float scaleY = 150.0f / originalSize.height;

    // 设置精灵的缩放
    heroButton1->setScale(scaleX, scaleY);
    heroButton1->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 0));
    this->addChild(heroButton1);
    herotype[0] = randnum;

    // 第二个按钮
    if (heroButton2 != nullptr)
        heroButton2->removeFromParent();
    randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton2->setPosition(Point(origin.x + visibleSize.width * 0.39 + 1 * visibleSize.width * 0.07, origin.y + visibleSize.height * 0.05));
    // 设置标准尺寸
    originalSize = heroButton2->getContentSize();

    // 计算缩放因子以使精灵大小变为20x20像素
    scaleX = 150.0f / originalSize.width;
    scaleY = 150.0f / originalSize.height;

    // 设置精灵的缩放
    heroButton2->setScale(scaleX, scaleY);
    heroButton2->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 1));
    this->addChild(heroButton2);
    herotype[1] = randnum;

    // 第三个按钮
    if (heroButton3 != nullptr)
        heroButton3->removeFromParent();
    randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton3->setPosition(Point(origin.x + visibleSize.width * 0.39 + 2 * visibleSize.width * 0.07, origin.y + visibleSize.height * 0.05));
    // 设置标准尺寸
    originalSize = heroButton3->getContentSize();

    // 计算缩放因子以使精灵大小变为20x20像素
    scaleX = 150.0f / originalSize.width;
    scaleY = 150.0f / originalSize.height;

    // 设置精灵的缩放
    heroButton3->setScale(scaleX, scaleY);
    heroButton3->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 2));
    this->addChild(heroButton3);
    herotype[2] = randnum;

    // 第四个按钮
    if (heroButton4 != nullptr)
        heroButton4->removeFromParent();
    randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton4->setPosition(Point(origin.x + visibleSize.width * 0.39 + 3 * visibleSize.width * 0.07, origin.y + visibleSize.height * 0.05));
    // 设置标准尺寸
    originalSize = heroButton4->getContentSize();

    // 计算缩放因子以使精灵大小变为20x20像素
    scaleX = 150.0f / originalSize.width;
    scaleY = 150.0f / originalSize.height;

    // 设置精灵的缩放
    heroButton4->setScale(scaleX, scaleY);
    heroButton4->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 3));
    this->addChild(heroButton4);
    herotype[3] = randnum;

    // 第五个按钮
    if (heroButton5 != nullptr)
        heroButton5->removeFromParent();
    randnum = rand() % 6 + 1;
    if (randnum == 1)
        heroButton1 = ui::Button::create("soldier.png");
    else if (randnum == 2)
        heroButton1 = ui::Button::create("supersoldier.png");
    else if (randnum == 3)
        heroButton1 = ui::Button::create("Demonsoldier.png");
    else if (randnum == 4)
        heroButton1 = ui::Button::create("shooter.png");
    else if (randnum == 5)
        heroButton1 = ui::Button::create("supershooter.png");
    else if (randnum == 6)
        heroButton1 = ui::Button::create("demonshooter.png");
    heroButton5->setPosition(Point(origin.x + visibleSize.width * 0.39 + 4 * visibleSize.width * 0.07, origin.y + visibleSize.height * 0.05));
    // 设置标准尺寸
    originalSize = heroButton5->getContentSize();

    // 计算缩放因子以使精灵大小变为20x20像素
    scaleX = 150.0f / originalSize.width;
    scaleY = 150.0f / originalSize.height;

    // 设置精灵的缩放
    heroButton5->setScale(scaleX, scaleY);
    heroButton5->addClickEventListener(CC_CALLBACK_1(storeLayer::onHeroButtonClicked, this, 4));
    this->addChild(heroButton5);
    herotype[4] = randnum;
}

// 点击购买函数
void storeLayer::onHeroButtonClicked(Ref *sender, int buttonIndex)
{

    // 获取当前屏幕的尺寸和原点位置
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (int i = 0; i < 9; i++)
    {
        if (seat2.seats[i].IsEmpty())
        {
            if (gold >= herocost[herotype[buttonIndex]])
            {

                // 金币减少
                gold -= herocost[herotype[buttonIndex]];
                updateUI(); // 刷新

                // 备战席显示
                // auto hero = Hero::creatHero(herotype[buttonIndex], Vec2(origin.x + visibleSize.width * 0.34 + (i - 1) * visibleSize.width * 0.08, origin.y + visibleSize.height * 0.17), 1);
                auto hero = Hero::creatHero(herotype[buttonIndex], Vec2(seat2.seats[i].x + 70, seat2.seats[i].y + 50), 1);
                this->getParent()->addChild(hero, 2);
                seat2.seats[i].Setsprite();
                hero->setIndex(i);

                // 按键消失
                if (buttonIndex == 0)
                {
                    heroButton1->removeFromParent();
                    delete heroButton1;
                    heroButton1 = nullptr;
                }
                else if (buttonIndex == 1)
                {
                    heroButton2->removeFromParent();
                    delete heroButton2;
                    heroButton2 = nullptr;
                }
                else if (buttonIndex == 2)
                {
                    heroButton3->removeFromParent();
                    delete heroButton3;
                    heroButton3 = nullptr;
                }
                else if (buttonIndex == 3)
                {
                    heroButton4->removeFromParent();
                    delete heroButton4;
                    heroButton4 = nullptr;
                }
                else if (buttonIndex == 4)
                {
                    heroButton5->removeFromParent();
                    delete heroButton5;
                    heroButton5 = nullptr;
                }

                Hero::mergeHeroes();

                break;
            }
        }
    }
}
// 创建按钮
ui::Button *storeLayer::createButton(const std::string &normalImage, const std::string &selectedImage, const Vec2 &position,
                                     const float &scale, const std::function<void(Ref *, ui::Widget::TouchEventType)> &callback)
{
    auto button = ui::Button::create(normalImage, selectedImage);
    button->setPosition(position);
    button->setScale(scale);
    button->addTouchEventListener(callback);
    this->addChild(button, 2);
    return button;
}
