#include "ponuda.h"


void dohvatiSvePonude(Sql *sql){
    strcpy(sql->query, "");
    sprintf(sql->query, "select p.key_ponuda as Sifra, s.naziv as Naziv, concat(s.drzava, s.grad, s.adresa) as Lokacija, p.tip_sobe as TipSobe, p.cena_sobe as CenaSoba, p.broj_soba as BrojSoba, p.datum_pocetka as DatumPocetka, p.datum_zavrsetka as DatumZavrsetka from ponuda p join smestaj s on p.registracija_smestaja_smestaj_key_smestaj = s.key_smestaj and p.aktivna = true");

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
    int brojSobaPonuda;
    int cenaSoba;
    int pomOdg = 0;
    char *str = (char *) malloc(100);
    char *strDatumOd = (char *) malloc(100);
    char *strDatumDo = (char *) malloc(100);
    char *strDatumPocetka = (char *) malloc(100);
    char *strDatumZavrsetka = (char *) malloc(100);

    char pomBuff[100];

    printf("\n\n Odaberite sifru ponude \n\n");
    scanf("%d", &keyPonuda);

    strcpy(sql->query, "");
    sprintf(sql->query, "select p.broj_soba, p.cena_sobe, p.datum_pocetka, p.datum_zavrsetka from ponuda p where p.key_ponuda = %i \
                            and not exists ( \
                                select r.ponuda_key_ponuda \
                                from rezervacija r \
                                where r.ponuda_key_ponuda = p.key_ponuda \
                                and r.fizicko_lice_klijent_key_klijent = %i \
                                and r.ponuda_key_ponuda = %i \
                            );", keyPonuda, keyUlog , keyPonuda);
    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        brojSobaPonuda = (int) strtol(sql->row[0],NULL,10);
        cenaSoba = (int) strtol(sql->row[1],NULL,10);
        strcpy(strDatumPocetka, sql->row[2]);
        strcpy(strDatumZavrsetka, sql->row[3]);
    } else {
        printf("\n\n Vec imate rezervaciju za ovu ponudu, ne mozete rezervisati novu\n\n");
        free(strDatumOd);
        free(strDatumDo);
        free(str);
        return;
    }
    mysql_free_result(sql->result);

    printf("\n\n Unesite broj soba koji zelite\n\n");
    scanf("%d", &brojSoba);

    printf("\n\n Unesite redom datum od i datum do\n\n");

    while(1){
        strcpy(sql->query, "");
        sprintf(sql->query,"select p.key_ponuda \
        from ponuda p WHERE key_ponuda=%i and ( ", keyPonuda);
        for(int i = 0; i<2; i++){
            scanf("%ms", &str);
            sprintf(pomBuff, "'%s'", str);
            strcpy(str, pomBuff);
            strcat(sql->query, str);
            if (i == 0) {
                strcpy(strDatumOd, pomBuff);
                strcat(sql->query, " between p.datum_pocetka and p.datum_zavrsetka and ");
            } else {
                strcpy(strDatumDo, pomBuff);
                strcat(sql->query, " between p.datum_pocetka and p.datum_zavrsetka);");
            }
            free(str);
        }
        if(mysql_query(sql->connection, sql->query)){
            printf("%s\n", mysql_error(sql->connection));
            exit(EXIT_FAILURE);
        }

        sql->result = mysql_use_result(sql->connection);
        if(!(sql->row = mysql_fetch_row(sql->result))){
            printf("\n\nPonuda je u okviru %s - %s, unesite ponovo redom datum od i datum do\n\n", strDatumPocetka, strDatumZavrsetka);
            mysql_free_result(sql->result);
        } else {
            mysql_free_result(sql->result);
            break;
        }
    }


    strcpy(sql->query, "");
    sprintf(sql->query,"select r.ponuda_key_ponuda, sum(r.koliko_soba), p.cena_sobe, p.broj_soba \
        from rezervacija r join ponuda p \
        on r.ponuda_key_ponuda = p.key_ponuda \
        where p.key_ponuda = %i and (%s \
        between r.datum_od and r.datum_do or %s \
        between r.datum_od and r.datum_do ) group by r.ponuda_key_ponuda;", keyPonuda, strDatumOd, strDatumDo);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n", mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        brojMogucihSoba = (int) strtol(sql->row[3],NULL,10) - (int) strtol(sql->row[1],NULL,10);
        cenaSoba = (int) strtol(sql->row[2],NULL,10);
    } else {
        brojMogucihSoba = brojSobaPonuda;
    }

    if(brojMogucihSoba == 0){
        printf("\n\nZao nam je sve sobe su nam rezervisane u tom periodu\n\n");
        free(strDatumOd);
        free(strDatumDo);
        return;
    }
    while(brojSoba > brojMogucihSoba){
        printf("\n\nZao mi je nemamo toliko soba za taj vremenski period, imamo %d, izaberite (ili 0 za izlazak)\n\n", brojMogucihSoba);
        scanf("%d", &brojSoba);
        if(brojSoba == 0){
            free(strDatumOd);
            free(strDatumDo);
            return;
        }
    }
    mysql_free_result(sql->result);

    printf("\n\nVasa cena bi bila %d, da li ste sigurni 1 (da), 0 (ne) \n\n", brojSoba * cenaSoba);
    scanf("%d",&pomOdg);

    if(pomOdg == 1){
        strcpy(sql->query, "");
        sprintf(sql->query, "insert into rezervacija (ponuda_key_ponuda, fizicko_lice_klijent_key_klijent,koliko_soba, datum_od, datum_do) values (%i, %i, %i, %s, %s)", keyPonuda, keyUlog, brojSoba, strDatumOd, strDatumDo);
        if(mysql_query(sql->connection, sql->query)){
            printf("%s\n",mysql_error(sql->connection));
            exit(EXIT_FAILURE);
        }
        printf("\n\nUspesno rezervisana ponuda!\n\n");
    } else {
        free(strDatumOd);
        free(strDatumDo);
        return;
    }
}

