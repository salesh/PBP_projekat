USE mydb;

DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER rezervacija_BEFORE_INSERT BEFORE INSERT ON rezervacija FOR EACH ROW
BEGIN
	set NEW.status_rezervacije_key_status_rezervacije = ( select key_status_rezervacije
								  						  from status_rezervacije
                                  						  where naziv ="odobrena");
END |
DELIMITER ;
