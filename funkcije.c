#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> //7 
#include <stdlib.h>
#include "Header.h"
#include <string.h>

void kreiranje(char* datoteka, unsigned int* BrojIgraca) { //9

	FILE* fp = fopen(datoteka, "rb");

	if (fp == NULL) {

		perror("File"); //19

		fp = fopen(datoteka, "wb");

		if (fp == NULL) {

			perror("File");
			exit(EXIT_FAILURE);
		}
		else {

			fwrite(BrojIgraca, sizeof(unsigned int), 1, fp);
			fclose(fp);
			printf("Datoteka usijesno kreirana!\n");
		}
	}
	else {

		fread(BrojIgraca, sizeof(unsigned int), 1, fp);
		fclose(fp);
		printf("Datoteka postoji\n");
	}
}

void pocetniIzbornik() { //8
	printf("\nZAPISNIK NOGOMETNE UTAKMICE\n");
	printf("Izaberite opciju\n");
	printf("[1.] Dodaj igraca\n");
	printf("[2.] Pregled svih igraca\n");
	printf("[3.] Pretrazi igraca\n");
	printf("[4.] Izbrisi igrace\n");
	printf("[5.] Pregled svih igraca poredani abecednim redom\n");
	printf("[0.] Izlaz\n");
	printf("Odabir: ");
}

void dodajIgraca(char* datoteka, unsigned int* IGRACNumber) {

	FILE* fp = NULL;

	fp = fopen(datoteka, "rb+");

	if (fp == NULL) {
		perror("Izbornik 1 - dodaj igrace");
		exit(EXIT_FAILURE);
	}
	
	else {
		IGRAC privremeniIgrac = { 0 }; //10
		printf("Ime: \n");
		scanf(" %50[^\n]", privremeniIgrac.Ime); //3
		printf("Prezime: \n");
		scanf(" %50[^\n]", privremeniIgrac.Prezime);
		printf("Broj dresa igraca :\n");
		scanf(" %30[^\n]", privremeniIgrac.brojDresa);
		

		
		

		fseek(fp, sizeof(unsigned int) + ((*IGRACNumber - 1) * sizeof(IGRAC)), SEEK_SET);
		fwrite(&privremeniIgrac, sizeof(IGRAC), 1, fp);
		rewind(fp);
		fwrite(IGRACNumber, sizeof(unsigned int), 1, fp);
		fclose(fp);
	}
}


void ispisiIgrace(char* datoteka, unsigned int* IGRACNumber) {

	FILE* fpRead = NULL;
	fpRead = fopen(datoteka, "rb");

	if (fpRead == NULL) {

		perror("Izbornik 2 - procitaj datoteku");
		exit(EXIT_FAILURE);
	}
	
	else {

		IGRAC* sviIgraci = NULL;

		fread(IGRACNumber, sizeof(unsigned int), 1, fpRead);

		if (*IGRACNumber == 0) {

			printf("Nema unesenih igraca!\n");
			fclose(fpRead);
			return;
		}
		
		else {
			sviIgraci = (IGRAC*)calloc(*IGRACNumber, sizeof(IGRAC)); //13

			if (sviIgraci == NULL) {

				perror("Citanje svih igraca:(");
				exit(EXIT_FAILURE);
			}
			
			else {
				fread(sviIgraci, sizeof(IGRAC), *IGRACNumber, fpRead);
				fclose(fpRead);

				unsigned int i;
				
				for (i = 0; i < *IGRACNumber; i++)
				{
					printf("%u\t", (sviIgraci + i)->brojac);
					printf("\nIme: %s ", (sviIgraci + i)->Ime);
					printf("\nPrezime: %s ", (sviIgraci + i)->Prezime);
					printf("\nBroj dresa: %s ", (sviIgraci + i)->brojDresa);
					
				}
				free(sviIgraci);
			}
		}
	}
}

