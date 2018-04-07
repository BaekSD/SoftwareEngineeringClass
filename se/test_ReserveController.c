#pragma once
#include <stdio.h>
#include "ReserveController.h"
#include "CUnit/Basic.h"

void test_ReserveController() {
	int i,j,k;

	for(j=0; j<=15*10; j+=15) {
		buttonData.reserveInfo[0] = 0;
		buttonData.reserveInfo[1] = j;
		buttonData.reserveInfo[2] = 1;
		ReserveController();
		CU_ASSERT(reserveData.mode == 0 && reserveData.remainTime == j &&
				reserveData.concentrate == buttonData.concentrate &&
				reserveData.temperature == buttonData.temperature &&
				buttonData.reserveInfo[2] == 0);
	}

	for(j=0; j<=15*10; j+=15) {
		buttonData.reserveInfo[0] = 1;
		buttonData.reserveInfo[1] = j;
		buttonData.reserveInfo[2] = 1;
		ReserveController();
		CU_ASSERT(reserveData.mode == 1 && reserveData.remainTime == j &&
				buttonData.reserveInfo[2] == 0);
	}

	for(i=0; i<=1; i++) {
		for(j=0; j<=15*10; j+=15) {
			buttonData.reserveInfo[0] = i;
			buttonData.reserveInfo[1] = j;
			buttonData.reserveInfo[2] = -1;
			ReserveController();
			CU_ASSERT(reserveData.mode == -1 && buttonData.reserveInfo[0] == 0 &&
					buttonData.reserveInfo[1] == 0 && buttonData.reserveInfo[2] == 0);
		}
	}

	for(i=0; i<=1; i++) {
		for(j=0; j<=15*10; j+=15) {
			for(k=1; k<300; k+=30) {
				buttonData.reserveInfo[0] = i;
				buttonData.reserveInfo[1] = j;
				buttonData.reserveInfo[2] = 0;
				reserveData.mode = 0;
				reserveData.remainTime = k;
				ReserveController();
				CU_ASSERT(reserveData.remainTime == k-1);
			}
		}
	}
}

int main() {
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("ReserveController_Suite",NULL,NULL);
	if(pSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(CU_add_test(pSuite, "test of ReserveController", test_ReserveController) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
