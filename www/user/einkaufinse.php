<?php include('../auth.php'); ?>
<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Einkaufsliste") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

$name = $_POST["nam"];
$menge = $_POST["menge"];
$datum = $_POST["jahr"] . "." . $_POST["monat"] . "." . $_POST["tag"];
$prio = $_POST["prio"];
$quel = $_POST["quel"];
$bes = $_POST["bes"];

mysql_query("insert into liste(Name,Menge,datum,priori,Quelle,Beschreibung) values('$name','$menge','$datum',$prio,'$quel','$bes')");

echo "Eintrag erfolgreich";
echo "<br>";
echo "<a href=\"Einkaufsliste.php\">Zur&uuml;ck</a><br>";

?>

