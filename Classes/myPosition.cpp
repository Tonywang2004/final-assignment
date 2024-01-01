#include "myPosition.h"

myPosition::myPosition() {
	x = -1;
	y = -1;
	state = 0;
}

myPosition::myPosition(int tx, int ty) :x(tx),y(ty){
	state = 0;
}

void myPosition::Setsprite() {
	state = 1;
}

void myPosition::Removesprite() {
	state = 0;
}

bool myPosition::IsEmpty() {
	if (state == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void myPosition::operator=(myPosition p) {
	x = p.x;
	y = p.y;
	this->state = p.state;
}

