#pragma once
#include <stdio.h>

void gotoxy(int x, int y) {
	printf("\033[%dd\033[%dG", y, x);
}
