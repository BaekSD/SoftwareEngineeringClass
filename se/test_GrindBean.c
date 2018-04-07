#pragma once
#include <stdio.h>
#include "MakeCoffeeController.h"
#include "CUnit/Basic.h"

void test_GrindBean() {
	struct CoffeeInfoData coffeeInfoData = {0,0,&ingredientData};
	ingredientData.bean = 100;
	ingredientData.coffeePowder = 0;

	GrindBean(coffeeInfoData);
	CU_ASSERT(ingredientData.bean == 90 && ingredientData.coffeePowder == 10);
}

int main() {
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("GrindBean_Suite",NULL,NULL);
	if(pSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(CU_add_test(pSuite, "test of GrindBean", test_GrindBean) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
