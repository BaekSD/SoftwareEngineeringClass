#pragma once
#include <stdio.h>
#include <unistd.h>
#include "datas.h"
#include "ViewInterface.h"
#include "SoundInterface.h"
#include "MessageSoundData.h"
#include <pthread.h>
#include "gotoxy.h"
#include <time.h>
#include <signal.h>
#include <setjmp.h>

void LCDSoundController(struct MessageSoundData *messageSoundData);
void WaitForOutputs();
void PrintMessage(char* msg);
void WarningSound(int beep);

struct MessageSoundData *messageSoundData1 = NULL;

int waitEnable = 1;
static int menu = -1;
static pthread_t th0;
static int thr0;
static int printEnable = 0;

void printMainInfo() {
    gotoxy(1,1);
    printf("*******************************\n");
    printf("*****Coffee Machine System*****\n");
    printf("*******************************\n");
    printf("Status \t");
    if(statusData.status == 0 || statusData.status == 100) {
        printf("   Wait                        \n");
    } else if(statusData.status == 1) {
        printf("Extract                        \n");
    } else if(statusData.status == 2) {
        printf("  Clean                        \n");
    } else {
        printf("    off                        \n");
    }
    printf("Conc.  \t");
    if(buttonData.concentrate == 100) {
        printf("   Soft                        \n");
    } else if(buttonData.concentrate == 200) {
        printf(" Midium                        \n");
    } else {
        printf(" Strong                        \n");
    }
    printf("Temp.  \t");
    if(buttonData.temperature == 0) {
        printf("    ICE                        \n");
    } else {
        printf("    Hot                        \n");
    }
    printf("Water  \t%5dml                        \n",ingredientData.water);
    printf("Bean   \t%6dg                         \n",ingredientData.bean);
    printf("Powder \t");
    if(ingredientData.coffeePowder >= 10) {
        printf("      O                        \n");
    } else {
        printf("      X                        \n");
    }
    if(statusData.removeNeed == 1) {
        printf("Remove the Coffee Powder                  \n");
    } else {
        printf("                                          \n");
    }
    
    printf("Reserve Buttons                        \n");
    printf(" -Mode\t");
    if(buttonData.reserveInfo[0] == 0) {
        printf("Extract                            \n");
    } else {
        printf("Clean                              \n");
    }
    printf(" -Time\t%-10d\n",buttonData.reserveInfo[1]);
    
    printf("                                    \n");
    printf("Reserve Info                        \n");
    printf(" -Mode  ");
    if(reserveData.mode == 0) {
        printf("Extract                            \n");
    } else if(reserveData.mode == 1) {
        printf("Clean                              \n");
    } else {
        printf("No Reserves                        \n");
    }
    printf(" -Time  %-10d                        \n",reserveData.remainTime);
    printf("                                    \n");
    
    //default print end
}

void *th_LSC_self(void *arg) {
    int i;
	while(1) {
        if(statusData.status == 100)
            continue;
        while(printEnable != 0) {}
        printMainInfo();
        printEnable = 1;
        
        usleep(1000000/60);
	}
}

