<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("philo") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

$wahl = $_POST["wahl"];
$name = $_POST["name"];
$text = $_POST["text"];

if ($wahl == "Philosophie")
	{
	mysql_query("insert into doku_philo(pdokuname,pdoku) values(\"$name\",\"$text\")");
	echo "Eintrag erfolgreich: $name";
	}
if ($wahl == "Gedichte")
	{
	mysql_query("insert into doku_gedichte(gdokuname,gdoku) values(\"$name\",\"$text\")");
	echo "Eintrag erfolgreich: $name";
	}

echo "<br>";
echo "<a href=\"neueseite.php\" target=\"haupt\">Zur&uuml;k</a><br>";
?>