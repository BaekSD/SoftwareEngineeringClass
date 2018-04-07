#pragma once
#include <stdio.h>
#include "datas.h"
#include "PowerInterface.h"
// #include "fileInterface.h"

void ShutdownController();
void MachineOn();
void Shutdown();

void ShutdownController()
{
	if (buttonData.powerBtn == 1) //buttonInput으로부터 buttonData가 들어오면
	{
		while(buttonDataAccess == 1)
		{}
			buttonDataAccess = 1; 
			buttonData.powerBtn = 0;
			buttonDataAccess = 0;
		
		if (statusData.status == 0 || statusData.status == 1 || statusData.status == 2) // CoffeeMachine 이 On이라면 
		{
			Shutdown();
		}
		else if (statusData.status == -1) // off상태라면 CoffeeMachine on
		{
			MachineOn();
		}
	}
}

void MachineOn()
{
	statusData.status = 100; // wait
	PowerInterface(0);							//CoffeeMachine On 출력
}

void Shutdown()
{
	statusData.status = -1; // off
	PowerInterface(1);							//CoffeeMachine Off 출력
    clicked = 0;
	// FileInterface(); 의 함수
}
