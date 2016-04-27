<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Fahrtenbuch") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title>Ueberpruefung</title>
</head>
<body>

<?php
$aus = mysql_query("select * from Fahrtenbuch");
$au = mysql_num_rows($aus);
$a = 0;

while($a < $au)
{
if (isset($_POST["los$a"]))
	{
	$ab = $_POST["los$a"];
	mysql_query("update Fahrtenbuch set Bezahlt = true where Nummer = $ab");
	echo "Update erfolgreich: $ab";
	echo "<br>";
	}
if (isset($_POST["losn$a"]))
	{
	$ab = $_POST["losn$a"];
	mysql_query("delete from Fahrtenbuch where Nummer = $ab");
	echo "L&ouml;schen erfolgreich: $ab";
	echo "<br>";
	}

$a++;
}


?>
<a href="Fahrtenbuchupdate.php" target="haupt">Zur&uuml;k</a><br>
</body>
</html>