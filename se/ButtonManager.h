#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ButtonInterface.h"
#include "datas.h"

void ButtonManager()	{
	int num;
	int* get;
	get = ReserveButtonInterface();
    
    while(buttonDataAccess == 1) {}
    buttonDataAccess = 1;
    
    if(PowerButtonInterface() == 1)
        buttonData.powerBtn = 1;
    if(CleanButtonInterface() == 1)
        buttonData.cleanBtn = 1;
    if(ExtractButtonInterface() == 1)
        buttonData.extractBtn = 1;
    if(ConcentrateButtonInterface() == 1)	{
        if(buttonData.concentrate == 100) {
            buttonData.concentrate = 200;
        } else if(buttonData.concentrate == 200) {
            buttonData.concentrate = 300;
        } else {
            buttonData.concentrate = 100;
        }
    }
    if(TemperatureButtonInterface() == 1)	{
        buttonData.temperature++;
        if(buttonData.temperature == 2)	{	// if 2
            buttonData.temperature = 0;	// go 0
        }
    }
    if(get != NULL) {
        if(get[0] == 1) {
            if(buttonData.reserveInfo[0] == 0) {
                buttonData.reserveInfo[0] = 1;
            } else {
                buttonData.reserveInfo[0] = 0;
            }
        }
        if(get[1] == 1) {
            buttonData.reserveInfo[1] += 15;
            if(buttonData.reserveInfo[1] > 60*24) {
                buttonData.reserveInfo[1] = 0;
            }
        }
        if(get[2] != 0) {
            //buttonData.reserveInfo[1] = 0;
            buttonData.reserveInfo[2] = get[2];
        }
    }
    
    buttonDataAccess = 0;
}	