void *th_print(void *arg) {
    int i,j;
    while(1) {
        while(printEnable != 1){}
        /*
         for(i=0; i<13; i++)
         printf("                                                      \n");
         gotoxy(0,15);
         */
        gotoxy(0,18);
        printf("\n");
        
        if(statusData.status == 0 || statusData.status == -1) {
            WaitForOutputs();
        } else if(statusData.status == 1) {
            for(i=0; i<30; i++)
                printf("                                                      \n");
            gotoxy(0,18);
            printf("\n===============================\n");
            printf("Coffee Extracting Process\n\n");
            usleep(10000);
            if(statusData.statusDetail == -1) {
                statusData.statusDetail = 0;
                printf("Shortage of Ingredients\n");
                printf("Please replenish the Ingredients\n");
                usleep(2000000);
            } else if(statusData.removeNeed == 1) {
                printf("Remove Coffee Powder First\n");
                usleep(2000000);
            } else {
                if(statusData.statusDetail == 1) {
                    gotoxy(0,22);
                    printf("Grinding      \n");
                    for(i=0; i<10; i++) {
                        for(j=0; j<i%4; j++) {
                            gotoxy(j+9,22);
                            printf(".\n");
                            usleep(500000);
                        }
                        if(statusData.status == 0)
                            break;
                        gotoxy(9,22);
                        printf("     \n");
                    }
                }
                if(statusData.statusDetail == 0) {
                    gotoxy(0,22);
                    printf("Boiling       \n");
                    for(i=0; i<20; i++) {
                        for(j=0; j<i%4; j++) {
                            gotoxy(j+8,22);
                            printf(".\n");
                            usleep(500000);
                        }
                        if(statusData.status == 0)
                            break;
                        gotoxy(8,22);
                        printf("     \n");
                    }
                }
                if(statusData.statusDetail == 2) {
                    gotoxy(0,22);
                    printf("Extracting    \n");
                    for(i=0; i<20; i++) {
                        for(j=0; j<i%4; j++) {
                            gotoxy(j+11,22);
                            printf(".\n");
                            usleep(500000);
                        }
                        if(statusData.status == 0)
                            break;
                        gotoxy(11,22);
                        printf("     \n");
                    }
                }
                if(statusData.status == 10) {
                    gotoxy(0,23);
                    printf("Extracting Complete!            \n");
                    printf("Concentrate: ");
                    if(reserveData.concentrate == 100) {
                        printf("SOFT             \n");
                    } else if(reserveData.concentrate == 200) {
                        printf("MIDIUM           \n");
                    } else {
                        printf("STRONG           \n");
                    }
                    printf("Temperature: ");
                    if(reserveData.temperature == 0) {
                        printf("ICE              \n");
                    } else {
                        printf("HOT              \n");
                    }
                    sleep(2);
                    messageSoundData1->msg = NULL;
                }
                statusData.removeNeed = 1;
            }
            statusData.status = 0;
        } else if(statusData.status == 2) {
            for(i=0; i<30; i++)
                printf("                                                      \n");
            gotoxy(0,18);
            printf("\n===============================\n");
            printf("Cleaning");
            for(i=0; i<20; i++) {
                for(j=0; j<i%4; j++) {
                    if(messageSoundData1->msg != NULL) {
                        gotoxy(0,20);
                        PrintMessage(messageSoundData1->msg);
                        messageSoundData1->msg = NULL;
                        statusData.status = 0;
                        break;
                    }
                    gotoxy(j+9,20);
                    printf(".\n");
                    usleep(500000);
                }
                if(statusData.status == 0)
                    break;
                gotoxy(9,20);
                printf("     \n");
            }
            if(statusData.status != 0) {
                gotoxy(0,20);
                PrintMessage("Cleaning Complete!\n");
                messageSoundData1->msg = NULL;
                statusData.status = 0;
            }
        }
        
        /*
        if(statusData.status != 0 && statusData.status != -1) {
            for(i=0; i<23; i++)
                printf("                                                      \n");
            continue;
        } else {
            WaitForOutputs();
        }
        
        if(messageSoundData1->msg != NULL) {
            waitEnable = 0;
        } else {
            waitEnable = 1;
        }
         */
        
        /*
         if(!waitEnable) {
         PrintMessage(messageSoundData1->msg);
         } else {
         WaitForOutputs();
         }
         
         if(messageSoundData1->beep > 0) {
         WarningSound(messageSoundData1->beep);
         }
         */
        
        printEnable = 0;
    }
}

void *th_input(void *arg) {
    while(1) {
        scanf("%d",&menu);
    }
}

void LCDSoundController(struct MessageSoundData *messageSoundData) {
	static pthread_t th[2];
	static int thr[2];
    
    messageSoundData1 = messageSoundData;

    thr[0] = pthread_create(&th[0], NULL, th_LSC_self, NULL);
    thr[1] = pthread_create(&th[1], NULL, th_print, NULL);
    thr0 = pthread_create(&th0, NULL, th_input, NULL);
}

