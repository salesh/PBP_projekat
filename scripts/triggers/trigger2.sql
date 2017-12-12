USE mydb;

DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER faktura_rezervacije_BEFORE_INSERT BEFORE INSERT ON faktura_rezervacije FOR EACH ROW
BEGIN
  SET NEW.suma = ( 
		select r.koliko_soba
		from rezervacija r
		where r.ponuda_key_ponuda = NEW.rezervacija_ponuda_key_ponuda
		and r.fizicko_lice_klijent_key_klijent = NEW.rezervacija_fizicko_lice_klijent_key_klijent
	) * (
		select p.cena_sobe
		from ponuda p
		where p.key_ponuda = NEW.rezervacija_ponuda_key_ponuda
		);
END|
DELIMITER ;
