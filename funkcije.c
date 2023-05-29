#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


void ispis_izbornika() {

	printf("ZAPNISNIK NOGOMETNE UTAKMICE\n");
	printf("1. Unesi igrace domace momcadi\n");
	printf("2. Unesi igrace gostujuce momcadi\n");
	printf("3. Unesi mjesto igranja utakmice\n");
	printf("4. Unesi vrijeme pocetka utakmice\n");
	printf("5. Unesi strijelce\n");
	printf("6. Unesi konacni rezultat\n");
}


void igraci_domace() {
	FILE* pokazivacDatoteke = fopen("igraci.txt", "a");
	if (pokazivacDatoteke == NULL) {
		perror("Ne mogu otvoriti dadoteku\n"); 
		return;
	}
	IGRAC c;
	
	printf("Unesite ime: ");
	scanf("%s", c.ime);
	printf("Unesite prezime: ");
	scanf("%s", c.prezime);
	printf("Unesite broj: ");
	scanf("%s", c.broj);
	
	
	fwrite(&c, sizeof(c), 1, pokazivacDatoteke);

	fclose(pokazivacDatoteke);
	printf("Igrac dodan.\n");
}
void igraci_gostujuce() {
	FILE* pokazivacDatoteke = fopen("igraci.txt", "a");
	if (pokazivacDatoteke == NULL) {
		perror("Ne mogu otvoriti dadoteku\n"); 
		return;
	}
	IGRAC c;
	
	printf("Unesite ime: ");
	scanf("%s", c.ime);
	printf("Unesite prezime: ");
	scanf("%s", c.prezime);
	printf("Unesite broj: ");
	scanf("%s", c.broj);
	
	
	fwrite(&c, sizeof(c), 1, pokazivacDatoteke);

	fclose(pokazivacDatoteke);
	printf("Igrac dodan.\n");
}


