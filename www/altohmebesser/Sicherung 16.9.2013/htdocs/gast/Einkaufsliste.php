<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Einkaufsliste") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title></title>
</head>
<body>

<h1>Einkaufsliste</h1>



<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>Nummer</th>";
echo	"<th>Name</th>";
echo	"<th>Menge</th>";
echo	"<th>Kaufdatum</th>";
echo	"<th>Priorit&auml;t</th>";
echo	"<th>Quelle</th>";
echo	"<th>Beschreibung</th>";

echo "</tr>";

$aus = mysql_query("select * from Liste");
$ausnr = mysql_num_rows($aus);
$a = 0;

while($a < $ausnr)
{

$ausnum = mysql_result($aus,$a,0);
$ausnam = mysql_result($aus,$a,1);
$ausmeng = mysql_result($aus,$a,2);
$ausdat = mysql_result($aus,$a,3);
$auspri = mysql_result($aus,$a,4);
$ausque = mysql_result($aus,$a,5);
$ausbes = mysql_result($aus,$a,6);

echo "<tr>";
echo	"<td>$ausnum</td>";
echo	"<td>$ausnam</td>";
echo	"<td>$ausmeng</td>";
echo	"<td>$ausdat</td>";
echo	"<td>$auspri</td>";
echo	"<td>$ausque</td>";
echo	"<td>$ausbes</td>";

echo "</tr>";

$a++;
}

echo "</table>";

?>




</body>
</html>