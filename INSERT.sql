USE `mydb`;

insert into `mydb`.`status_rezervacije`(naziv) values ("otkazano");
insert into `mydb`.`status_rezervacije`(naziv) values ("odobreno");
insert into `mydb`.`status_rezervacije`(naziv) values ("potvrdjeno");


INSERT INTO `mydb`.`klijent` (`ime`, `prezime`, `email`, `kontakt_telefon`) VALUES ('Sasa', 'Cvetkovic', 'saskko@gmail.com', '');
INSERT INTO `mydb`.`klijent` (`ime`, `prezime`, `email`, `kontakt_telefon`) VALUES ('Nenad', 'Micunovic', 'nenadko@gmail.com', '');


INSERT INTO `mydb`.`firma` (`naziv`, `PIB`, `broj_racuna`, `drzava`, `grad`, `adresa`, `internet_adresa`, `email`, `kontakt_telefon`) VALUES ('FIsko', '3124124141', '4141414141', 'Srbija ', 'Beograd', 'Banijska 124', 'www.blagomeni.com', 'blagomeni@gmail.com', DEFAULT);


INSERT INTO `mydb`.`smestaj` (`naziv`, `drzava`, `grad`, `adresa`, `tip`, `opis`) VALUES (DEFAULT, 'Bele vode', 'Srbija', 'Kovilovo', 'Nedodjija 15', '1', 'Jednokrevetne sobe');


