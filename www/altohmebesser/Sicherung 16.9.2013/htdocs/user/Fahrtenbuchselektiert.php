<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Fahrtenbuch") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title>Fahrtenbuch selektiert</title>
</head>
<body>
<h1>Fahrtenbuch Auswahl</h1>
Hier werden nur die Fahrtenbucheinträge auf die jeweiliegen Personen bezogen ausgegeben, die noch nicht als bezahlt markiert sind.<br>
<br>

<?php
$kueau = mysql_query("select * from Mitfahrer");
$kuenum = mysql_num_rows($kueau);
$k = 0;
while($k < $kuenum)
{
$kueaus = mysql_result($kueau,$k,1);
$kueausku = mysql_result($kueau,$k,0);
echo	"$kueaus: ";
echo	"<br>";


echo "<table border=1>";
echo "<tr>";
echo	"<th>Datum</th>";
echo	"<th>Geld</th>";
echo	"<th>Hinfahrt</th>";
echo	"<th>Rückfahrt</th>";
echo "</tr>";
$aus = mysql_query("select * from Fahrtenbuch where Bezahlt = 0 AND Mkuerzel = \"$kueausku\" ORDER BY Tag");
$ausnr = mysql_num_rows($aus);
$a = 0;
while($a < $ausnr)
{
$au = mysql_query("select * from Fahrtenbuch where Bezahlt = 0 AND Mkuerzel = \"$kueausku\" ORDER BY Tag");
$ausdat = mysql_result($au,$a,2);
$ausge = mysql_result($au,$a,3);
$aushin = mysql_result($au,$a,4);
$ausruck = mysql_result($au,$a,5);
echo "<tr>";
echo	"<td>$ausdat</td>";
echo	"<td>$ausge</td>";
echo	"<td>$aushin</td>";
echo	"<td>$ausruck</td>";
echo "</tr>";
$a++;
}


echo "</table>";
$k++;
echo	"<br>";
echo	"<hr>";
}
?>

</body>
</html>