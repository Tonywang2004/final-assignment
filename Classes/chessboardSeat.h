#pragma once
#include"myPosition.h"

class chessboardSeat
{
public:
	myPosition* seats;
	int Size;
	int mine;
	int getmine()const{ return mine; }
	chessboardSeat(int IsMine);
	~chessboardSeat();
};
