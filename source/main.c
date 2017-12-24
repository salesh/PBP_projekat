#include "main.h"
#include "ponuda.h"
#include "klijent.h"

int main(){
    Sql sql;
    sql.connection = mysql_init(NULL);
    
    if(mysql_real_connect(sql.connection,"localhost", "root", "root", "mydb",0, NULL, 0) == NULL){
        printf("Failed to connect to database\n\n");
        printf("%s\n",mysql_error(sql.connection));
    } else {
        printf("\nDobrodosli na Booking.com\n\n");
    }

    int stanje = 0;

    while(1){
        printf("%s:\n%s\n%s\n%s\n%s\n\n",
            "Izaberite opciju",
            "1. Registracija naloga", 
            "2. Ulogujte se", 
            "3. Pogledajte trenutne ponude", 
            "4. Napustite program");
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
                printf("\nNiste izabrali nijednu validnu opciju!\n");
        }
    }
    mysql_close(sql.connection);
    return 0;
}