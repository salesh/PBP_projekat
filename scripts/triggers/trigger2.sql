USE mydb;

DROP TRIGGER IF EXISTS rezervacija_AFTER_INSERT;
DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER rezervacija_AFTER_INSERT AFTER INSERT ON rezervacija 
FOR EACH ROW
BEGIN

  insert into faktura_rezervacije 
	(rezervacija_ponuda_key_ponuda,rezervacija_fizicko_lice_klijent_key_klijent,suma)
  values (NEW.ponuda_key_ponuda, NEW.fizicko_lice_klijent_key_klijent, NEW.koliko_soba * (
		select p.cena_sobe
		from ponuda p
		where p.key_ponuda = NEW.ponuda_key_ponuda
		) );

   UPDATE fizicko_lice fl
   SET fl.broj_registracija = fl.broj_registracija + 1
   WHERE fl.klijent_key_klijent = NEW.fizicko_lice_klijent_key_klijent;

END|
DELIMITER ;
