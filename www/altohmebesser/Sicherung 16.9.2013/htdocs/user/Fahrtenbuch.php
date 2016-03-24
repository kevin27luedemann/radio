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
	$bezahltja = "TRUE";
	}
else
	{
	$bezahltja = "FALSE";
	}
?>

<html>
<head>
<title>Fahrtenbuch</title>
</head>
<body>
<h1>Fahrtenbucheintragungen</h1>
Mit diesem Interface werden Eintr&auml;ge in das Fahrtenbuch geschrieben.<br><br>
<form action="Fahrtenbuch.php" method=post>


K&uuml;rzel: 
<?php
$kueau = mysql_query("select Mkuerzel from Mitfahrer");
$kuenum = mysql_num_rows($kueau);
$k = 0;
echo	"<select name=\"kuerzel\">";
while($k < $kuenum)
{
$kueaus = mysql_result($kueau,$k,0);
echo	"<option> $kueaus";
$k++;
}
echo	"</select>";
?><br><br>

Datum (Tag/Monat/Jahr): 
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
</select><br><br>

<input type=radio name="geld" checked value=1> Normaler Betrag<br>
<input type=radio name="geld" value=0> Sonderbetrag in Euro (nur mit '.'): 
<input name="geldsonder"><br><br>

<input type=checkbox name="hin" value="Hinfahrt"> Hinfahrt<br><br>

<input type=checkbox name="rueck" value="Rueckfahrt"> Rueckfahrt<br><br>

<input type=checkbox name="bezahlt" value="bezahlt"> Bezahlt<br><br>

<input type=submit values="Eintragen"><br><br>

</form>
<?php
$geld = $_POST["geld"];

if ($geld == 0)
	{
	$geld = $_POST["geldsonder"];
	}
?>
<hr>

<?php

mysql_query("insert into Fahrtenbuch(Mkuerzel,Tag,Geld,Hin,Rueck,Bezahlt) values('$kuerzel','$datum',$geld,'$hinja','$rueckja',$bezahltja)");
echo	 "Eingetragen wurde: ";
echo "<br>";
echo "<br>";
echo	 "K&uuml;rzel: ";
echo	 $kuerzel;
echo "<br>";
echo	 "Datum: ";
echo	 $datum;
echo "<br>";
echo	"Geldbetrag: ";
echo	$geld;
echo "<br>";
echo	 "Hinfahrt: ";
echo	 $hinja;
echo "<br>";
echo	 "R&uuml;ckfahrt: ";
echo	 $rueckja;
echo "<br>";
echo	 "Bezahlt: ";
echo	 $bezahltja;
echo "<br>";
?>


</body>
</html>