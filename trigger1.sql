USE `mydb`;

DELIMITER |
CREATE DEFINER = CURRENT_USER TRIGGER `mydb`.`rezervacija_BEFORE_INSERT` BEFORE INSERT ON `rezervacija` FOR EACH ROW
BEGIN
	set NEW.status_key_status_rezervacije = ( select key_status
								  from status_rezervacije
                                  where status ="odobreno");
END |
DELIMITER;
