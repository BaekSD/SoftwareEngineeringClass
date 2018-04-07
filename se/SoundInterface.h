#pragma once
#include <stdio.h>
#include <unistd.h>

void SoundInterface(int beep) {
	int i;
	for(i=0; i<beep; i++) {
		printf("B");
	}
    printf("\n");
	sleep(2);
	
}
