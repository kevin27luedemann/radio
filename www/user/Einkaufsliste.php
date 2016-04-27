<?php include('../auth.php'); ?>
<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Einkaufsliste") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title></title>
</head>
<body>
<h1>Einkaufsliste</h1>
Hiermit kann die Einkausfliste ge&auml;andert werden.<br><br>

<form action="einkaufinse.php" method=POST>

Name: 
<input name="nam"><br><br>

Menge: 
<input name="menge"><br><br>

Einkaufsdatum (Tag/Monat/Jahr): 
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
<option> 2014
<option> 2015
<option> 2016
<option> 2017
<option> 2018
</select><br><br>

Priorität(niedrig = 1, hoch = 5): 
<select name="prio">
<option> 5
<option> 4
<option> 3
<option> 2
<option> 1
</select><br><br>

Quelle: 
<input name="quel"><br><br>

Beschreibung: <br>
<textarea name="bes" rows=5 cols=30></textarea><br>

<input type=submit value="Eintragen"><br>


</form>
<hr>
<form action="einkaufupdate.php" method=POST>
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
echo	"<th>L&ouml;schen</th>";
echo "</tr>";

$aus = mysql_query("select * from liste");
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
echo	"<td><input type=checkbox name=\"los$a\" value=$ausnum></td>";
echo "</tr>";

$a++;
}

echo "</table>";

?>
<input type=submit value="L&ouml;schen">

</form>
<a href="haupt.php">Hauptseite</a><br>
<a href="../logout.php">Logout</a>
</body>
</html>
