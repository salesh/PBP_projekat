#include "klijent.h"

void registrujNalog(Sql *sql){
    
    strcpy(sql->query,"");
    printf("\n\n");
    printf("Unesite redom:\n ime\n prezime\n email\n kontakt_telefon\n korisnicko_ime\n lozinka \n");
    printf("\n");
    sprintf(sql->query, "INSERT INTO klijent (ime, prezime, email,kontakt_telefon, korisnicko_ime, lozinka) values(");

    char *str = (char *) malloc(100);
    char pomBuff[100];
    char *pomKI = (char *) malloc(100);
    int kljucKlijenta;
    for(int i=0; i<6; i++){
        scanf("%ms", &str);

        sprintf(pomBuff, "'%s'", str);
        strcpy(str, pomBuff);
        strcat(sql->query, str);

        if(i == 4) {
            strcpy(pomKI,pomBuff);
        }
        if(i!=5){
            strcat(sql->query, ",");
        }
        free(str);
    }
    strcat (sql->query,");");
    
    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    } 

    strcpy(sql->query, "");
    sprintf(sql->query, "select k.key_klijent from klijent k where k.korisnicko_ime = ");
        
    strcat(sql->query, pomKI);
    strcat(sql->query, ";");
    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        kljucKlijenta = (int) strtol(sql->row[0], NULL, 10);
    }
    mysql_free_result(sql->result);
    printf("\n\nUspesno ste kreirali nalog!\n\n");
    printf("%s\n%s\n%s\n","Odaberite: \n",
                "0 - ako ste fizicko lice \n",
               "1 - ako ste pravno lice \n");

    int pomNum;
    scanf("%d", &pomNum);
    if(pomNum == 1){
        kreirajPravnoLice(sql, kljucKlijenta);
    } else if(pomNum == 0) {
        kreirajFizickoLice(sql, kljucKlijenta);
    } else {
        printf("\n\nPogresili ste unos \n\n");
    }
    free(pomKI);
}

void kreirajPravnoLice(Sql* sql, int kljucKlijenta){
    printf("\n\nUnesite redom:\n naziv\n PIB \n broj racuna\n drzava\n grad\n adresa \n internet_adresa \n email \n kontak telefon \n");
    char *str = (char *) malloc(100);
    char pomBuff[100];
    char *pomF = (char *) malloc(100);;
    int kljucFirme;

    strcpy(sql->query, "");
    sprintf(sql->query, "insert into firma (naziv, PIB, broj_racuna,drzava, grad, adresa, internet_adresa, email, kontakt_telefon) values(");
    for(int i = 0; i<9; i++){
        scanf("%ms", &str);
        sprintf(pomBuff, "'%s'", str);
        strcpy(str, pomBuff);
        strcat(sql->query, str);
        if(i == 1){
            strcpy(pomF, pomBuff);
        }
        if(i!=8){
            strcat(sql->query, ",");
        }
        free(str);
    }
    strcat(sql->query,");");

    printf("\n\n%s\n\n", sql->query);
    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    strcpy(sql->query, "");
    sprintf(sql->query, "select f.key_firma from firma f where f.PIB = ");
    strcat(sql->query, pomF);
    strcat(sql->query, ";");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
    
    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        kljucFirme = (int)strtol(sql->row[0],NULL,10);
    }
    mysql_free_result(sql->result);

    strcpy(sql->query, "");
    sprintf(sql->query, "insert into pravno_lice (klijent_key_klijent, firma_key_firma) values (%i, %i);", kljucKlijenta, kljucFirme);
    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
    
    printf("\n\nUspesno ste kreirali firmu i vas pravni nalog\n\n");
    free(pomF);
}

