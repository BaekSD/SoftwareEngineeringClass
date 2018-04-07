#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "ButtonInterface.h"
#include "CUnit/Basic.h"

void test_PowerButtonInterface() {
	int a = -1;
	buttonInput.powerBtn = 0;
	a = PowerButtonInterface();
	CU_ASSERT(a == 0);

	buttonInput.powerBtn = 1;
	a = PowerButtonInterface();
	CU_ASSERT(a == 1 && buttonInput.powerBtn == 0);
}

void test_CleanButtonInterface() {
	int a = -1;
	buttonInput.cleanBtn = 0;
	a = CleanButtonInterface();
	CU_ASSERT(a == 0);

	buttonInput.cleanBtn = 1;
	a = CleanButtonInterface();
	CU_ASSERT(a == 1 && buttonInput.cleanBtn == 0);
}

void test_ExtractButtonInterface() {
	int a = -1;
	buttonInput.extractBtn = 0;
	a = ExtractButtonInterface();
	CU_ASSERT(a == 0);

	buttonInput.extractBtn = 1;
	a = ExtractButtonInterface();
	CU_ASSERT(a == 1 && buttonInput.extractBtn == 0);
}

void test_ReserveButtonInterface() {
	int i,j,k;
	int *a = NULL;
	
	for(i=0; i<=1; i++) {
		for(j=0; j<=1; j++) {
			for(k=0; k<=1; k++) {
				buttonInput.reserveBtn[0] = i;
				buttonInput.reserveBtn[1] = j;
				buttonInput.reserveBtn[2] = 1;
				buttonInput.reserveBtn[3] = k;
				a = ReserveButtonInterface();
				CU_ASSERT(buttonInput.reserveBtn[0] == 0 && buttonInput.reserveBtn[1] == 0 &&
					buttonInput.reserveBtn[2] == 0 && buttonInput.reserveBtn[3] == 0 &&
					a[0] == 0 && a[1] == 0 && a[2] == 1);
			}
		}
	}

	for(i=0; i<=1; i++) {
		for(j=0; j<=1; j++) {
			buttonInput.reserveBtn[0] = i;
			buttonInput.reserveBtn[1] = j;
			buttonInput.reserveBtn[2] = 0;
			buttonInput.reserveBtn[3] = 1;
			a = ReserveButtonInterface();
			CU_ASSERT(buttonInput.reserveBtn[0] == 0 && buttonInput.reserveBtn[1] == 0 &&
				buttonInput.reserveBtn[2] == 0 && buttonInput.reserveBtn[3] == 0 &&
				a[0] == 0 && a[1] == 0 && a[2] == -1);
		}
	}

	for(i=0; i<=1; i++) {
		buttonInput.reserveBtn[0] = 1;
		buttonInput.reserveBtn[1] = i;
		buttonInput.reserveBtn[2] = 0;
		buttonInput.reserveBtn[3] = 0;
		a = ReserveButtonInterface();
		CU_ASSERT(buttonInput.reserveBtn[0] == 0 && a[0] == 1 && a[1] == 0 && a[2] == 0);
	}

	buttonInput.reserveBtn[0] = 0;
	buttonInput.reserveBtn[1] = 1;
	buttonInput.reserveBtn[2] = 0;
	buttonInput.reserveBtn[3] = 0;
	a = ReserveButtonInterface();
	CU_ASSERT(buttonInput.reserveBtn[1] == 0 && a[0] == 0 && a[1] == 1 && a[2] == 0);

	buttonInput.reserveBtn[0] = 0;
	buttonInput.reserveBtn[1] = 0;
	buttonInput.reserveBtn[2] = 0;
	buttonInput.reserveBtn[3] = 0;
	a = ReserveButtonInterface();
	CU_ASSERT(a == NULL);
}

void test_ConcentrateButtonInterface() {
	int a = -1;
	buttonInput.concentrate = 0;
	a = ConcentrateButtonInterface();
	CU_ASSERT(a == 0);

	buttonInput.concentrate = 1;
	a = ConcentrateButtonInterface();
	CU_ASSERT(a == 1 && buttonInput.concentrate == 0);
}

void test_TemperatureButtonInterface() {
	int a = -1;
	buttonInput.temperature = 0;
	a = TemperatureButtonInterface();
	CU_ASSERT(a == 0);

	buttonInput.temperature = 1;
	a = TemperatureButtonInterface();
	CU_ASSERT(a == 1 && buttonInput.temperature == 0);
}

int main() {
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("ButtonInterface_Suite",NULL,NULL);
	if(pSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(CU_add_test(pSuite, "test of PowerBtnInter", test_PowerButtonInterface) == NULL ||
		CU_add_test(pSuite, "test of CleanBtnInter", test_CleanButtonInterface) == NULL ||
		CU_add_test(pSuite, "test of ExtractBtnInter", test_ExtractButtonInterface) == NULL ||
		CU_add_test(pSuite, "test of ReserveBtnInter", test_ReserveButtonInterface) == NULL ||
		CU_add_test(pSuite, "test of ConcBtnInter", test_ConcentrateButtonInterface) == NULL ||
		CU_add_test(pSuite, "test of TempBtnInter", test_TemperatureButtonInterface) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
