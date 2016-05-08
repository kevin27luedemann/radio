<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("philo") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title>Gedichte</title>
</head>
<body>
<h1>Gedichte von mir</h1>
Hier werden die Gedichte ausgegeben.<br>

<form action="gediup.php" method=POST>
<?php
echo "<table border=1>";
echo "<tr>";
echo	"<th>Nummer</th>";
echo	"<th>Gedichtname</th>";
echo	"<th>Gedicht</th>";
echo	"<th>L&ouml;schen<th>";
echo "</tr>";
$aus = mysql_query("select * from doku_gedichte order by gdokunr");
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
echo	"<td><input type=checkbox name=\"los$a\" value=$ausnum></td>";
echo "</tr>";
$a++;
}
echo "</table>";

?><br>
<input type=submit value="L&ouml;schen"><br>
</form>
</body>
</html>