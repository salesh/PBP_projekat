-- -----------------------------------------------------
-- Data for table status_rezervacije
-- -----------------------------------------------------

START TRANSACTION;
USE mydb;

insert into status_rezervacije (naziv) values ("otkazana");
insert into status_rezervacije (naziv) values ("odobrena");
insert into status_rezervacije (naziv) values ("potvrdjena");

COMMIT;


-- -----------------------------------------------------
-- Data for table klijent
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO klijent (ime, prezime, email, kontakt_telefon) VALUES ("Sasa", "Cvetkovic", "sasko@gmail.com", "064555444");
INSERT INTO klijent (ime, prezime, email, kontakt_telefon) VALUES ("Nenad", "Micunovic", "nenadko@gmail.com", "064333444");

COMMIT;


-- -----------------------------------------------------
-- Data for table fizicko_lice
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO fizicko_lice (klijent_key_klijent,jmbg, grad, adresa, drzava) VALUES (2, "1414151515123", "Zemun", "Prvomajska 15", " Srbija");

COMMIT;


-- -----------------------------------------------------
-- Data for table firma
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO firma (naziv, PIB, broj_racuna, drzava, grad, adresa, internet_adresa, email, kontakt_telefon) VALUES ("Fisko", "3124124141", "4141414141", "Srbija ", "Beograd", "Banijska 124", "www.blagomeni.com", "blagomeni@gmail.com", "065444333");

COMMIT;


-- -----------------------------------------------------
-- Data for table pravno_lice
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO pravno_lice (klijent_key_klijent, firma_key_firma) VALUES (1, 1);

COMMIT;


-- -----------------------------------------------------
-- Data for table smestaj
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO smestaj (naziv, drzava, grad, adresa, tip, opis) VALUES ("Bele vode", "Srbija", "Kovilovo", "Nedodjija 15", "1", "Jednokrevetne sobe");

COMMIT;


-- -----------------------------------------------------
-- Data for table registracija_smestaja
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO registracija_smestaja (pravno_lice_klijent_key_klijent, smestaj_key_smestaj, datum_registracije) VALUES (1, 1, "10.12.2017");

COMMIT;


-- -----------------------------------------------------
-- Data for table ponuda
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO ponuda (registracija_smestaja_pravno_lice_klijent_key_klijent, registracija_smestaja_smestaj_key_smestaj, tip_sobe, broj_soba, aktivna, cena_sobe, datum_pocetka, datum_zavrsetka) VALUES (1, 1, "1", 5, 1, 150, "12.12.2017", "31.12.2017");

COMMIT;


-- -----------------------------------------------------
-- Data for table rezervacija
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO rezervacija (ponuda_key_ponuda, fizicko_lice_klijent_key_klijent, datum_rezervacije, koliko_soba, tip_soba) VALUES (1, 2,"11.12.2017", 2, "1");

COMMIT;


-- -----------------------------------------------------
-- Data for table faktura_rezervacije
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO faktura_rezervacije (rezervacija_ponuda_key_ponuda, rezervacija_fizicko_lice_klijent_key_klijent) VALUES (1, 2);

COMMIT;


