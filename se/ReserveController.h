#pragma once
#include <stdio.h>
#include "datas.h"
#include "CoffeeMachineController.h"
//#include <unistd.h>

void CountDown();

void ReserveController()
{
	if (buttonData.reserveInfo[2] == 1)
	{
		reserveData.mode = buttonData.reserveInfo[0];
		reserveData.remainTime = buttonData.reserveInfo[1];
        if(reserveData.mode == 0) {
            reserveData.concentrate = buttonData.concentrate;
            reserveData.temperature = buttonData.temperature;
        }
		while (buttonDataAccess == 1)
		{
		}
        buttonDataAccess = 1;
        buttonData.reserveInfo[0] = 0;
        buttonData.reserveInfo[1] = 0;
        buttonData.reserveInfo[2] = 0;
		buttonDataAccess = 0;
    } else if(buttonData.reserveInfo[2] == -1) {
        reserveData.mode = -1;
        while(buttonDataAccess == 1) {}
        buttonDataAccess = 1;
        buttonData.reserveInfo[0] = 0;
        buttonData.reserveInfo[1] = 0;
        buttonData.reserveInfo[2] = 0;
        buttonDataAccess = 0;
    } else if (reserveData.mode != -1 && reserveData.remainTime > 0)
	{
		CountDown();
	}
}

void CountDown()
{		
	reserveData.remainTime -= 1;		
}
