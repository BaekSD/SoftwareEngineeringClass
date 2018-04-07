#pragma once
#include <stdio.h>
#include "datas.h"

void FileInterface()	{
    while(ingredientDataAccess == 1 || ingredientDataAccess == 100) {}
    ingredientDataAccess = 1;
	FILE *fp = fopen("fileInfo.txt", "wt");
	if(fp == NULL)	{
		printf("fail\n");
		return;
	}
	if(statusData.status==0)	{
		fprintf(fp, "0\n");
		fprintf(fp, "%d\n", ingredientData.water);
		fprintf(fp, "%d\n", ingredientData.bean);
		fprintf(fp, "%d\n", ingredientData.coffeePowder);
	}
	else	{
		fprintf(fp, "1\n");
		fprintf(fp, "%d\n", ingredientData.water);
		fprintf(fp, "%d\n", ingredientData.bean);
		fprintf(fp, "%d\n", ingredientData.coffeePowder);
	}
    fclose(fp);
    ingredientDataAccess = 0;
}
