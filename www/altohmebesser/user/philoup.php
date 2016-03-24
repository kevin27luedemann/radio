<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("philo") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

$aus = mysql_query("select * from doku_philo");
$au = mysql_num_rows($aus);
$a = 0;

while($a<$au)
{
if (isset($_POST["los$a"]))
	{
	$ab = $_POST["los$a"];
	mysql_query("delete from doku_philo where pdokunr = $ab");
	echo "L&ouml;schen erfolgreich: $ab";
	echo "<br>";
	}


$a++;
}
echo "<a href=\"philo.php\" target=\"haupt\">Zur&uuml;ck</a><br>";
?>
