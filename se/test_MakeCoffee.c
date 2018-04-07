#pragma once
#include <stdio.h>
#include "MakeCoffeeController.h"
#include "CUnit/Basic.h"

void test_MakeCoffee() {
	struct CoffeeInfoData coffeeInfoData = {200,0,&ingredientData};
	ingredientData.water = 600;
	ingredientData.coffeePowder = 10;
	MakeCoffee(coffeeInfoData);
	CU_ASSERT(ingredientData.water == 400 && ingredientData.coffeePowder == 0);
}

int main() {
	CU_pSuite pSuite = NULL;

	if(CUE_SUCCESS != CU_initialize_registry()) {
		return CU_get_error();
	}

	pSuite = CU_add_suite("MakeCoffee_Suite",NULL,NULL);
	if(pSuite == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	if(CU_add_test(pSuite, "test of MakeCoffee", test_MakeCoffee) == NULL) {
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return CU_get_error();
}
