#include <stdio.h>
#include "datas.h"
#include "SensorInterface.h"

void SensorManager()	{
    if(statusData.status == 100) {
        while(ingredientDataAccess == 1) { }
        ingredientDataAccess = 1;
        ingredientData.water = WaterSensorInterface();
        ingredientData.bean = BeanSensorInterface();
        ingredientData.coffeePowder = CoffeePowderSensorInterface();
        ingredientDataAccess = 0;
        statusData.status = 0;
    }
}

