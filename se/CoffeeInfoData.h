#pragma once
#include <stdio.h>
#include "datas.h"

struct CoffeeInfoData {
	int concentrate;
	int temperature;
	struct IngredientData *ingredientData;
};
