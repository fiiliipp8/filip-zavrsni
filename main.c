//3.
//4.
//5.
//6.
//8.
//10.
//16.
//18.
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
		
		scanf("%d", &izbor);

		switch (izbor) {
		case 1:
			igraci_domace();
			break;
		case 2:
			igraci_gostujuce();
			break;
		case 3:
			ispisi_igrace();
			break;
		case 4:
			izbrisi_igraca();
			break;
		default:
			printf("Neispravan izbor\n");
			break;
		}


	} while (1);

	return 0;
}