void pronalazenjeIgraca(char* datoteka, unsigned int* IGRACNumber) {
	FILE* fpSearch = NULL;
	fpSearch = fopen(datoteka, "rb");

	if (fpSearch == NULL) {

		perror("Izbornik 3 - Pretrazi igraca");
		return;

	}

	else {
		IGRAC* sviIgraci = NULL;

		fread(IGRACNumber, sizeof(unsigned int), 1, fpSearch);

		if (*IGRACNumber == 0) {

			printf("Nema unesenih igraca!\n");
			fclose(fpSearch);
			return;
		}
		
		else {
			sviIgraci = (IGRAC*)calloc(*IGRACNumber, sizeof(IGRAC)); //14

			if (sviIgraci == NULL) {

				perror("Citanje svih igraca");
				exit(EXIT_FAILURE);
			}
		
			else {
				fread(sviIgraci, sizeof(IGRAC), *IGRACNumber, fpSearch);
				fclose(fpSearch);
				unsigned int search;
				unsigned int i;
				printf("Pretrazi pomocu imena[1] ili broja dresa[2]?\n");
				scanf("%u", &search);

				
				switch (search) {
				case 1:

					printf("Unesite ime\n");
					char privremenoIme[51] = { '\0' };
					scanf(" %50[^\n]", privremenoIme);
					unsigned int statusIme = 0;
					unsigned int indeksIme = -1;

					
					for (i = 0; i < *IGRACNumber; i++)
					{
						if (!strcmp((sviIgraci + i)->Ime, privremenoIme)) { //21
							statusIme = 1;
							indeksIme = i;
						}
					}

					if (statusIme)
					{
						printf("\nIgrac pronaden!\n");

						printf("Ime: %s\n", (sviIgraci + indeksIme)->Ime);
						printf("Prezime: %s\n", (sviIgraci + indeksIme)->Prezime);
						printf("Broj dresa: %s\n", (sviIgraci + indeksIme)->brojDresa);
						
					}
					else
					{
						printf("Igrac ne postoji!\n");
					}
					break;

				case 2:

					printf("Unesite broj dresa:\n");
					char privremeniBroj[2] = { '\0' };
					scanf("%2s", privremeniBroj);
					unsigned int statusBroj = 0;
					unsigned int indeksBroj = -1;

					
					for (i = 0; i < *IGRACNumber; i++)
					{

						if (!strcmp((sviIgraci + i)->brojDresa, privremeniBroj)) {
							statusBroj = 1;
							indeksBroj = i;
						}
					}

					if (statusBroj)
					{
						printf("\nIgrac pronaden\n");

						printf("Ime: %s\n", (sviIgraci + indeksBroj)->Ime);
						printf("Prezime: %s\n", (sviIgraci + indeksBroj)->Prezime);
						printf("Broj Dresa: %s\n", (sviIgraci + indeksBroj)->brojDresa);
						
					}
					else
					{
						printf("Igrac ne postoji!\n");
					}
					break;

				default: //11
					printf("Nevazeci unos, pokusajte ponovo!\n");
				}
			}
			free(sviIgraci); //15
		}
	}

}

void izlazFunkcija(void) {

	printf("Jeste li sigurni da zelite izaci?(D/N)\n");
	char izbor[2] = { '\0' }; //1
	scanf(" %s", izbor);
	if (!strcmp("D", izbor)) {
		exit(EXIT_FAILURE);
	}
	return;
}



