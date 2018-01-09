USE mydb;

DROP TRIGGER IF EXISTS rezervacija_AFTER_DELETE;
DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER rezervacija_AFTER_DELETE AFTER DELETE ON rezervacija 
FOR EACH ROW
BEGIN

  DELETE FROM faktura_rezervacije
  where rezervacija_ponuda_key_ponuda = OLD.ponuda_key_ponuda
  and rezervacija_fizicko_lice_klijent_key_klijent = OLD.fizicko_lice_klijent_key_klijent;

  UPDATE fizicko_lice fl
  SET fl.broj_registracija = fl.broj_registracija - 1
  WHERE fl.klijent_key_klijent = OLD.fizicko_lice_klijent_key_klijent;
  
END|
DELIMITER ;
