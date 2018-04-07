#pragma once
#include <stdio.h>
#include <unistd.h>

void ViewInterface(char* msg) {
	printf("%s\n",msg);
	sleep(3);
}
