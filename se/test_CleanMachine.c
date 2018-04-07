#pragma once
#include <stdio.h>
#include "CoffeeMachineController.h"
#include "CUnit/Basic.h"

void test_CleanMachine() {
	int i=0;

	for(i=0; i<500; i+=100) {
		ingredientData.water = i;
		CleanMachine();
		CU_ASSERT(ingredientData.water == i);
	}

	for(i=500; i<=1000; i+=200) {
		ingredientData.water = i;
		CleanMachine();
		CU_ASSERT(ingredientData.water == i-500);
	}
}

int main() {
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("CleanMachine_Suite",NULL,NULL);
	if(pSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(CU_add_test(pSuite, "test of CleanMachine", test_CleanMachine) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
