#pragma once
#include <stdio.h>
#include <unistd.h>

int CoffeeMachineInterface(int command) {       //0:grind, 1:boil, 2:extract
    int ret = 0;
    if(command == 0) {
        
        sleep(5);
        
    } else if(command == 1) {
        
        sleep(10);
        
    } else if(command == 2) {
        
        sleep(10);
        
    } else {
        ret = -10;
    }
    
    return ret;
}
