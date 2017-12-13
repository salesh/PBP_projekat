#include "ponuda.h"


void dohvatiSvePonude(Sql *sql){
    sprintf(sql->query, "select s.naziv as Naziv, concat(s.drzava, s.grad, s.adresa) as Lokacija, s.opis as Opis, p.cena_sobe as CenaSoba, p.broj_soba as BrojSoba, p.datum_pocetka as DatumPocetka, p.datum_zavrsetka as DatumZavrsetka from ponuda p join smestaj s on p.registracija_smestaja_smestaj_key_smestaj = s.key_smestaj");
    printf("%s\n", sql->query);

    if(mysql_query(sql->connection, sql->query)){
        printf("Neuspesno");
        exit(EXIT_FAILURE);
    }

    sql->result = mysql_use_result(sql->connection);
    sql->column = mysql_fetch_fields(sql->result);

    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", 
    sql->column[0].name, sql->column[1].name, sql->column[2].name, 
    sql->column[3].name, sql->column[4].name, sql->column[5].name,
    sql->column[6].name);

    while((sql->row = mysql_fetch_row(sql->result))){
        printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", 
            sql->row[0], sql->row[1], sql->row[2], 
            sql->row[3], sql->row[4], sql->row[5],
            sql->row[6]);
    }
}