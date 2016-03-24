<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("philo") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title>Philosophie</title>
</head>
<body>
<h1>Philosophische Texte</h1>
Hier werden die philosophischen Texte ausgegeben.<br>


<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>Nummer</th>";
echo	"<th>Dokumentenname</th>";
echo	"<th>Dokument</th>";
echo "</tr>";
$aus = mysql_query("select * from doku_philo order by pdokunr");
$ausnr = mysql_num_rows($aus);
$a = 0;
while($a < $ausnr)
{
$ausnum = mysql_result($aus,$a,0);
$ausnam = mysql_result($aus,$a,1);
$ausdoc = mysql_result($aus,$a,2);
echo "<tr>";
echo	"<td>$ausnum</td>";
echo	"<td>$ausnam</td>";
echo	"<td>$ausdoc</td>";
echo "</tr>";
$a++;
}
echo "</table>";

?>
<a href="haupt.php">Hauptseite</a>
</body>
</html>
