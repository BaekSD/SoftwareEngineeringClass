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
	if (buttonData.powerBtn == 1) //buttonInput���κ��� buttonData�� ������
	{
		while(buttonDataAccess == 1)
		{}
			buttonDataAccess = 1; 
			buttonData.powerBtn = 0;
			buttonDataAccess = 0;
		
		if (statusData.status == 0 || statusData.status == 1 || statusData.status == 2) // CoffeeMachine �� On�̶�� 
		{
			Shutdown();
		}
		else if (statusData.status == -1) // off���¶�� CoffeeMachine on
		{
			MachineOn();
		}
	}
}

void MachineOn()
{
	statusData.status = 100; // wait
	PowerInterface(0);							//CoffeeMachine On ���
}

void Shutdown()
{
	statusData.status = -1; // off
	PowerInterface(1);							//CoffeeMachine Off ���
    clicked = 0;
	// FileInterface(); �� �Լ�
}
