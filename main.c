#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "Header.h"


int main(void) {

	char* fp = "clanovi.bin"; //16
	unsigned int IGRACNumber = 0;

	kreiranje(fp, &IGRACNumber); //10

	glavniIzbornik(fp, &IGRACNumber);

	return 0;
}
