USE mydb;

DROP TRIGGER IF EXISTS rezervacija_AFTER_UPDATE;
DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER rezervacija_AFTER_UPDATE AFTER UPDATE ON rezervacija 
FOR EACH ROW
BEGIN
  update faktura_rezervacije
  set suma = NEW.koliko_soba * (
		select p.cena_sobe
		from ponuda p
		where p.key_ponuda = NEW.ponuda_key_ponuda
		)
  where rezervacija_ponuda_key_ponuda = NEW.ponuda_key_ponuda
  and rezervacija_fizicko_lice_klijent_key_klijent = NEW.fizicko_lice_klijent_key_klijent;

  update ponuda
  set broj_soba = (
		 case when NEW.koliko_soba > OLD.koliko_soba THEN broj_soba - (NEW.koliko_soba - OLD.koliko_soba)
			ELSE broj_soba + (OLD.koliko_soba - NEW.koliko_soba)
         end
		)
  where key_ponuda = NEW.ponuda_key_ponuda;
END|
DELIMITER ;
