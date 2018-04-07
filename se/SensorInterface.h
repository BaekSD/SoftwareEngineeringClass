#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int WaterSensorInterface()	{
	char *p;
    char *pp;
	char str[100];
	int len;
	int i;
	int amount = 0;
    
	FILE *fp = fopen("fileInfo.txt", "rt");
	if(fp == NULL) {
		return 0;
	}
	fgets(str, 100, fp);
    fgets(str, 100, fp);
    len = strlen(str);
    p = (char*)malloc(sizeof(char)*(len+1));
    pp = p;
	for(i=0; i<len; i++)	{
		p[i] = str[i];
	}
	if('0' <= *p && *p <= '9')	{
		for(amount=0; '0'<=*p && *p <= '9'; p++)	{
			amount *= 10;
			amount += *p - '0';
		}
	}
    
	free(pp);
    
    if(amount > 1000) {
        amount = 1000;
    } else if(amount < 0) {
        amount = 0;
    }
    
    fclose(fp);
    
	return amount;	
}
int BeanSensorInterface()	{
	char *p;
    char *pp;
	char str[100];
	int len;
	int i;
	int amount = 0;
	FILE *fp = fopen("fileInfo.txt", "rt");
	if(fp == NULL) {
		return 0;
	}
	fgets(str, 100, fp);
	fgets(str, 100, fp);
	fgets(str, 100, fp);
	len = strlen(str);
	p = (char*)malloc(sizeof(char)*(len+1));
    pp = p;
	for(i=0; i<len; i++)	{
		p[i] = str[i];
	}
	if('0' <= *p && *p <= '9')	{
		for(amount=0; '0'<=*p && *p <= '9'; p++)	{
			amount *= 10;
			amount += *p - '0';
		}
	}
	free(pp);
    if(amount > 100) {
        amount = 100;
    } else if(amount < 0) {
        amount = 0;
    }
    
    fclose(fp);
    
	return amount;
}
int CoffeePowderSensorInterface()	{
	char *p;
    char *pp;
	char str[100];
	int len;
	int i;
	int amount = 0;
	FILE *fp = fopen("fileInfo.txt", "rt");
	if(fp == NULL) {
		return 0;
	}
	fgets(str, 100, fp);
	fgets(str, 100, fp);
	fgets(str, 100, fp);
	fgets(str, 100, fp);
	len = strlen(str);
	p = (char*)malloc(sizeof(char)*(len+1));
    pp = p;
	for(i=0; i<len; i++)	{
		p[i] = str[i];
	}
	if('0' <= *p && *p <= '9')	{
		for(amount=0; '0'<=*p && *p <= '9'; p++)	{
			amount *= 10;
			amount += *p - '0';
		}
	}
	free(pp);
    if(amount > 10) {
        amount = 10;
    } else if(amount != 10) {
        amount = 0;
    }
    
    fclose(fp);
    
	return amount;
}
