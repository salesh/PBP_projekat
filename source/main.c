#include "main.h"
#include "ponuda.h"

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
            "Izaberite opciju","1. Registracija naloga", "2. Ulogujte se", "3. Pogledajte trenutne ponude", "4. Napustite sajt");
        scanf("%i", &stanje);

        switch(stanje){
            case 1:
            break;
            case 2:
            break;
            case 3:
                dohvatiSvePonude(&sql);
            break;
            default:
            printf("Niste izabrali nijednu validnu opciju!\n");
        }
    }
    return 0;
}