void kreirajFizickoLice(Sql* sql, int kljucK){
    printf("\n\nUnesite redom:\n jmbg\n grad \n adresa\n drzava\n\n");
    char *str = (char *) malloc(100);
    char pomBuff[100];

    strcpy(sql->query, "");
    sprintf(sql->query, "insert into fizicko_lice (klijent_key_klijent, jmbg, grad, adresa, drzava) values(%i",kljucK);
    for(int i = 0; i<5; i++){
        if(i!=0){
          scanf("%ms", &str);
          sprintf(pomBuff, "'%s'", str);
          strcpy(str, pomBuff);
          strcat(sql->query, str);
          free(str);
        }
        if(i!=4){
            strcat(sql->query, ",");
        }
    }
    strcat(sql->query,");");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
    printf("\n\nUspesno popunjeni podaci vaseg naloga\n\n");
}

void ulogujteSe(Sql *sql){
    char *str = (char *) malloc(100);
    char pomBuff[50];
    printf("\nUnesite vase korisnicko ime:\n\n");
    scanf("%ms", &str);

    strcpy(sql->query, "");
    sprintf(sql->query, "select k.ime, k.prezime, k.pravno_lice, k.key_klijent from klijent k where k.korisnicko_ime = ");
   
    sprintf(pomBuff, "'%s'", str);
    strcpy(str, pomBuff);
    strcat(sql->query, str);

    printf("\nUnesite vasu lozinku:\n\n");
    scanf("%ms", &str);
    strcat(sql->query, " and k.lozinka = ");
    
    sprintf(pomBuff, "'%s'", str);
    strcpy(str, pomBuff);
    strcat(sql->query, str);

    free(str);

    if(mysql_query(sql->connection, sql->query) != 0){
      printf("%s\n",mysql_error(sql->connection));
      exit (EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        
        printf("\n\n");
        printf ("Uspesno ste ulogovani %s %s\n", sql->row[0], sql->row[1]);
        int tipUlogovanog =  (int)strtol(sql->row[2], NULL, 10);   
        int keyUlogovanog =  (int)strtol(sql->row[3], NULL, 10);    
        mysql_free_result(sql->result);

        printf("\n\n");
        if(tipUlogovanog){
            idiNaAkcijePravnogLica(sql, keyUlogovanog);
         } else {
            idiNaAkcijeFizickogLica(sql, keyUlogovanog);
        }
        printf("\n\n");

    } else {
        printf("\n\n");
        printf ("Nalog ne postoji!");
        printf("\n\n");
    }
}


void idiNaAkcijePravnogLica(Sql *sql, int keyPravnogLica){
    int stanje = 0;
    while(1){
        printf("%s:\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
            "Izaberite opciju",
            "1.Pogledajte svoje trenutne ponude iz svih smestaja",
            "2.Pogledajte svoje smestaje",  
            "3.Kreirajte novi smestaj", 
            "4.Kreirajte novu ponudu", 
            "5.Azurirajte ponudu",
            "6.Podaci o firmi", 
            "7.Izlogujte se");
        scanf("%d", &stanje);

        switch(stanje){
            case 1:
                trenutnePonudeSvihSmestaja(sql, keyPravnogLica);
            break;
            case 2:
                sviSmestaji(sql, keyPravnogLica);
            break;
            case 3:
                noviSmestaj(sql, keyPravnogLica);
            break;
            case 4:
                novaPonuda(sql, keyPravnogLica);
            break;
            case 5:
                azuzirajPonudu(sql, keyPravnogLica);
            break;
            case 6:
                podaciOFirmi(sql, keyPravnogLica);
            case 7:
                printf("\nUspesno izlogovani!\n");
                return;
            break;
            default:
            printf("\nNiste izabrali nijednu validnu opciju!\n");
        }
    }

}

void idiNaAkcijeFizickogLica(Sql *sql, int keyUlog){
    int stanje = 0;
    while(1){
        printf("%s:\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
            "Izaberite opciju",
            "1.Pogledajte trenutne ponude",
            "2.Rezervisite ponudu", 
            "3.Pogledajte svoje trenutne rezervacije",
            "4.Azurirajte rezervaciju",
            "5.Obrisite rezervaciju",    
            "6.Podaci o nalogu",
            "7.Izlogujte se");
        scanf("%i", &stanje);

        switch(stanje){
            case 1:
                dohvatiSvePonude(sql);
            break;
            case 2:
                rezervacijaPonude(sql, keyUlog);
            break;
            case 3:
                trenutneRezervacije(sql, keyUlog);
            break;
            case 4:
                azurirajteRezervaciju(sql, keyUlog);
            break;
            case 5:
                brisanjeRezervacije(sql, keyUlog);
            break;
            case 6:
                podaciONalogu(sql, keyUlog);
            break;
            case 7:
                printf("\nUspesno izlogovani!\n");
            return;
            default:
            printf("\nNiste izabrali nijednu validnu opciju!\n");
        }
    }
}

void podaciOFirmi(Sql *sql, int keyPravnogLica){
    strcpy(sql->query, "");
    sprintf(sql->query, "select pl.firma_key_firma from pravno_lice pl where pl.klijent_key_klijent=%i", keyPravnogLica);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        int keyFirma = strtol(sql->row[0], NULL, 10);
        strcpy(sql->query, "");
        sprintf(sql->query, "select * from firma f where f.key_firma = %i",  keyFirma);
        mysql_free_result(sql->result);
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

        printf("\n");

        if((sql->row = mysql_fetch_row(sql->result))){
            for(int i = 0; i<n; i++){
                printf("%s\t",sql->row[i]);
            }
        } else {
                 printf("Nije pronadjena firma pravnog lica");
        }
        printf("\n");
    }
    printf("\n");
}

