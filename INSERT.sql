USE `mydb`;

insert into `mydb`.`status_rezervacije`(naziv) values ("otkazano");
insert into `mydb`.`status_rezervacije`(naziv) values ("odobreno");
insert into `mydb`.`status_rezervacije`(naziv) values ("potvrdjeno");


-- -----------------------------------------------------
-- Data for table `mydb`.`klijent`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`klijent` (`ime`, `prezime`, `email`, `kontakt_telefon`) VALUES ('Sasa', 'Cvetkovic', 'sasko@gmail.com', '11242494');
INSERT INTO `mydb`.`klijent` (`ime`, `prezime`, `email`, `kontakt_telefon`) VALUES ('Nenad', 'Micunovic', 'nenadko@gmail.com', '');

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`fizicko_lice`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`fizicko_lice` (`klijent_key_klijent`,`jmbg`, `grad`, `adresa`, `drzava`, `broj_registracija`) VALUES (2, '14141515151', 'Zemun', 'Prvomajska 15', ' Srbija', 0);

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`firma`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`firma` (`naziv`, `PIB`, `broj_racuna`, `drzava`, `grad`, `adresa`, `internet_adresa`, `email`, `kontakt_telefon`) VALUES ('FIsko', '3124124141', '4141414141', 'Srbija ', 'Beograd', 'Banijska 124', 'www.blagomeni.com', 'blagomeni@gmail.com', DEFAULT);

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`pravno_lice`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`pravno_lice` (`klijent_key_klijent`, `firma_key_firma`) VALUES (1, 1);

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`smestaj`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`smestaj` (`naziv`, `drzava`, `grad`, `adresa`, `tip`, `opis`) VALUES ('Bele vode', 'Srbija', 'Kovilovo', 'Nedodjija 15', '1', 'Jednokrevetne sobe');

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`registracija_smestaja`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`registracija_smestaja` (`pravno_lice_klijent_key_klijent`, `smestaj_key_smestaj`, `datum_registracije`) VALUES (1, 1, '10.12.2017');

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`ponuda`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`ponuda` (`registracija_smestaja_pravno_lice_klijent_key_klijent`, `registracija_smestaja_smestaj_key_smestaj`, `tip_sobe`, `broj_soba`, `aktivna`, `cena_sobe`, `datum_pocetka`, `datum_zavrsetka`) VALUES (1, 1, '1', 5, 1, 150, '12.12.2017', '31.12.2017');

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`rezervacija`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`rezervacija` (`ponuda_key_ponuda`, `fizicko_lice_klijent_key_klijent`, `status_rezervacije_key_status_rezervacije`, `datum_rezervacije`, `koliko_soba`, `tip_soba`) VALUES (1, 2, , '11.12.2017', 2, '1');

COMMIT;


-- -----------------------------------------------------
-- Data for table `mydb`.`faktura_rezervacije`
-- -----------------------------------------------------
START TRANSACTION;
USE `mydb`;
INSERT INTO `mydb`.`faktura_rezervacije` (`rezervacija_ponuda_key_ponuda`, `rezervacija_fizicko_lice_klijent_key_klijent`, `suma`, `placena_faktura`) VALUES (1, 1, , );

COMMIT;


