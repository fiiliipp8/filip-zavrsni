#ifndef MYHEADER
#define MYHEADER

typedef struct igrac { 
	unsigned int brojac;
	char Ime[51];
	char Prezime[51];
	char brojDresa[2];
	struct igrac* nextNode;
}IGRAC;

void kreiranje(char* datoteka, unsigned int* pBrojIgraca);
void glavniIzbornik(char* datoteka, unsigned int* BrojIgraca);
void pocetniIzbornik();
void dodajIgraca(char* datoteka, unsigned int* brojIgraca);
void ispisiIgrace(char* datoteka, unsigned int* brojIgraca);
void pronalazenjeIgraca(char* datoteka, unsigned int* brojIgraca);
void uredivanjeIgraca(char* datoteka, unsigned int* brojIgraca);
void sortiranjeImena(char* datoteka, unsigned int* brojIgraca);
void izlazFunkcija(void);

#endif
