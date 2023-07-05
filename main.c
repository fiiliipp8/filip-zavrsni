#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


int main(void) {

	char* fp = "clanovi.bin"; 
	unsigned int brojIgraca = 0;

	kreiranje(fp, &brojIgraca); 

	glavniIzbornik(fp, &brojIgraca);

	return 0;
}
