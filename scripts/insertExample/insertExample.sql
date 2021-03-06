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
INSERT INTO klijent (ime, prezime, email, kontakt_telefon, korisnicko_ime, lozinka) VALUES ("Sasa", "Cvetkovic", "sasko@gmail.com", "064555444", "root", "root");
INSERT INTO klijent (ime, prezime, email, kontakt_telefon, korisnicko_ime, lozinka) VALUES ("Nenad", "Micunovic", "nenadko@gmail.com", "064333444", "roott", "roott");
INSERT INTO klijent (ime, prezime, email, kontakt_telefon, korisnicko_ime, lozinka) VALUES ("Mrki", "Mrki", "nenadko@Mrki.com", "064333444", "mrki", "mrki");
COMMIT;


-- -----------------------------------------------------
-- Data for table fizicko_lice
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO fizicko_lice (klijent_key_klijent,jmbg, grad, adresa, drzava) VALUES (2, "1414151515123", "Zemun", "Prvomajska 15", " Srbija");
INSERT INTO fizicko_lice (klijent_key_klijent,jmbg, grad, adresa, drzava) VALUES (3, "414124", "Zemun", "Prvomajska 14", " Srbija");

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
INSERT INTO smestaj (naziv, drzava, grad, adresa,univerzalna_sifra) VALUES ("Bele vode", "Srbija", "Kovilovo", "Nedodjija 15", "1");
INSERT INTO smestaj (naziv, drzava, grad, adresa,univerzalna_sifra) VALUES ("Crne vode", "Austrija", "Bec", "Dodjija 51", "2");
COMMIT;


-- -----------------------------------------------------
-- Data for table registracija_smestaja
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO registracija_smestaja (pravno_lice_klijent_key_klijent, smestaj_key_smestaj) VALUES (1, 1);
INSERT INTO registracija_smestaja (pravno_lice_klijent_key_klijent, smestaj_key_smestaj) VALUES (1, 2);
COMMIT;


-- -----------------------------------------------------
-- Data for table ponuda
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO ponuda (registracija_smestaja_pravno_lice_klijent_key_klijent, registracija_smestaja_smestaj_key_smestaj, broj_soba, aktivna, cena_sobe, datum_pocetka, datum_zavrsetka, tip_sobe) VALUES (1, 1, 5, 1, 150, "2017-12-10", "2017-12-31", "jednokrevetna");

INSERT INTO ponuda (registracija_smestaja_pravno_lice_klijent_key_klijent, registracija_smestaja_smestaj_key_smestaj, broj_soba, aktivna, cena_sobe, datum_pocetka, datum_zavrsetka, tip_sobe) VALUES (1, 2, 5, 1, 200, "2017-11-12", "2017-11-30", "dvokrevetna");

COMMIT;


-- -----------------------------------------------------
-- Data for table rezervacija
-- -----------------------------------------------------
START TRANSACTION;
USE mydb;
INSERT INTO rezervacija (ponuda_key_ponuda, fizicko_lice_klijent_key_klijent, koliko_soba,datum_od, datum_do) VALUES (1, 2, 1, "2017-12-12", "2017-12-22");

INSERT INTO rezervacija (ponuda_key_ponuda, fizicko_lice_klijent_key_klijent, koliko_soba,datum_od, datum_do) VALUES (1, 3, 2, "2017-12-23", "2017-12-30");
COMMIT;