void WaitForOutputs() {
    int amount;
    int i;
    
    menu = 98761234;
    
    if(clicked == 1)
        return;
    
    if(statusData.status == -1) {
        printf("=========Power off=========          \n");
        printf("1. Power On                          \n");
        printf("2. Exit                              \n");
        printf("===========================          \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        printf("                                     \n");
        gotoxy(0,22);
        printf("\n");
        
        menu = 98761234;
        while(1) {
            if(statusData.status != -1 || menu != 98761234) {
                break;
            }
            usleep(10000);
        }
        
        clicked = 0;
        if(menu == 1)
            buttonInput.powerBtn = 1;
        else if(menu == 2)
            exit(0);
        else if(menu != 98761234) {
            printf("Invalid Input...\n");
            sleep(1);
        }
        return;
    } else if(statusData.status != 0) {
        return;
    }
    
    if(statusData.status == 0) {

        printf("========Select Menu========           \n");
        printf("1.  Power Button                      \n");
        printf("2.  Clean Button                      \n");
        printf("3.  Extract Button                    \n");
        printf("4.  Reserve Mode Toggle               \n");
        printf("5.  Reserve Time Increase             \n");
        printf("6.  Reserve Confirm                   \n");
        printf("7.  Reserve Cancel                    \n");
        printf("8.  Concentrate Button                \n");
        printf("9.  Temperature Button                \n");
        printf("10. Replenish Ingredients             \n");
        printf("11. Remove Coffee Powder              \n");
        printf("===========================           \n");
        printf("                                      \n");
        printf("                                      \n");
	
        clicked = 0;
        
        menu = 98761234;
        gotoxy(0,31);
        printf("\n");
        while(1) {
            if(statusData.status != 0 || menu != 98761234) {
                break;
            }
            usleep(10000);
        }
    
        waitEnable = 0;
        switch(menu) {
            case 1:
                buttonInput.powerBtn = 1;
                break;
            case 2:
                buttonInput.cleanBtn = 1;
                break;
            case 3:
                buttonInput.extractBtn = 1;
                break;
            case 4:
                buttonInput.reserveBtn[0] = 1;
                break;
            case 5:
                buttonInput.reserveBtn[1] = 1;
                break;
            case 6:
                buttonInput.reserveBtn[2] = 1;
                break;
            case 7:
                buttonInput.reserveBtn[3] = 1;
                break;
            case 8:
                buttonInput.concentrate = 1;
            break;
            case 9:
                buttonInput.temperature = 1;
                break;
            case 98761234:
                break;
            case 10:
                printf("\n=====Select Ingredient=====          \n");
                printf("1. Coffee Bean                       \n");
                printf("2. Coffee Powder                     \n");
                printf("3. Water                             \n");
                printf("===========================          \n");
            
                menu = 98761234;
                while(1) {
                    if(statusData.status != 0 || menu != 98761234) {
                        break;
                    }
                    usleep(10000);
                }
            
                if(menu == 98761234)
                    break;
            
                printf("\n");
                switch(menu) {
                    case 1:
                        printf("Input Coffee Bean amount                     \n");
                    
                        menu = 98761234;
                        while(1) {
                            if(statusData.status != 0 || menu != 98761234) {
                                break;
                            }
                            usleep(10000);
                        }
                    
                        if(menu == 98761234)
                            break;
                    
                        if(ingredientData.bean + menu <= 100) {
                            //fill
                            while(ingredientDataAccess == 1) {};
                            ingredientDataAccess = 1;
                            ingredientData.bean += menu;
                            ingredientDataAccess = 0;
                            printf("Coffee Bean is replenished successfully!\n");
                            sleep(1);
                        } else {
                            printf("Maximum Bean amount is 100g (remain: %dg)\n",ingredientData.bean);
                            sleep(1);
                        }
                        break;
                    case 2:
                        while(ingredientDataAccess == 1) {};
                        ingredientDataAccess = 1;
                        ingredientData.coffeePowder = 10;
                        ingredientDataAccess = 0;
                        printf("Coffee Powder is replenished successfully!\n");
                        sleep(1);
                        break;
                    case 3:
                        printf("Input Water amount                     \n");
                    
                        menu = 98761234;
                        while(1) {
                            if(statusData.status != 0 || menu != 98761234) {
                                break;
                            }
                            usleep(10000);
                        }
                    
                        if(menu == 98761234)
                            break;
                    
                        if(ingredientData.water + menu <= 1000) {
                            while(ingredientDataAccess == 1) {};
                            ingredientDataAccess = 1;
                            ingredientData.water += menu;
                            ingredientDataAccess = 0;
                            printf("Water is replenished successfully!\n");
                            sleep(1);
                        } else {
                            printf("Maximum Water amount is 1000ml (remain: %dml)\n",ingredientData.water);
                            sleep(1);
                        }
                        break;
                    default:
                        printf("Invalid Input..\n");
                        sleep(1);
                }
                gotoxy(0,31);
                for(i=0; i<15; i++)
                    printf("                                                    \n");
                break;
            case 11:
                statusData.removeNeed = 0;
                printf("Coffee Powder Removed!\n");
                sleep(1);
                break;
            default:
                printf("Invalid Input...\n");
                sleep(1);
                clicked = 0;
        
        }
        usleep(100000);
        menu = 98761234;
    }
}

void PrintMessage(char* msg) {
	ViewInterface(msg);
}

void WarningSound(int beep) {
	SoundInterface(beep);
}
