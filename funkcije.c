#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


void ispis_izbornika() {

	printf("***ZAPNISNIK NOGOMETNE UTAKMICE***\n");
	printf("1. Unesi igrace domace momcadi\n");
	printf("2. Unesi igrace gostujuce momcadi\n");
	printf("3. Ispisi igrace\n");
	printf("4. Obrisi igraca\n");

}


void igraci_domace() {
	FILE* pokazivacDatoteke = fopen("igracii.txt", "a");
	if (pokazivacDatoteke == NULL) {
		perror("Ne mogu otvoriti dadoteku\n");
		return;
	}
	IGRAC c;

	printf("Unesite ime igraca: ");
	scanf("%s", c.ime);
	fprintf(pokazivacDatoteke, c.ime);
	fprintf(pokazivacDatoteke, "\n");
	printf("Unesite prezime igraca: ");
	scanf("%s", c.prezime);
	fprintf(pokazivacDatoteke, c.prezime);
	fprintf(pokazivacDatoteke, "\n");

	printf("Unesite broj igraca: ");
	scanf("%d", c.broj);
	fprintf(pokazivacDatoteke, c.broj);
	fprintf(pokazivacDatoteke, "\n");


	fclose(pokazivacDatoteke);
	printf("Igrac dodan.\n");
}

void igraci_gostujuce() {
	FILE* pokazivacDatoteke = fopen("igracii.txt", "a");
	if (pokazivacDatoteke == NULL) {
		perror("Ne mogu otvoriti dadoteku\n");
		return;
	}
	IGRAC c;

	printf("\nUnesite ime igraca: ");
	scanf("%s", c.ime);
	fprintf(pokazivacDatoteke, c.ime);
	fprintf(pokazivacDatoteke, "\n");
	printf("\nUnesite prezime igraca: ");
	scanf("%s", c.prezime);
	fprintf(pokazivacDatoteke, c.prezime);
	fprintf(pokazivacDatoteke, "\n");

	printf("\nUnesite broj igraca: ");
	scanf("%d", c.broj);
	fprintf(pokazivacDatoteke, c.broj);
	fprintf(pokazivacDatoteke, "\n");


	fclose(pokazivacDatoteke);
	printf("Igrac dodan.\n");
}

void ispisi_igrace() {
	FILE* pokazivacDatoteke = fopen("igracii.txt", "r"); 
	if (pokazivacDatoteke == NULL) {
		printf("Ne mogu otvoriti dadoteku\n");
		return;
	}
	IGRAC c;


	static char citanjeDatoteke[5000];
	while (!feof(pokazivacDatoteke))
	{
		fgets(citanjeDatoteke, 5000, pokazivacDatoteke);
		puts(citanjeDatoteke);
	}

	fclose(pokazivacDatoteke);
}


void izbrisi_igraca() {
	char imeDat[] = "igracii.txt";
	char imeZaObrisat[20];

	printf("Unesite ime igraca kojega zelite izbrisati: ");
	scanf("%s", imeZaObrisat);

	FILE* fp = fopen(imeDat, "r+");
	if (fp == NULL) {
		printf("Ne moze se otvoriti datoteka %s\n", imeDat);
		return 1;
	}


	char tempFilename[] = "temp.txt";
	FILE* tempFp = fopen(tempFilename, "w");
	char line[100];
	while (fgets(line, 100, fp) != NULL) {
		char* token = strtok(line, ",");
		if (strcmp(token, imeZaObrisat) != 0) {
			fputs(line, tempFp);
		}
	}

	fclose(fp);
	fclose(tempFp);

	remove(imeDat);
	rename(tempFilename, imeDat);

	printf("Igrac %s je uspijesno obrisan.\n", imeZaObrisat);
}