void podaciONalogu(Sql *sql, int keyUlog){
    strcpy(sql->query, "");
    sprintf(sql->query, "select concat(k.ime,' ',k.prezime) as ImePrezime, k.email as Email,\
    k.kontakt_telefon as Telefon, concat(fl.drzava,' ', fl.grad, ' ', fl.adresa) as Lokacija,\
    fl.broj_registracija as BrojRegistracija, fl.jmbg as JMBG \
    from klijent k join fizicko_lice fl on k.key_klijent = fl.klijent_key_klijent\
    where k.key_klijent=%i;", keyUlog);

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

void trenutnePonudeSvihSmestaja(Sql *sql, int keyPravnogLica){

    strcpy(sql->query, "");
    sprintf(sql->query, "select s.key_smestaj as SifraSmestaja, p.key_ponuda as SifraPonude, concat(s.naziv, ' ', s.drzava,' ', s.grad, ' ', s.adresa, ' ', s.opis, ' ', s.univerzalna_sifra) as PodaciSmestaja,\
        rs.datum_registracije as DatumRegistracije,\
        concat(p.broj_soba, ' ', p.cena_sobe,' ', p.datum_pocetka, ' ', p.datum_zavrsetka) as BrojSobaCenaDatumPocetkaDatumZavrsetka\
        from smestaj s join registracija_smestaja rs\
	    on s.key_smestaj = rs.smestaj_key_smestaj\
        join ponuda p on rs.pravno_lice_klijent_key_klijent =  p.registracija_smestaja_pravno_lice_klijent_key_klijent\
        and rs.smestaj_key_smestaj = p.registracija_smestaja_smestaj_key_smestaj where rs.pravno_lice_klijent_key_klijent = %d;", keyPravnogLica);

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


void sviSmestaji(Sql *sql, int keyPravnogLica){
    strcpy(sql->query, "");
    sprintf(sql->query, "select s.key_smestaj as SifraSmestaja, concat(s.naziv, ' ', s.drzava,' ', s.grad, ' ', s.adresa, ' ', s.opis, ' ', s.univerzalna_sifra) as PodaciSmestaja, \
        rs.datum_registracije as DatumRegistracijeSmestaja \
        from smestaj s join registracija_smestaja rs \
	    on s.key_smestaj = rs.smestaj_key_smestaj \
        where rs.pravno_lice_klijent_key_klijent = %d;", keyPravnogLica);


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

void noviSmestaj(Sql *sql, int keyPravnogLica){
    strcpy(sql->query,"");

    printf("Unesite redom:\n naziv\n drzava\n grad\n adresa\n opis\n univerzalna_sifra\n");
    printf("\n\n");
    sprintf(sql->query, "INSERT INTO smestaj (naziv, drzava, grad, adresa, opis, univerzalna_sifra) values(");

    char *str = (char *) malloc(100);
    char pomBuff[100];
    int keySmestaj;
    char *pomKI = (char *) malloc(100);

    for(int i=0; i<6; i++){
        scanf("%ms", &str);
        sprintf(pomBuff, "'%s'", str);

        if(i == 5){
           strcpy(pomKI, pomBuff);
        }
        strcpy(str, pomBuff);
        strcat(sql->query, str);
        if(i!=5){
            strcat(sql->query, ",");
        } 
        free(str);
    }
    strcat (sql->query,");");
    
    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    } 

    strcpy(sql->query, "");
    sprintf(sql->query, "select s.key_smestaj from smestaj s where s.univerzalna_sifra = ");
        
    strcat(sql->query, pomKI);
    strcat(sql->query, ";");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    if((sql->row = mysql_fetch_row(sql->result))){
        keySmestaj = (int) strtol(sql->row[0], NULL, 10);
    }
    mysql_free_result(sql->result);

    strcpy(sql->query, "");
    sprintf(sql->query, "insert into registracija_smestaja (pravno_lice_klijent_key_klijent, smestaj_key_smestaj) values(%i,%i)",keyPravnogLica,keySmestaj);
    printf("\nUspesno ste kreirali smestaj!\n");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }
    printf("\n\n");
    free(pomKI);
}

void azuzirajPonudu(Sql *sql, int keyPravnogLica){
    trenutnePonudeSvihSmestaja(sql,keyPravnogLica);
    
    int keySmestaj;
    int keyPonuda;
    int brSoba;
    int brCena;

    strcpy(sql->query,"");
    printf("\n\nOdaberite u redosledu \n sifru smestaja \n sifru ponude za izmenu\n\n");
    scanf("%d", &keySmestaj);
    scanf("%d", &keyPonuda);

    printf("\n\nUnesite novi broj soba, novu cenu soba\n\n");
    scanf("%d", &brSoba);
    scanf("%d", &brCena);
    printf("\n\n");

    printf("\n\nUkoliko zelite da menjate datum pocetka ili datum zavrsetka obratite se sluzbi\n\n");
    sprintf(sql->query, "update ponuda SET broj_soba = %d, cena_sobe = %d where \
    registracija_smestaja_pravno_lice_klijent_key_klijent = %d and \
    registracija_smestaja_smestaj_key_smestaj = %d and \
    key_ponuda = %d;", brSoba, brCena, keyPravnogLica, keySmestaj, keyPonuda);

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    printf("\n\nUspesno azuirana ponuda\n\n");
}

void novaPonuda(Sql *sql, int keyPravnogLica){

    sviSmestaji(sql, keyPravnogLica);
    int keySmestaj;
    printf("\n\nIzaberite sifru smestaja za kreiranje nove ponudu\n\n");
    scanf("%d", &keySmestaj);

    printf("\n\nUnesite redom:\n broj soba\n cena soba \n datum pocetka\n datum zavrsetka (npr2017-1-19)\n\n");
    char *str = (char *) malloc(100);
    char pomBuff[100];

    strcpy(sql->query, "");
    sprintf(sql->query, "insert into ponuda (registracija_smestaja_pravno_lice_klijent_key_klijent, \
        registracija_smestaja_smestaj_key_smestaj, \
        broj_soba, cena_sobe, datum_pocetka, datum_zavrsetka) values(%d, %d,", keyPravnogLica, keySmestaj);
    for(int i = 0; i<4; i++){
        scanf("%ms", &str);
        sprintf(pomBuff, "'%s'", str);
        strcpy(str, pomBuff);
        strcat(sql->query, str);
        if(i != 3){
            strcat(sql->query, ",");
        }
        free(str);
    }
    strcat(sql->query,");");

    if(mysql_query(sql->connection, sql->query)){
        printf("%s\n",mysql_error(sql->connection));
        exit(EXIT_FAILURE);
    }

    printf("\n\n Uspesno dodata ponuda\n\n");
}