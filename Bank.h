#ifndef _BANK_H_
#define _BANK_H_

#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Hero.h"
#include <vector>
USING_NS_CC;
using namespace std;

vector<Hero> bank;//´æ´¢ËùÓÐ¿¨ÅÆµÄ¿â

//¿¨ÅÆ¿â³õÊ¼»¯
void bank_init() {
    for (int price = 1; price <= 4; ++price)
        for (int i = 1; i <= cardtypes[price - 1]; ++i)
            for (int j = 1; j <= cardnums[price - 1]; ++j)
                bank.emplace_back(price, "Price" + to_string(price) + "_" + to_string(i) + ".png");
    // Ëæ»ú´òÂÒ¿¨ÅÆË³Ðò
    random_shuffle(bank.begin(), bank.end());
}

#endif 

