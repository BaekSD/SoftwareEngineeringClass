#pragma once
#include <stdio.h>
#include "CoffeeMachineInterface.h"
#include "CUnit/Basic.h"

void test_CoffeeMachineInterface() {
	CU_ASSERT(CoffeeMachineInterface(0) == 0);
	CU_ASSERT(CoffeeMachineInterface(1) == 0);
	CU_ASSERT(CoffeeMachineInterface(2) == 0);
	CU_ASSERT(CoffeeMachineInterface(3) == -10);
	CU_ASSERT(CoffeeMachineInterface(-1) == -10);
}

int main() {
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("CoffeeMachineInterface_Suite",NULL,NULL);
	if(pSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(CU_add_test(pSuite, "test of CoffeeMachineInter", test_CoffeeMachineInterface) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
