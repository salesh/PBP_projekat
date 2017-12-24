#ifndef KLIJENT_H
#define KLIJENT_H

#include "main.h"

void registrujNalog(Sql *sql);
void ulogujteSe(Sql *sql);

void idiNaAkcijePravnogLica(Sql *sql, int keyPravnogLica);
void podaciOFirmi(Sql *sql, int keyPravnogLica);
void trenutnePonudeSvihSmestaja(Sql *sql, int keyPravnogLica);
void sviSmestaji(Sql *sql, int keyPravnogLica);
void noviSmestaj(Sql *sql, int keyPravnogLica);
void novaPonuda(Sql *sql, int keyPravnogLica);
void azuzirajPonudu(Sql *sql, int keyPravnogLica);


void idiNaAkcijeFizickogLica(Sql *sql, int keyUlog);
void kreirajPravnoLice(Sql *sql, int kljucK);
void kreirajFizickoLice(Sql *sql, int kljucK);
void azurirajteRezervaciju(Sql *sql, int kljucK);
void podaciONalogu(Sql *sql, int keyUlog);



#endif