void trenutneRezervacije(Sql *sql, int keyUlog){
    strcpy(sql->query, "");
    sprintf(sql->query, "select p.key_ponuda as Sifra, r.datum_rezervacije as DatumRezervacija, r.koliko_soba as Soba, fr.suma as UkupnaSuma, \
    concat(r.datum_od,' - ',r.datum_do) as Period, \
    concat(s.naziv,' ', s.drzava, ' ', s.grad, ' ', s.adresa, ' ', p.tip_sobe) \
    as OpisSmestajaIPonude from rezervacija r join ponuda p on r.ponuda_key_ponuda = p.key_ponuda \
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

    printf("\n\nIzaberite sifru rezervacije koju zelite da obriste?\n\n");
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
    int zeliteSoba;

    int ponudaSoba;
    int brojMogucihSoba;
    char *str = (char *) malloc(100);
    char *strDatumOd = (char *) malloc(100);
    char *strDatumDo = (char *) malloc(100);
    char *strDatumPocetka = (char *) malloc(100);
    char *strDatumZavrsetka = (char *) malloc(100);
    char pomBuff[100];

    printf("\n\nIzaberite sifru rezervacije koju zelite da izmenite?\n\n");
    scanf("%d",&keyPonude);

    strcpy(sql->query,"");
    sprintf(sql->query,"select koliko_soba from rezervacija r WHERE ponuda_key_ponuda=%i and r.fizicko_lice_klijent_key_klijent = %i;", keyPonude, keyUlog);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        trenutnoSoba = (int) strtol(sql->row[0],NULL,10);
    }
    mysql_free_result(sql->result);


    printf("\n\nKoliko soba zelite?\n\n");
    scanf("%d",&zeliteSoba);
    if(zeliteSoba == 0 || zeliteSoba == trenutnoSoba){
        printf("Izabrali ste isti broj soba ili 0 soba - prekid");
        return;
    }

    strcpy(sql->query,"");
    sprintf(sql->query,"select broj_soba, datum_pocetka, datum_zavrsetka from ponuda WHERE key_ponuda=%i;", keyPonude);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        ponudaSoba = (int) strtol(sql->row[0],NULL,10);
        strcpy(strDatumPocetka, sql->row[1]);
        strcpy(strDatumZavrsetka, sql->row[2]);
    }
    mysql_free_result(sql->result);

    printf("\n\n Unesite redom novi ili stari datum od i datum do\n\n");

    while(1){
        strcpy(sql->query, "");
        sprintf(sql->query,"select p.key_ponuda \
        from ponuda p WHERE key_ponuda=%i and ( ", keyPonude);
        for(int i = 0; i<2; i++){
            scanf("%ms", &str);
            sprintf(pomBuff, "'%s'", str);
            strcpy(str, pomBuff);
            strcat(sql->query, str);
            if (i == 0) {
                strcpy(strDatumOd, pomBuff);
                strcat(sql->query, " between p.datum_pocetka and p.datum_zavrsetka and ");
            } else {
                strcpy(strDatumDo, pomBuff);
                strcat(sql->query, " between p.datum_pocetka and p.datum_zavrsetka);");
            }
            free(str);
        }
        if(mysql_query(sql->connection, sql->query)){
            printf("%s\n", mysql_error(sql->connection));
            exit(EXIT_FAILURE);
        }

        sql->result = mysql_use_result(sql->connection);
        if(!(sql->row = mysql_fetch_row(sql->result))){
            printf("\n\nPonuda je u okviru %s - %s, unesite ponovo redom datum od i datum do\n\n", strDatumPocetka, strDatumZavrsetka);
            mysql_free_result(sql->result);
        } else {
            mysql_free_result(sql->result);
            break;
        }
    }

    strcpy(sql->query, "");
    sprintf(sql->query,"select r.ponuda_key_ponuda, sum(r.koliko_soba), p.broj_soba \
        from rezervacija r join ponuda p \
        on r.ponuda_key_ponuda = p.key_ponuda \
        where p.key_ponuda = %i and r.fizicko_lice_klijent_key_klijent != %i and (%s \
        between r.datum_od and r.datum_do or %s between r.datum_od and r.datum_do) group by r.ponuda_key_ponuda;", keyPonude, keyUlog, strDatumOd, strDatumDo);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n", mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        brojMogucihSoba = (int) strtol(sql->row[2],NULL,10) - (int) strtol(sql->row[0],NULL,10);
    } else {
        brojMogucihSoba = ponudaSoba;
    }
    while(1){
        if(brojMogucihSoba < zeliteSoba){
                printf("\nTrenutno imate %d, zelite %d a u ponudi zajedno sa vasim trenutnim u zbiru ostaje %d\n", trenutnoSoba, zeliteSoba, brojMogucihSoba);
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
    sprintf(sql->query,"UPDATE rezervacija SET koliko_soba = %d, datum_od = %s, datum_do = %s \
     WHERE ponuda_key_ponuda= %d and fizicko_lice_klijent_key_klijent=%d;", zeliteSoba, strDatumOd , strDatumDo ,keyPonude, keyUlog);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
    printf("\n\nUspesno ste azurirali rezervaciju\n\n");
}
