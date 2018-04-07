#include <stdio.h>
#include "ButtonManager.h"
#include "SensorManager.h"
#include "CoffeeMachineController.h"
#include "ReserveController.h"
#include "ShutdownController.h"
#include <unistd.h>
#include <pthread.h>

void *th_Managers(void *arg) {
	while(1) {
		ButtonManager();
		SensorManager();

		usleep(1000);
	}
}

void *th_CMC(void *arg) {
	while(1) {
		CoffeeMachineController();

		usleep(1000);
	}
}

void *th_RC(void *arg) {
	while(1) {
		ReserveController();

		usleep(100000);
	}
}

void *th_SDC(void *arg) {
	while(1) {
		ShutdownController();

		usleep(1000);
	}
}

int main() {
	pthread_t th[5];
	int thr[5];
	system("clear");

	thr[0] = pthread_create(&th[0], NULL, th_Managers, NULL);
	thr[1] = pthread_create(&th[1], NULL, th_CMC, NULL);
	thr[2] = pthread_create(&th[2], NULL, th_RC, NULL);
	thr[3] = pthread_create(&th[3], NULL, th_SDC, NULL);

	thr[0] = pthread_join(th[0], NULL);
	thr[1] = pthread_join(th[1], NULL);
	thr[2] = pthread_join(th[2], NULL);
	thr[3] = pthread_join(th[3], NULL);

	return 0;
}
