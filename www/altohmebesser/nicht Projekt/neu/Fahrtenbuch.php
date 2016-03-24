<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Fahrtenbuch") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

$kuerzel = $_POST["kuerzel"];
$datum = $_POST["jahr"] . "." . $_POST["monat"] . "." . $_POST["tag"];
$sonder = $_POST["sonder"];
$hin = $_POST["hin"];
$rueck = $_POST["rueck"];
$bezahlt = $_POST["bezahlt"];

if ($hin == "Hinfahrt")
	{
	$hinja = 1;
	}
else 
	{
	$hinja = 0;
	}
if ($rueck == "Rueckfahrt")
	{
	$rueckja = 1;
	}
else
	{
	$rueckja = 0;
	}
if ($bezahlt == "bezahlt")
	{
	$bezahltja = "true";
	}
else
	{
	$bezahltja = "false";
	}
?>

<html>
<head>
<title>Fahrtenbuch</title>
</head>
<body>
<h1>Fahrtenbucheintragungen</h1>
Mit diesem Interface werden Eintr&auml;ge in das Fahrtenbuch geschrieben.<br><br>
<form action="index.php" method=post>

K&uuml;rzel: 
<select name="kuerzel" size=3>
<option> Tl
<option> Ma
<option> Di
</select><br>

Datum: 
<select name="tag">
<option> 1
<option> 2
<option> 3
<option> 4
<option> 5
<option> 6
<option> 7
<option> 8
<option> 9
<option> 10
<option> 11
<option> 12
<option> 13
<option> 14
<option> 15
<option> 16
<option> 17
<option> 18
<option> 19
<option> 20
<option> 21
<option> 22
<option> 23
<option> 24
<option> 25
<option> 26
<option> 27
<option> 28
<option> 29
<option> 30
<option> 31
</select>

<select name="monat">
<option> 1
<option> 2
<option> 3
<option> 4
<option> 5
<option> 6
<option> 7
<option> 8
<option> 9
<option> 10
<option> 11
<option> 12
</select>

<select name="jahr">
<option> 2011
<option> 2012
<option> 2013
<option> 2014
<option> 2015
</select><br>

<input type=checkbox name="hin" value="Hinfahrt"> Hinfahrt<br>

<input type=checkbox name="rueck" value="Rueckfahrt"> Rueckfahrt<br>

<input type=checkbox name="bezahlt" value="bezahlt"> Bezahlt<br>

<input type=submit values="Eintragen"><br>

</form>

<hr>

<?php

mysql_query("insert into Fahrtenbuch() values('$kuerzel','$datum',1,'$hinja','$rueckja',$bezahltja)");
echo "Eingetragen wurde: ";
echo "<br>";
echo "<br>";
echo "K&uuml;rzel: ";
echo $kuerzel;
echo "<br>";
echo "Datum: ";
echo $datum;
echo "<br>";
echo "Hinfahrt: ";
echo $hinja;
echo "<br>";
echo "R&uuml;ckfahrt: ";
echo $rueckja;
echo "<br>";
echo "Bezahlt: ";
echo $bezahltja;
echo "<br>";
?>

<hr>
<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>Nummer</th>";
echo	"<th>K&uuml;rzel</th>";
echo	"<th>Datum</th>";
echo	"<th>Hinfahrt</th>";
echo	"<th>Rückfahrt</th>";
echo	"<th>Bezahlt</th>";
echo "</tr>";
$aus = mysql_query("select * from Fahrtenbuch");
$ausnr = mysql_num_rows($aus);
$a = 0;
while($a < $ausnr)
{
$au = mysql_query("select * from Fahrtenbuch");
$ausku = mysql_result($au,$a,0);
$ausdat = mysql_result($au,$a,1);
$aushin = mysql_result($au,$a,2);
$ausruck = mysql_result($au,$a,3);
$ausbez = mysql_result($au,$a,4);
echo "<tr>";
echo	"<td>$a</td>";
echo	"<td>$ausku</td>";
echo	"<td>$ausdat</td>";
echo	"<td>$aushin</td>";
echo	"<td>$ausruck</td>";
echo	"<td>$ausbez</td>";
echo "</tr>";
$a++;
}
echo "</table>";

?>
</body>
</html>