#include "preparationSeat.h"
#include"myPosition.h"
preparationSeat::preparationSeat(int me) {
	Size = 9;
	seats = new myPosition[9];

	//备战席位置
	if (me)
	{
		seats[0] = myPosition(380, 241);
		seats[1] = myPosition(493, 241);
		seats[2] = myPosition(608, 241);
		seats[3] = myPosition(721, 241);
		seats[4] = myPosition(831, 241);
		seats[5] = myPosition(952, 241);
		seats[6] = myPosition(1069, 241);
		seats[7] = myPosition(1170, 241);
		seats[8] = myPosition(1275, 241);
	}
	else {
		seats[0] = myPosition(558, 872);
		seats[1] = myPosition(635, 872);
		seats[2] = myPosition(718, 872);
		seats[3] = myPosition(807, 872);
		seats[4] = myPosition(887, 872);
		seats[5] = myPosition(961, 872);
		seats[6] = myPosition(1043, 872);
		seats[7] = myPosition(1133, 872);
		seats[8] = myPosition(1219, 872);
	}
}
//释放内存
preparationSeat::~preparationSeat() {
	delete[]seats;
}