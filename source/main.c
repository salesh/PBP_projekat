#include "main.h"
#include "ponuda.h"
#include "klijent.h"

int main(){
    Sql sql;
    sql.connection = mysql_init(NULL);
    
    if(mysql_real_connect(sql.connection,"localhost", "root", "root", "mydb",0, NULL, 0) == NULL){
        printf("Failed to connect to database\n");
    } else {
        printf("Dobrodosli na Booking.com\n");
    }

    int stanje = 0;

    while(1){
        printf("%s:\n%s\n%s\n%s\n%s\n",
            "Izaberite opciju","1. Registracija naloga", "2. Ulogujte se", "3. Pogledajte trenutne ponude", "4. Napustite program");
        scanf("%i", &stanje);

        switch(stanje){
            case 1:
                registrujNalog(&sql);
            break;
            case 2:
               ulogujteSe(&sql);
            break;
            case 3:
                dohvatiSvePonude(&sql);
            break;
            case 4:
                exit(EXIT_SUCCESS);
            default:
            printf("Niste izabrali nijednu validnu opciju!\n");
        }
    }
    return 0;
}