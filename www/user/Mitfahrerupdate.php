<?php include('../auth.php'); ?>
<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Fahrtenbuch") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title>Mitfahrerupdate</title>
</head>
<body>
<h1>Mitfahrerupdate</h1>

<form action="Mitupdate.php" method=POST>
Neuen Mitfahrer hinzufügen:<br><br>

K&uuml;rzel (nur 2 Zeichen): 
<input name="kuerzel" size=1><br><br>

Vorname, Name: 
<input name="vorname"> <input name="name"><br><br>

Telefonnummer: 
<input name="tel"><br><br>

Straße, Hausnummer: 
<input name="str"> <input name="haus"><br><br>

Ort, PLZ: 
<input name="ort"> <input name="plz"><br><br>
<input type=submit value="Eintragen"><br>
</form>
<hr>

<form action="mitupdateueber.php" method=POST>

<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>K&uuml;rzel</th>";
echo	"<th>Vorname</th>";
echo	"<th>Name</th>";
echo	"<th>Telefonnummer</th>";
echo	"<th>Straße</th>";
echo	"<th>Hausnummer</th>";
echo	"<th>Ort</th>";
echo	"<th>PLZ</th>";
echo	"<th>L&ouml;schen</th>";
echo "</tr>";
$aus = mysql_query("select * from Mitfahrer");
$ausnr = mysql_num_rows($aus);
$a = 0;
while($a < $ausnr)
{
$au = mysql_query("select * from Mitfahrer");
$ausku = mysql_result($au,$a,0);
$ausvor = mysql_result($au,$a,1);
$ausname = mysql_result($au,$a,2);
$austel = mysql_result($au,$a,3);
$ausstr = mysql_result($au,$a,4);
$aushaus = mysql_result($au,$a,5);
$ausort = mysql_result($au,$a,6);
$ausplz = mysql_result($au,$a,7);
echo "<tr>";
echo	"<td>$ausku</td>";
echo	"<td>$ausvor</td>";
echo	"<td>$ausname</td>";
echo	"<td>$austel</td>";
echo	"<td>$ausstr</td>";
echo	"<td>$aushaus</td>";
echo	"<td>$ausort</td>";
echo	"<td>$ausplz</td>";
echo	"<td><input type=checkbox name=\"losc$a\" value=\"$ausku\"<td>";
echo "</tr>";
$a++;
}
echo "</table>";

?><br>
<input type=submit value="Auswahl L&ouml;schen">

</form>
<a href="haupt.php">Hauptseite</a><br>
<a href="../logout.php">Logout</a>
</body>
</html>
