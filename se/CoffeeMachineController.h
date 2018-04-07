#pragma once
#include <stdio.h>
#include "datas.h"
#include "LCDSoundController.h"
#include "MakeCoffeeController.h"
#include "CoffeeInfoData.h"
#include "FileInterface.h"
#include <unistd.h>
#include <pthread.h>
#include "gotoxy.h"

void CoffeeMachineController();
void CleanMachine();
void Wait();

static struct CoffeeInfoData coffeeInfoData0 = {0,0,&ingredientData};
static struct MessageSoundData messageSoundData0 = {NULL, 0};

void *th_CMC_self(void *arg) {
	while(1) {
		if(statusData.status == 0) {
			if(buttonData.cleanBtn == 1) {
				statusData.status = 2;
				CleanMachine();
			} else if(buttonData.extractBtn == 1) {
				statusData.status = 1;
				coffeeInfoData0.concentrate = buttonData.concentrate;
				coffeeInfoData0.temperature = buttonData.temperature;
            } else if(reserveData.mode == 1 && reserveData.remainTime <= 0) {
				statusData.status = 2;
				CleanMachine();
			} else if(reserveData.mode == 0 && reserveData.remainTime <= 0) {
                statusData.status = 1;
				coffeeInfoData0.concentrate = reserveData.concentrate;
				coffeeInfoData0.temperature = reserveData.temperature;
			} else {
				Wait();
			}
		}

		usleep(1000000/60);
	}
}

void CoffeeMachineController()
{
	pthread_t th;
    int thr;
    
    MakeCoffeeController(&coffeeInfoData0);
    LCDSoundController(&messageSoundData0);

	thr = pthread_create(&th, NULL, th_CMC_self, NULL);
	thr = pthread_join(th, NULL);
}

void CleanMachine(void)
{
    if(statusData.status != 2)
        return;
	int i,j;
    //gotoxy(0,15);
    
    while (buttonDataAccess == 1)
    {
    }
    buttonDataAccess = 1;
    if(buttonData.cleanBtn == 1)
        buttonData.cleanBtn = 0;
    else
        buttonInput.reserveBtn[3] = 1;
    buttonDataAccess = 0;
    
    if (ingredientData.water < 500)
    {
        messageSoundData0.msg = "Lack of Water";
        //statusData.status = 0;
        
        return;
    }
    
    //gotoxy(0,15);
    //printf("Cleaning");
    
    /*
    for(i=0; i<20; i++) {
        for(j=0; j<i%4; j++) {
            if(j==0)
                messageSoundData0.msg = "Cleaning";
            else if(j==1)
                messageSoundData0.msg = "Cleaning.";
            else if(j==2)
                messageSoundData0.msg = "Cleaning..";
            else if(j==3)
                messageSoundData0.msg = "Cleaning...";
            //gotoxy(i%4+9,15);
            //printf(".\n");
        }
        usleep(500000);
    }
     */
    
    sleep(10);
    
    //printf("Cleaning Complete!\n");
    messageSoundData0.msg = "Cleaning Complete!";
    
    usleep(400000);
    
    while (ingredientDataAccess == 1)
    {
    }
    ingredientDataAccess = 1;
    ingredientData.water -= 500;
    ingredientDataAccess = 0;
		
    statusData.status = 0;
    messageSoundData0.msg = NULL;
}

void Wait(void)
{
    FileInterface();
}
