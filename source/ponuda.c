#include "ponuda.h"


void dohvatiSvePonude(Sql *sql){
    strcpy(sql->query, "");
    sprintf(sql->query, "select p.key_ponuda as Sifra, s.naziv as Naziv, concat(s.drzava, s.grad, s.adresa) as Lokacija, s.opis as Opis, p.cena_sobe as CenaSoba, p.broj_soba as BrojSoba, p.datum_pocetka as DatumPocetka, p.datum_zavrsetka as DatumZavrsetka from ponuda p join smestaj s on p.registracija_smestaja_smestaj_key_smestaj = s.key_smestaj and p.aktivna = true");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count (sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s\t",sql->column[i].name);
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s\t",sql->row[i]);
        }
        printf("\n\n");
    }
    
    mysql_free_result(sql->result);
    printf("\n\n");

}


void rezervacijaPonude(Sql *sql, int keyUlog){
    dohvatiSvePonude(sql);

    int keyPonuda;
    int brojSoba;
    int brojMogucihSoba;
    int cenaSoba;
    int pomOdg = 0;

    printf("\n Odaberite sifru ponude \n");
    scanf("%d", &keyPonuda);

    strcpy(sql->query, "");
    sprintf(sql->query, "select p.broj_soba, p.cena_sobe from ponuda p where p.key_ponuda = %i", keyPonuda);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        brojMogucihSoba = (int) strtol(sql->row[0],NULL,10);
        cenaSoba = (int) strtol(sql->row[1],NULL,10);
    }

    printf("\nKoliko soba zelite? \n");
    scanf("%d", &brojSoba);

    if(brojSoba < 0){
        printf("Negativna vrednost\n\n");
        exit(EXIT_FAILURE);
    }

    while(brojSoba > brojMogucihSoba){
        printf("Zao mi je toliko soba nemamo, imamo %d, izaberite \n\n", brojMogucihSoba);
        scanf("%d", &brojSoba);
    }
    
    printf("Vasa cena bi bila %d, da li ste sigurni 1 (da), 0 (ne) \n\n", brojSoba * cenaSoba);
    scanf("%d",&pomOdg);

    mysql_free_result(sql->result);
    if(pomOdg == 1){
        strcpy(sql->query, "");
        sprintf(sql->query, "insert into rezervacija (ponuda_key_ponuda, fizicko_lice_klijent_key_klijent,koliko_soba) values (%i, %i, %i);", keyPonuda, keyUlog, brojSoba);
        printf("%s\n", sql->query);
        if(mysql_query(sql->connection, sql->query)){
            printf("%s\n",mysql_error(sql->connection));
            exit(EXIT_FAILURE);
        }
        printf("Uspesno rezervisana ponuda!\n\n");
    }
}

void trenutneRezervacije(Sql *sql, int keyUlog){
    strcpy(sql->query, "");
    sprintf(sql->query, "select p.key_ponuda as Sifra, r.datum_rezervacije as DatumRezervacija, r.koliko_soba as Soba, fr.suma as UkupnaSuma, \
    concat(p.datum_pocetka,' - ',p.datum_zavrsetka) as Period, \
    concat(s.naziv,' ',s.naziv, ' ', s.drzava, ' ', s.grad, ' ', s.adresa, ' ', s.opis) \
    as Opis from rezervacija r join ponuda p on r.ponuda_key_ponuda = p.key_ponuda \
    join smestaj s on p.registracija_smestaja_smestaj_key_smestaj = s.key_smestaj \
    join faktura_rezervacije fr on fr.rezervacija_ponuda_key_ponuda = p.key_ponuda \
    and fr.rezervacija_fizicko_lice_klijent_key_klijent = r.fizicko_lice_klijent_key_klijent \
    where r.fizicko_lice_klijent_key_klijent = %i;", keyUlog);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);
    int n = mysql_field_count (sql->connection);

    for(int i = 0; i<n; i++){
        printf("%s\t",sql->column[i].name);
    }

    printf("\n\n");

    while((sql->row = mysql_fetch_row(sql->result))){
        for(int i = 0; i<n; i++){
            printf("%s\t",sql->row[i]);
        }
        printf("\n\n");
    }
    
    mysql_free_result(sql->result);
    printf("\n\n");
}


void brisanjeRezervacije(Sql *sql, int keyUlog){
    trenutneRezervacije(sql,keyUlog);
    int keyPonude;

    printf("\nIzaberite sifru rezervacije koju zelite da obriste?\n");
    scanf("%d",&keyPonude);
    strcpy(sql->query,"");
    sprintf(sql->query,"DELETE FROM rezervacija WHERE ponuda_key_ponuda=%i and fizicko_lice_klijent_key_klijent =%i;", keyPonude, keyUlog);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    printf("\n\n");
    printf("Uspesno obrisana rezervacija");
    printf("\n\n");

}

void azurirajteRezervaciju(Sql *sql, int keyUlog){
    trenutneRezervacije(sql,keyUlog);
    int keyPonude;
    int trenutnoSoba;
    int ostaloSoba;
    int zeliteSoba;

    printf("\nIzaberite sifru rezervacije koju zelite da izmenite?\n");
    scanf("%d",&keyPonude);

    strcpy(sql->query,"");
    sprintf(sql->query,"select koliko_soba from rezervacija WHERE ponuda_key_ponuda=%i;", keyPonude);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        trenutnoSoba = (int) strtol(sql->row[0],NULL,10);
    }
    mysql_free_result(sql->result);


    printf("\nKoliko soba zelite?\n");
    scanf("%d",&zeliteSoba);
    if(zeliteSoba == 0 || zeliteSoba == trenutnoSoba){
        return;
    }

    strcpy(sql->query,"");
    sprintf(sql->query,"select broj_soba from ponuda WHERE key_ponuda=%i;", keyPonude);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        ostaloSoba = (int) strtol(sql->row[0],NULL,10);
        while(1){
            if(ostaloSoba + trenutnoSoba < zeliteSoba){
                    printf("\nTrenutno imate %d, zelite %d a u ponudi je ostalo %d\n", trenutnoSoba, zeliteSoba, ostaloSoba);
                    printf("\nUnesite ponovo broj soba? (0 za odustajanje)\n");
                    scanf("%d",&zeliteSoba);
                    if(zeliteSoba == 0){
                        return;
                    }
            } else {
                   break;
            }
        }
        mysql_free_result(sql->result);
        
        strcpy(sql->query,"");
        sprintf(sql->query,"UPDATE rezervacija SET koliko_soba = %d WHERE ponuda_key_ponuda= %d and fizicko_lice_klijent_key_klijent=%d;", zeliteSoba,keyPonude, keyUlog);

        if(mysql_query(sql->connection, sql->query)){
            printf("%s\n",mysql_error(sql->connection));
            exit(EXIT_FAILURE);
        }

        printf("\nUspesno ste azurirali rezervaciju\n");

    } else {
        printf("\nPonuda nije aktivna, kontaktirajte sluzbu\n");
    }
}
