#include"weapon.h"
//第一个为小数，第二个为大数，返回为一个新的装备，否则为nullptr
Weapon* Weapon::check_combination(Weapon* fir,Weapon* sec)
{
	pair<int, int> key = { fir->No,sec->No };
	if (combination.find(key) != combination.end()) {
		int newkey = combination[key];
		Weapon* newweapon = new Weapon(newkey);
		return newweapon;
	}
	return nullptr;
}