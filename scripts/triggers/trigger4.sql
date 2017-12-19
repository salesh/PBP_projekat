USE mydb;

DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER pravno_lice_AFTER_INSERT AFTER INSERT on pravno_lice
FOR EACH ROW
BEGIN
    UPDATE klijent k
    SET k.pravno_lice = 1
    WHERE k.key_klijent = NEW.klijent_key_klijent;
END |
DELIMITER ;
