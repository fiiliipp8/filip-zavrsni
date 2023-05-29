//3.
//4.
//6.
//8.
//10.
//16.
//19.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main() {
	int izbor;
	do {
		ispis_izbornika();
		printf("Unesite izbor: ");
		scanf("%d", &izbor);
		switch (izbor) {
		case 1:
			igraci_domace();
			break;
		case 2:
			igraci_gostujuce();
			break;
		case 3:
			mjesto_igranja();
			break;
		case 4:
			vrijeme_pocetka();
			break;
		case 5;
			strijelci();
			break;
		case 6;
			konacni_rezultat();
		default:
			printf("Neispravan izbor\n");
			break;
		}


	} while (1);

	return 0;
}
