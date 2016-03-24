<?php include('../auth.php'); ?>
<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Fahrtenbuch") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>
<html>
<head>
<title>Fahrtenbuchausgabe</title>
</head>
<body>
<h1>Fahrtenbuchausgabe komplett</h1>

<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>Nummer</th>";
echo	"<th>K&uuml;rzel</th>";
echo	"<th>Datum</th>";
echo	"<th>Geld</th>";
echo	"<th>Hinfahrt</th>";
echo	"<th>Rückfahrt</th>";
echo	"<th>Bezahlt</th>";
echo "</tr>";
$aus = mysql_query("select * from Fahrtenbuch order by Tag");
$ausnr = mysql_num_rows($aus);
$a = 0;
while($a < $ausnr)
{
$au = mysql_query("select * from Fahrtenbuch order by Tag");
$ausnum = mysql_result($au,$a,0);
$ausku = mysql_result($au,$a,1);
$ausdat = mysql_result($au,$a,2);
$ausge = mysql_result($au,$a,3);
$aushin = mysql_result($au,$a,4);
$ausruck = mysql_result($au,$a,5);
$ausbez = mysql_result($au,$a,6);
echo "<tr>";
echo	"<td>$ausnum</td>";
echo	"<td>$ausku</td>";
echo	"<td>$ausdat</td>";
echo	"<td>$ausge</td>";
echo	"<td>$aushin</td>";
echo	"<td>$ausruck</td>";
echo	"<td>$ausbez</td>";
echo "</tr>";
$a++;
}
echo "</table>";

?>
<a href="haupt.php">Hauptseite</a><br>
<a href="../logout.php">Logout</a>
</body>
</html>
