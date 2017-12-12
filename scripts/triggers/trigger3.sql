USE mydb;

DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER rezervacija_AFTER_INSERT AFTER INSERT on rezervacija
FOR EACH ROW
BEGIN
    UPDATE fizicko_lice fl
    SET fl.broj_registracija = fl.broj_registracija + 1
    WHERE fl.klijent_key_klijent = NEW.fizicko_lice_klijent_key_klijent;
END |
DELIMITER ;