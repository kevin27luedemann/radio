<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Einkaufsliste") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

$name = $_POST["nam"];
$menge = $_POST["menge"];
$datum = $_POST["jahr"] . "." . $_POST["monat"] . "." . $_POST["tag"];
$prio = $_POST["prio"];
$quel = $_POST["quel"];
$bes = $_POST["bes"];

mysql_query("insert into Liste(Name,Menge,datum,priori,Quelle,Beschreibung) values('$name','$menge','$datum',$prio,'$quel','$bes')");

echo "Eintrag erfolgreich";
echo "<br>";
echo "<a href=\"Einkaufsliste.php\" target=\"haupt\">Zur&uuml;ck</a><br>";

?>

