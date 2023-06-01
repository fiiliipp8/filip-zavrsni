#pragma once
#ifndef HEADER_H
#define HEADER_H

typedef struct igrac {

	char ime[20];
	char prezime[20];
	int broj;

}IGRAC;

void ispis_izbornika();
void igraci_domace();
void igraci_gostujuce();
void ispisi_igrace();
void izbrisi_igraca();


#endif
