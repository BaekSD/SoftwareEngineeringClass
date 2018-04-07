#pragma once
#include <stdio.h>
#include "ButtonManager.h"
#include "CUnit/Basic.h"

void test_ButtonManager() {
	int i,j,k;

	buttonInput.powerBtn = 1;
	ButtonManager();
	CU_ASSERT(buttonData.powerBtn == 1);

	buttonInput.cleanBtn = 1;
	ButtonManager();
	CU_ASSERT(buttonData.cleanBtn == 1);
	
	buttonInput.extractBtn = 1;
	ButtonManager();
	CU_ASSERT(buttonData.extractBtn == 1);

	buttonInput.concentrate = 1;
	buttonData.concentrate = 100;
	ButtonManager();
	CU_ASSERT(buttonData.concentrate == 200);

	buttonInput.concentrate = 1;
	buttonData.concentrate = 200;
	ButtonManager();
	CU_ASSERT(buttonData.concentrate == 300);

	buttonInput.concentrate = 1;
	buttonData.concentrate = 300;
	ButtonManager();
	CU_ASSERT(buttonData.concentrate == 100);

	buttonInput.temperature = 1;
	buttonData.temperature = 1;
	ButtonManager();
	CU_ASSERT(buttonData.temperature == 0);

	buttonInput.temperature = 1;
	buttonData.temperature = 0;
	ButtonManager();
	CU_ASSERT(buttonData.temperature == 1);

	for(i=0; i<=1; i++) {
		buttonInput.reserveBtn[0] = 1;
		buttonInput.reserveBtn[1] = i;
		buttonInput.reserveBtn[2] = 0;
		buttonInput.reserveBtn[3] = 0;
		buttonData.reserveInfo[0] = 0;
		ButtonManager();
		CU_ASSERT(buttonData.reserveInfo[0] == 1);
	}

	for(i=0; i<=1; i++) {
		buttonInput.reserveBtn[0] = 1;
		buttonInput.reserveBtn[1] = i;
		buttonInput.reserveBtn[2] = 0;
		buttonInput.reserveBtn[3] = 0;
		buttonData.reserveInfo[0] = 1;
		ButtonManager();
		CU_ASSERT(buttonData.reserveInfo[0] == 0);
	}

	buttonInput.reserveBtn[0] = 0;
	buttonInput.reserveBtn[1] = 1;
	buttonInput.reserveBtn[2] = 0;
	buttonInput.reserveBtn[3] = 0;
	buttonData.reserveInfo[1] = 0;
	ButtonManager();
	CU_ASSERT(buttonData.reserveInfo[1] == 15);

	buttonInput.reserveBtn[0] = 0;
	buttonInput.reserveBtn[1] = 1;
	buttonInput.reserveBtn[2] = 0;
	buttonInput.reserveBtn[3] = 0;
	buttonData.reserveInfo[1] = 120;
	ButtonManager();
	CU_ASSERT(buttonData.reserveInfo[1] == 135);

	buttonInput.reserveBtn[0] = 0;
	buttonInput.reserveBtn[1] = 1;
	buttonInput.reserveBtn[2] = 0;
	buttonInput.reserveBtn[3] = 0;
	buttonData.reserveInfo[1] = 24*60 + 15;
	ButtonManager();
	CU_ASSERT(buttonData.reserveInfo[1] == 0);

	for(i=0; i<=1; i++) {
		for(j=0; j<=1; j++) {
			for(k=0; k<=1; k++) {
				buttonInput.reserveBtn[0] = i;
				buttonInput.reserveBtn[1] = j;
				buttonInput.reserveBtn[2] = 1;
				buttonInput.reserveBtn[3] = k;
				ButtonManager();
				CU_ASSERT(buttonData.reserveInfo[2] == 1);
			}
		}
	}

	for(i=0; i<=1; i++) {
		for(j=0; j<=1; j++) {
			buttonInput.reserveBtn[0] = i;
			buttonInput.reserveBtn[1] = j;
			buttonInput.reserveBtn[2] = 0;
			buttonInput.reserveBtn[3] = 1;
			ButtonManager();
			CU_ASSERT(buttonData.reserveInfo[2] == -1);
		}
	}
}

int main() {
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("ButtonManager_Suite",NULL,NULL);
	if(pSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(CU_add_test(pSuite, "test of ButtonManager", test_ButtonManager) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
