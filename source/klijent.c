#include "klijent.h"

void registrujNalog(Sql *sql){

}


void ulogujteSe(Sql *sql){
    char *str, pomBuff[50];
    printf("Unesite vase korisnicko ime:\n");
    scanf("%ms", &str);

    strcpy(sql->query, "");
    sprintf(sql->query, "select k.ime, k.prezime, k.pravno_lice, k.key_klijent from klijent k where k.korisnicko_ime = ");
   
    sprintf(pomBuff, "'%s'", str);
    strcpy(str, pomBuff);
    strcat(sql->query, str);
    
    
    printf("Unesite vasu lozinku:\n");
    scanf("%ms", &str);
    strcat(sql->query, " and k.lozinka = ");
    
    sprintf(pomBuff, "'%s'", str);
    strcpy(str, pomBuff);
    strcat(sql->query, str);
    strcat(sql->query, " ;");

    free(str);

    printf("%s\n", sql->query);

    if(mysql_query(sql->connection, sql->query) != 0){
      printf ("Neuspesno izvrsavanje upita\n");
      exit (EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        printf ("Uspesno ste ulogovani %s %s\n", sql->row[0], sql->row[1]);
        int tipUlogovanog =  (int)strtol(sql->row[2], NULL, 10);   
        int keyUlogovanog =  (int)strtol(sql->row[3], NULL, 10);    
 
        if(tipUlogovanog){
            idiNaAkcijePravnogLica(sql, keyUlogovanog);
         } else {
            idiNaAkcijeFizickogLica(sql, keyUlogovanog);
        }

    } else {
        printf ("Nalog ne postoji!\n");
    }
}


void idiNaAkcijePravnogLica(Sql *sql, int keyPravnogLica){
    int stanje = 0;
    while(1){
        printf("%s:\n%s\n%s\n%s\n%s\n",
            "Izaberite opciju","1.Pogledajte svoje trenutne ponude", "2.Kreirajte novi smestaj", "3.Podaci o firmi", "4. Izlogujte se");
        scanf("%i", &stanje);

        switch(stanje){
            case 1:
            break;
            case 2:
            break;
            case 3:
                 podaciOFirmi(sql, keyPravnogLica);
            case 4:
            break;
            default:
            printf("Niste izabrali nijednu validnu opciju!\n");
        }
    }

}

void idiNaAkcijeFizickogLica(Sql *sql, int keyUlog){
    int stanje = 0;
    while(1){
        printf("%s:\n%s\n%s\n%s\n%s\n",
            "Izaberite opciju","1.Rezervisite novi smestaj", "2.Pogledajte svoje trenutne rezervacije", "3.Podaci o nalogu", "4. Izlogujte se");
        scanf("%i", &stanje);

        switch(stanje){
            case 1:
               // trenutnePonudeFizickogLica(&sql);
            case 2:
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            default:
            printf("Niste izabrali nijednu validnu opciju!\n");
        }
    }
}

void podaciOFirmi(Sql *sql, int keyPravnogLica){
    printf("%i\n", keyPravnogLica);
    strcpy(sql->query, "");
    sprintf(sql->query, "select pl.firma_key_firma from pravno_lice pl where pl.klijent_key_klijent=%i", keyPravnogLica);
    if(mysql_query(sql->connection, sql->query)){
        //printf("Neuspesnoo");
        printf(mysql_error(&(sql->connection)));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        int keyFirma = strtol(sql->row[0], NULL, 10);
        printf("AAAA %i", keyFirma);
        strcpy(sql->query, "");
        sprintf(sql->query, "select naziv, PIB, broj_racuna, drzava, grad, adresa, internet_adresa, email, kontakt_telefon from firma f where f.key_firma = %i",  keyFirma);
        if(mysql_query(sql->connection, sql->query)){
            printf("Neuspesno");
            exit(EXIT_FAILURE);
        }
             sql->result = mysql_use_result(sql->connection);
             if((sql->row = mysql_fetch_row(sql->result))){
                printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", 
                  sql->row[0], sql->row[1], sql->row[2], 
                  sql->row[3], sql->row[4],sql->row[5],
                  sql->row[6], sql->row[7],sql->row[8]);
             } else {
                 printf("Nije pronadjena firma pravnog lica");
             }
    }

}
