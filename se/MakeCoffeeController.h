#pragma once
#include <stdio.h>
#include <unistd.h>
#include "CoffeeInfoData.h"
#include "CoffeeMachineInterface.h"
#include <pthread.h>
#include "FileInterface.h"

void MakeCoffeeController(struct CoffeeInfoData *coffeeInfoData);
int GrindBean(struct CoffeeInfoData coffeeInfoData);
int BoilWater(struct CoffeeInfoData coffeeInfoData);
int MakeCoffee(struct CoffeeInfoData coffeeInfoData);

struct CoffeeInfoData *coffeeInfoData1 = NULL;

void *th_MCC_self(void *arg) {
	static int waitEnable = 1;
	int ret = 0;
    
    while(1) {
        if(statusData.status == 1) {
            
            while(buttonDataAccess == 1) {}
            buttonDataAccess = 1;
            if(buttonData.extractBtn == 1)
                buttonData.extractBtn = 0;
            else
                buttonInput.reserveBtn[3] = 1;
            reserveData.temperature = coffeeInfoData1->temperature;
            reserveData.concentrate = coffeeInfoData1->concentrate;
            buttonDataAccess = 0;
            
            if(statusData.removeNeed == 1) {
                continue;
            } else {
                if(coffeeInfoData1->ingredientData->coffeePowder<10 &&
                   coffeeInfoData1->ingredientData->bean>=10 &&
                   coffeeInfoData1->ingredientData->water>=coffeeInfoData1->concentrate) {
			
                    waitEnable = 0;
                    ret = GrindBean(*coffeeInfoData1);
                    if(ret < 0) {
                        statusData.status = 0;
                        continue;
                    }
                    if(coffeeInfoData1->temperature == 1) {
                        ret = BoilWater(*coffeeInfoData1);
                        if(ret < 0) {
                            statusData.status = 0;
                            continue;
                        }
                    } else if(coffeeInfoData1->temperature != 0) {
                        statusData.status = 0;
                        continue;
                    }
                    ret = MakeCoffee(*coffeeInfoData1);
                    if(ret < 0) {
                        statusData.status = 0;
                        continue;
                    }
                } else if(coffeeInfoData1->temperature==1 &&
                          coffeeInfoData1->ingredientData->coffeePowder>=10 &&
                          coffeeInfoData1->ingredientData->water>=coffeeInfoData1->concentrate) {
			
                    waitEnable = 0;
                    ret = BoilWater(*coffeeInfoData1);
                    if(ret < 0) {
                        statusData.status = 0;
                        continue;
                    }
            
                    ret = MakeCoffee(*coffeeInfoData1);
                    if(ret < 0) {
                        statusData.status = 0;
                        continue;
                    }
                } else if(coffeeInfoData1->temperature==0 &&
                          coffeeInfoData1->ingredientData->coffeePowder>=10 &&
                          coffeeInfoData1->ingredientData->water>=coffeeInfoData1->concentrate) {

                    waitEnable = 0;
                    ret = MakeCoffee(*coffeeInfoData1);
                    if(ret < 0) {
                        statusData.status = 0;
                        continue;
                    }
                } else {
                    statusData.statusDetail = -1;
                }
                if(statusData.statusDetail != -1) {
                    statusData.status = 10;
                }
            }
        }
    }
}

void MakeCoffeeController(struct CoffeeInfoData *coffeeInfoData) {
    static pthread_t th;
    static int thr;
    
    coffeeInfoData1 = coffeeInfoData;
    
    thr = pthread_create(&th, NULL, th_MCC_self, NULL);
}

int GrindBean(struct CoffeeInfoData coffeeInfoData) {
	int ret = 0;
	//grind process start

    statusData.statusDetail = 1;
    
    ret = CoffeeMachineInterface(0);
    
    while(ingredientDataAccess == 1) {}
    ingredientDataAccess = 1;
    coffeeInfoData.ingredientData->bean -= 10;
    coffeeInfoData.ingredientData->coffeePowder += 10;
    ingredientDataAccess = 0;
    
    FileInterface();
    
	//error - return -3;
	//grind process end

	return 0;
}

int BoilWater(struct CoffeeInfoData coffeeInfoData) {
	int ret = 0;
	//boil process start
    
    statusData.statusDetail = 0;

    ret = CoffeeMachineInterface(1);
    
	//error - return -4;
	//boil process end

	if(ret < 0) {
		return ret;
	}

	return 0;
}

int MakeCoffee(struct CoffeeInfoData coffeeInfoData) {
    int ret = 0;
	//make coffee process start
    
    statusData.statusDetail = 2;
    
    ret = CoffeeMachineInterface(2);
    
    while(ingredientDataAccess == 1) {}
    ingredientDataAccess = 1;
    coffeeInfoData.ingredientData->water -= coffeeInfoData.concentrate;
    coffeeInfoData.ingredientData->coffeePowder -= 10;
    ingredientDataAccess = 0;
    
    FileInterface();

	//error - return -5;
	//make coffee process end
    
    if(ret < 0) {
        return ret;
    }

	return 0;
}
