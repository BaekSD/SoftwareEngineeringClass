#pragma once
#include <stdio.h>
#include "datas.h"
#include <stdlib.h>

int PowerButtonInterface()	{	// check power button
	if(buttonInput.powerBtn == 1)	{	// if push
		buttonInput.powerBtn--; 	// init
		return 1;
	}
	else
		return 0;
		 
}

int CleanButtonInterface()	{	// check clean button
	if(buttonInput.cleanBtn == 1)	{	// if push
		buttonInput.cleanBtn--;		// init
		return 1;
	}
	else
		return 0;

}

int ExtractButtonInterface()	{	// check extract button
	if(buttonInput.extractBtn == 1)	{	// if push
		buttonInput.extractBtn--;	// init
		return 1;
	}
	else
		return 0;
}

int* ReserveButtonInterface()	{	// check reserve button
	int* temp;
	temp = (int*)malloc(sizeof(int)*3);		// because input must be init
	if(buttonInput.reserveBtn[2] == 1)	{	// if check button push
		temp[0] = 0;
		temp[1] = 0;
		temp[2] = 1;
		buttonInput.reserveBtn[2]--;	//
		buttonInput.reserveBtn[0] = 0;	// init
		buttonInput.reserveBtn[1] = 0;	//
        buttonInput.reserveBtn[3] = 0;
	}
	else if(buttonInput.reserveBtn[3] == 1)	{	// if cancel button push
		temp[0] = 0;
		temp[1] = 0;
		temp[2] = -1;
		buttonInput.reserveBtn[3] = 0;	//
		buttonInput.reserveBtn[0] = 0;	// init
		buttonInput.reserveBtn[1] = 0;	//
	}
	else if(buttonInput.reserveBtn[0] == 1) {
        temp[0] = 1;
        temp[1] = 0;
        temp[2] = 0;
        buttonInput.reserveBtn[0] = 0;
    } else if(buttonInput.reserveBtn[1] == 1) {
        temp[0] = 0;
        temp[1] = 1;
        temp[2] = 0;
        buttonInput.reserveBtn[1] = 0;
    } else {
        return NULL;
    }
    return temp;
}

int ConcentrateButtonInterface()	{	// check concentrate button
	if(buttonInput.concentrate == 1)	{
		buttonInput.concentrate--;
		return 1;
	}
	else
		return 0;
}

int TemperatureButtonInterface()	{	// check temperature button
	if(buttonInput.temperature == 1)	{
		buttonInput.temperature--;
		return 1;
	}
	else
		return 0;
}
