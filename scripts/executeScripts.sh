#!/bin/sh

USER="root"
PASS="-proot"
DATABASE_NAME="mydb"

#Create database

mysql -u $USER $PASS < ./createDatabase.sql

echo "Created database"

#Create triggers

mysql -u $USER $PASS < ./triggers/trigger1.sql
mysql -u $USER $PASS < ./triggers/trigger2.sql

echo "Created triggers"

#Insert example

mysql -u $USER $PASS < ./insertExample/insertExample.sql

echo "Exampled inserted"
