#ifndef MYHEADER
#define MYHEADER

typedef struct IGRAC { //2 //3
	unsigned int brojac;
	char Ime[51];
	char Prezime[51];
	char brojDresa[2];
	struct igrac* nextNode;
}IGRAC;

void kreiranje(char* datoteka, unsigned int* pBrojIgraca);
void glavniIzbornik(char* datoteka, unsigned int* BrojIgraca);

#endif 