void sortiranjeImena(char* datoteka, unsigned int* IGRACNumber) { //20
	FILE* fpEdit = NULL;
	fpEdit = fopen(datoteka, "rb");

	if (fpEdit == NULL) {

		perror("Izbornik 2 - Citanje datoteke");
		return;

	}
	
	else {
		IGRAC* sviIgraci = NULL;

		fread(IGRACNumber, sizeof(unsigned int), 1, fpEdit);

		if (*IGRACNumber == 0) {

			printf("Nema unesenih igraca!\n");
			fclose(fpEdit);
			return;
		}

		else {
			sviIgraci = (IGRAC*)calloc(*IGRACNumber, sizeof(IGRAC));
			IGRAC temp;
			char prvoSlovo, prvoSlovoPom;
			int min;
			if (sviIgraci == NULL) {
				perror("Citanje svih igraca");
				exit(EXIT_FAILURE);
			}

			else {
				fread(sviIgraci, sizeof(IGRAC), *IGRACNumber, fpEdit);

				for (int i = 0; i < *IGRACNumber - 1; i++)
				{
					min = i;
					prvoSlovo = (sviIgraci + i)->Ime[0] >= 'A' && (sviIgraci + i)->Ime[0] <= 'Z' ? (sviIgraci + i)->Ime[0] : (sviIgraci + i)->Ime[0] - 32;
					for (int j = i + 1; j < *IGRACNumber; j++)
					{
						prvoSlovoPom = (sviIgraci + j)->Ime[0] >= 'A' && (sviIgraci + j)->Ime[0] <= 'Z' ? (sviIgraci + j)->Ime[0] : (sviIgraci + j)->Ime[0] - 32;
						if (prvoSlovo < prvoSlovoPom)
						{
							min = j;
							prvoSlovo = (sviIgraci + j)->Ime[0] >= 'A' && (sviIgraci + j)->Ime[0] <= 'Z' ? (sviIgraci + j)->Ime[0] : (sviIgraci + j)->Ime[0] - 32;
						}
					}
					
					strcpy(temp.Ime, (sviIgraci + i)->Ime);
					strcpy((sviIgraci + i)->Ime, (sviIgraci + min)->Ime);
					strcpy((sviIgraci + min)->Ime, temp.Ime);
					
					strcpy(temp.Prezime, (sviIgraci + i)->Prezime);
					strcpy((sviIgraci + i)->Prezime, (sviIgraci + min)->Prezime);
					strcpy((sviIgraci + min)->Prezime, temp.Prezime);
					
					strcpy(temp.brojDresa, (sviIgraci + i)->brojDresa);
					strcpy((sviIgraci + i)->brojDresa, (sviIgraci + min)->brojDresa);
					strcpy((sviIgraci + min)->brojDresa, temp.brojDresa);
					
				}

				
				for (int i = 0; i < *IGRACNumber; i++)
				{
					printf("%u\t", (sviIgraci + i)->brojac);
					printf("\nIme: %s ", (sviIgraci + i)->Ime);
					printf("\nPrezime: %s ", (sviIgraci + i)->Prezime);
					printf("\nBroj dresa: %s ", (sviIgraci + i)->brojDresa);
					
				}
				free(sviIgraci);
			}
		}
	}
}



void glavniIzbornik(char* datoteka, unsigned int* IGRACNumber) {
	unsigned int izbor = -1;
	static int loop = 1; 
	while (loop) {
		pocetniIzbornik();

		scanf("%u", &izbor);

		switch (izbor) {

		case 1:
			printf("\n\t\tDodaj igraca\n\n");
			dodajIgraca(datoteka, IGRACNumber);
			break;

		case 2:
			printf("\n\t\tPregled svih igraca\n\n");
			ispisiIgrace(datoteka, IGRACNumber);
			break;

		case 3:
			printf("\n\t\tPretrazivanje igraca\n\n");
			pronalazenjeIgraca(datoteka, IGRACNumber);
			break;


		case 4:
			printf("\n\t\tBrisanje svih igraca\n\n");
			printf("Jeste li sigurni da zelite izbrisati sve igrace(D/N)\n");
			char izbor[2] = { '\0' };
			scanf(" %s", izbor);
			if (!strcmp("D", izbor)) {
				remove(datoteka); //18
				printf("Svi igraci su izbrisani, pravljenje nove datoteke!");
				kreiranje(datoteka, IGRACNumber);
			}
			break;

		case 5:
			printf("\n\t\Pregled svih igraca poredano abecedno po imenu\n\n");

			sortiranjeImena(datoteka, IGRACNumber);

			break;
		case 0:
			printf("\nIzlaz...\n\n");
			izlazFunkcija();
			break;

		default:
			printf("Nevazeci unos, pokusajte ponovo!\n");
		}
	}
}
