<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("budget") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");
?>

<html>
<head>
<title></title>
</head>
<body>
<h1>Budget</h1>
Einkommen: <br>
<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>Name</th>";
echo	"<th>Menge</th>";
echo	"<th>Quelle</th>";
echo	"<th>Beschreibung</th>";
echo "</tr>";

$aus = mysql_query("select * from einkommen");
$ausnr = mysql_num_rows($aus);
$a = 0;
$sumein=0;
while($a < $ausnr)
{

$ausnam = mysql_result($aus,$a,1);
$ausmeng = mysql_result($aus,$a,2);
$ausque = mysql_result($aus,$a,3);
$ausbes = mysql_result($aus,$a,4);

echo "<tr>";
echo	"<td>$ausnam</td>";
echo	"<td>$ausmeng</td>";
echo	"<td>$ausque</td>";
echo	"<td>$ausbes</td>";
echo "</tr>";
$sumein+=$ausmeng;
$a++;
}
echo "</table>";
echo "Summe: $sumein <br>";
?>

<br>
Lister der L&auml;den:<br>

<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>Name</th>";
echo	"<th>Adresse</th>";
echo	"<th>Bio</th>";
echo	"<th>Beschreibung</th>";
echo "</tr>";

$aus = mysql_query("select * from laden");
$ausnr = mysql_num_rows($aus);
$a = 0;
while($a < $ausnr)
{

$ausnam = mysql_result($aus,$a,1);
$ausadres = mysql_result($aus,$a,2);
$ausbio = mysql_result($aus,$a,3);
$ausbes = mysql_result($aus,$a,4);

echo "<tr>";
echo	"<td>$ausnam</td>";
echo	"<td>$ausadres</td>";
echo	"<td>$ausbio</td>";
echo	"<td>$ausbes</td>";
echo "</tr>";
$a++;
}
echo "</table>";
?>

<br>
Liste der Artikel: <br>

<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>Name</th>";
echo	"<th>Ort</th>";
echo	"<th>Preis</th>";
echo	"<th>Barcode</th>";
echo	"<th>Beschreibung</th>";
echo "</tr>";

$aus = mysql_query("select * from artikel");
$ausnr = mysql_num_rows($aus);
$a = 0;
while($a < $ausnr)
{

$ausnam = mysql_result($aus,$a,1);
$ausbarc = mysql_result($aus,$a,2);
$auspreis = mysql_result($aus,$a,3);
$ausbes = mysql_result($aus,$a,4);
$ausort = mysql_result($aus,$a,5);

echo "<tr>";
echo	"<td>$ausnam</td>";
echo	"<td>$ausort</td>";
echo	"<td>$auspreis</td>";
echo	"<td>$ausbarc</td>";
echo	"<td>$ausbes</td>";
echo "</tr>";
$a++;
}
echo "</table>";
?>

<br>
Liste der Ausgaben: <br>

<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>Name</th>";
echo	"<th>Ort</th>";
echo	"<th>Datum</th>";
echo	"<th>Menge</th>";
echo "</tr>";

$aus = mysql_query("select c.name, b.name, a.datum, a.menge from ausgaben a, artikel b, laden c where a.ort = c.nummer AND a.name=b.nummer");
$ausnr = mysql_num_rows($aus);
$a = 0;
while($a < $ausnr)
{

$ausnam = mysql_result($aus,$a,1);
$ausmeng = mysql_result($aus,$a,3);
$ausdat = mysql_result($aus,$a,2);
$ausort = mysql_result($aus,$a,0);

echo "<tr>";
echo	"<td>$ausnam</td>";
echo	"<td>$ausort</td>";
echo	"<td>$ausdat</td>";
echo	"<td>$ausmeng</td>";
echo "</tr>";
$a++;
}
echo "</table>";
?>


</body>
</html>
