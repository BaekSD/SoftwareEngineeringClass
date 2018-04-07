#pragma once
#include <stdio.h>

static int buttonDataAccess;
static int ingredientDataAccess;
static int clicked = 0;

/*
how to use access variable

while(buttonDataAccess==1) {};
buttonDataAccess=1;

*****buttonData use*****

buttonDataAccess=0;

*/

struct ButtonInput {
	int powerBtn;
	int cleanBtn;
	int extractBtn;
	int reserveBtn[4];		//mode, time, confirm, cancel
	int concentrate;
	int temperature;
};

struct ButtonData {
	int powerBtn;
	int cleanBtn;
	int extractBtn;
	int reserveInfo[3];		//mode, time, isReserved	isReserved == 0: no reserves, -1:cancel
	int concentrate;
	int temperature;
};

struct IngredientData {
	int water;			//max: 1000
	int bean;			//max: 100
	int coffeePowder;		//max: 10, we need 10g of powder when make coffee
};

struct ReserveData {
	int mode;			//0:coffee, 1:clean, -1:no reserve
    int concentrate;
    int temperature;
	int remainTime;
};

struct StatusData {
	int status;			//0:wait, 1:making, 2:cleaning, -1:off
	int statusDetail;		//if status==1, 0:boil, 1:grind, 2:make
    int removeNeed;
};

struct ButtonInput buttonInput = {0,0,0,{0,0,0,0},0,0};
struct ButtonData buttonData = {0,0,0,{0,0,0},100,0};
struct IngredientData ingredientData = {0,0,0};
struct StatusData statusData = {100,0,0};
struct ReserveData reserveData = {-1,0,0,0};
