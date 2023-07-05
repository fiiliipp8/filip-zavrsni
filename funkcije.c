#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>
#include "Header.h"
#include <string.h>

void kreiranje(char* datoteka, unsigned int* BrojIgraca) { 

	FILE* fp = fopen(datoteka, "rb");

	if (fp == NULL) {

		perror("\nGreska");

		fp = fopen(datoteka, "wb");

		if (fp == NULL) {

			perror("Greska");
			exit(EXIT_FAILURE);
		}
		else {

			fwrite(BrojIgraca, sizeof(unsigned int), 1, fp);
			fclose(fp);
			printf("Pravljenje Datoteke...\nDatoteka usijesno kreirana!\n");
		}
	}
	else {

		fread(BrojIgraca, sizeof(unsigned int), 1, fp);
		fclose(fp);
		
	}
}



void glavniIzbornik(char* datoteka, unsigned int* brojIgraca) {
	unsigned int izbor = -1;
	static int loop = 1; 
	while (loop) {
		pocetniIzbornik();

		scanf("%u", &izbor);

		switch (izbor) {

		case 1:
			printf("\n\t\tDodaj igraca\n\n");
			dodajIgraca(datoteka, brojIgraca);
			break;

		case 2:
			printf("\n\t\tPregled svih igraca\n\n");
			ispisiIgrace(datoteka, brojIgraca);
			break;

		case 3:
			printf("\n\t\tPretrazivanje igraca\n\n");
			pronalazenjeIgraca(datoteka, brojIgraca);
			break;

		case 4:
			printf("\n\t\tUredivanje igraca\n\n");
			uredivanjeIgraca(datoteka, brojIgraca);
			break;

		
		case 5:
			printf("\n\t\Pregled svih igraca poredano abecedno po imenu (Z-A)\n\n");

			sortiranjeImena(datoteka, brojIgraca);

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






void pocetniIzbornik() { 
	printf("\n[ZAPNISNIK NOGOMETNE UTAKMICE]\n");
	printf("Odabir\n");
	printf("1. Dodavanje igraca\n");
	printf("2. Pregled svih igraca u zapisniku\n");
	printf("3. Pretrazivanje igraca\n");
	printf("4. Uredivanje igraca\n");
	printf("5. Sortiranje imena\n");
	printf("0. Izlaz\n");
	printf("Odabir: ");
}

void dodajIgraca(char* datoteka, unsigned int* brojIgraca) {

	FILE* fp = NULL;

	fp = fopen(datoteka, "rb+");

	if (fp == NULL) {
		perror("Greska");
		exit(EXIT_FAILURE);
	}
	
	else {
		IGRAC privremeniIgrac = { 0 };
		printf("Ime: \n");
		scanf(" %50[^\n]", privremeniIgrac.Ime); 
		printf("Prezime: \n");
		scanf(" %50[^\n]", privremeniIgrac.Prezime);
		printf("Broj dresa:\n");
		char privremeniBroj[10] = { '\0' }; 
		scanf("%9s", privremeniBroj);
		strcpy(privremeniIgrac.brojDresa, "");
		strcat(privremeniIgrac.brojDresa, privremeniBroj);
		privremeniIgrac.brojac = (*brojIgraca)++;

		fseek(fp, sizeof(unsigned int) + ((*brojIgraca - 1) * sizeof(IGRAC)), SEEK_SET);
		fwrite(&privremeniIgrac, sizeof(IGRAC), 1, fp);
		rewind(fp);
		fwrite(brojIgraca, sizeof(unsigned int), 1, fp);
		fclose(fp);
	}
}


void ispisiIgrace(char* datoteka, unsigned int* brojIgraca) {

	FILE* fpRead = NULL;
	fpRead = fopen(datoteka, "rb");

	if (fpRead == NULL) {

		perror("Greska");
		exit(EXIT_FAILURE);
	}
	
	else {
		
		IGRAC* sviIgraci = NULL;

		fread(brojIgraca, sizeof(unsigned int), 1, fpRead);

		if (*brojIgraca == 0) {

			printf("Nema unesenih igraca!\n");
			fclose(fpRead);
			return;
		}
		else {
			sviIgraci = (IGRAC*)calloc(*brojIgraca, sizeof(IGRAC)); //13

			if (sviIgraci == NULL) {

				perror("Greska");
				exit(EXIT_FAILURE);
			}
			
			else {
				fread(sviIgraci, sizeof(IGRAC), *brojIgraca, fpRead);
				fclose(fpRead);

				unsigned int i;
				
				for (i = 0; i < *brojIgraca; i++)
				{

					printf("\nIme: %s ", (sviIgraci + i)->Ime);
					printf("\nPrezime: %s ", (sviIgraci + i)->Prezime);
					printf("\nBroj dresa: %s\n", (sviIgraci + i)->brojDresa);

				}
				free(sviIgraci);
			}
		}
	}
}

void pronalazenjeIgraca(char* datoteka, unsigned int* brojIgraca) {
	FILE* fpSearch = NULL;
	fpSearch = fopen(datoteka, "rb");

	if (fpSearch == NULL) {

		perror("Greska");
		return;

	}
	
	else {
		IGRAC* sviIgraci = NULL;

		fread(brojIgraca, sizeof(unsigned int), 1, fpSearch);

		if (*brojIgraca == 0) {

			printf("Nema unesenih Igraca!\n");
			fclose(fpSearch);
			return;
		}
		
		else {
			sviIgraci = (IGRAC*)calloc(*brojIgraca, sizeof(IGRAC)); 

			if (sviIgraci == NULL) {

				perror("Greska");
				exit(EXIT_FAILURE);
			}
			
			else {
				fread(sviIgraci, sizeof(IGRAC), *brojIgraca, fpSearch);
				fclose(fpSearch);
				unsigned int search;
				unsigned int i;
				printf("Pretrazi pomocu imena[1] ili broja dresa[2]?\n");
				do {
					scanf("%u", &search);
					if (search != 1 && search != 2)
					{
						printf("Unesite [1] ili [2]!\n");
					}
				} while (search != 1 && search != 2);


				
				switch (search) {
				case 1:

					printf("Unesite ime\n");
					char privremenoIme[51] = { '\0' };
					scanf(" %50[^\n]", privremenoIme);
					unsigned int statusIme = 0;
					unsigned int indeksIme = -1;

					
					for (i = 0; i < *brojIgraca; i++)
					{
						if (!strcmp((sviIgraci + i)->Ime, privremenoIme)) {
							statusIme = 1;
							indeksIme = i;
						}
					}

					if (statusIme)
					{
						printf("\nIgrac pronaden!\n");

						printf("Ime: %s\n", (sviIgraci + indeksIme)->Ime);
						printf("Prezime: %s\n", (sviIgraci + indeksIme)->Prezime);
						printf("Broj dresa: %s\n\n", (sviIgraci + indeksIme)->brojDresa);
					}
					else
					{
						printf("Igrac nije u bazi podataka\n");
					}
					break;

				case 2:

					printf("Unesite broj dresa:\n");
					char privremeniBroj[2] = { '\0' };
					scanf("%14s", privremeniBroj);
					unsigned int statusBroj = 0;
					unsigned int indeksBroj = -1;

					
					for (i = 0; i < *brojIgraca; i++)
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
						printf("Broj dresa: %s\n\n", (sviIgraci + indeksBroj)->brojDresa);
					}
					else
					{
						printf("Igrac nije u bazi podataka\n");
					}
					break;

				default:
					printf("Nevazeci unos, pokusajte ponovo!\n");
				}
			}
			free(sviIgraci); 
		}
	}

}




void uredivanjeIgraca(char* datoteka, unsigned int* brojIgraca) {

	FILE* fpEdit = NULL;
	fpEdit = fopen(datoteka, "rb");

	if (fpEdit == NULL) {

		perror("Greska");
		return;

	}
	
	else {
		IGRAC* sviIgraci = NULL;

		fread(brojIgraca, sizeof(unsigned int), 1, fpEdit);

		if (*brojIgraca == 0) {

			printf("Nema unesenih igraca!\n");
			fclose(fpEdit);
			return;
		}
		
		else {
			sviIgraci = (IGRAC*)calloc(*brojIgraca, sizeof(IGRAC));

			if (sviIgraci == NULL) {
				perror("Greska");
				exit(EXIT_FAILURE);
			}
			
			else {
				IGRAC privremeniIgrac = { 0 };
				fread(sviIgraci, sizeof(IGRAC), *brojIgraca, fpEdit);

				unsigned int i;

				printf("Unesite ime igraca:\n");
				char privremenoIme[51] = { '\0' };
				scanf(" %50[^\n]", privremenoIme);
				unsigned int statusIme = 0;
				unsigned int indeksIme = -1;

				
				for (i = 0; i < *brojIgraca; i++)
				{
					if (!strcmp((sviIgraci + i)->Ime, privremenoIme)) {
						statusIme = 1;
						indeksIme = i;
					}
				}

				if (statusIme == 1) {
					printf("\nIgrac pronaden\n");

					printf("Ime: %s\n", (sviIgraci + indeksIme)->Ime);
					printf("Prezime: %s\n", (sviIgraci + indeksIme)->Prezime);
					printf("Broj dresa: %s\n\n", (sviIgraci + indeksIme)->brojDresa);
					fclose(fpEdit);
					fpEdit = fopen(datoteka, "rb+");
					printf("Novo ime: \n");
					scanf(" %50[^\n]", privremeniIgrac.Ime);
					printf("Novo prezime: \n");
					scanf(" %50[^\n]", privremeniIgrac.Prezime);
					printf("Novi broj dresa: \n");
					scanf(" %50[^\n]", privremeniIgrac.brojDresa);
					
					

					fseek(fpEdit, sizeof(unsigned int) + ((indeksIme) * sizeof(IGRAC)), SEEK_SET); 
					fwrite(&privremeniIgrac, sizeof(IGRAC), 1, fpEdit);
					rewind(fpEdit);
					fwrite(brojIgraca, sizeof(unsigned int), 1, fpEdit);
					fclose(fpEdit);
				}
				else {
					printf("Igrac nije u bazi podataka\n");
				}
				free(sviIgraci);
			}
		}
	}
	fclose(fpEdit);
}

void sortiranjeImena(char* datoteka, unsigned int* brojIgraca) { 
	FILE* fpEdit = NULL;
	fpEdit = fopen(datoteka, "rb");

	if (fpEdit == NULL) {

		perror("Izbornik 2 - Citanje datoteke");
		return;

	}

	else {
		IGRAC* sviIgraci = NULL;

		fread(brojIgraca, sizeof(unsigned int), 1, fpEdit);

		if (*brojIgraca == 0) {

			printf("Nema unesenih igraca!\n");
			fclose(fpEdit);
			return;
		}

		else {
			sviIgraci = (IGRAC*)calloc(*brojIgraca, sizeof(IGRAC));
			IGRAC temp;
			char prvoSlovo, prvoSlovoPom;
			int min;
			if (sviIgraci == NULL) {
				perror("Citanje svih igraca");
				exit(EXIT_FAILURE);
			}

			else {
				fread(sviIgraci, sizeof(IGRAC), *brojIgraca, fpEdit);

				for (int i = 0; i < *brojIgraca - 1; i++)
				{
					min = i;
					prvoSlovo = (sviIgraci + i)->Ime[0] >= 'A' && (sviIgraci + i)->Ime[0] <= 'Z' ? (sviIgraci + i)->Ime[0] : (sviIgraci + i)->Ime[0] - 32;
					for (int j = i + 1; j < *brojIgraca; j++)
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


				for (int i = 0; i < *brojIgraca; i++)
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


void izlazFunkcija(void) {

	printf("Jeste li sigurni da zelite izaci?(D/N)\n");
	char izbor[2] = { '\0' }; 
	scanf(" %s", izbor);
	if (!strcmp("D", izbor)) {
		exit(EXIT_FAILURE);
	}
	return;
}
