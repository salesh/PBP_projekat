#ifndef PONUDA_H
#define PONUDA_H

#include "main.h"


void dohvatiSvePonude(Sql *sql);
void rezervacijaPonude(Sql *sql, int keyUlog);
void trenutneRezervacije(Sql *sql, int keyUlog);
void brisanjeRezervacije(Sql *sql, int keyUlog);

#endif