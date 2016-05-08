<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Fahrtenbuch") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title></title>
</head>
<body>
<?php
$kuerzel = $_POST["kuerzel"];
$vorname = $_POST["vorname"];
$name = $_POST["name"];
$tel = $_POST["tel"];
$str = $_POST["str"];
$haus = $_POST["haus"];
$ort = $_POST["ort"];
$plz = $_POST["plz"];
mysql_query("insert into Mitfahrer() values('$kuerzel','$vorname','$name','$tel','$str','$haus','$ort',$plz)");
echo "Eintrag erfolgreich";
?>
<br>
<a href="Mitfahrerupdate.php" target="haupt">Zur&uuml;k</a><br>
</body>
</html>