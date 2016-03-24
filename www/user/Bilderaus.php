<?php include('../auth.php'); ?>
<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Bilder") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>
<html>
<head>
<title>Bilderausgabe</title>
</head>
<body>
<h1>Bilderausgabe komplett</h1>

<p>W&auml;len sie ein Album aus:</p>




<?php

echo "<table border=1>";

echo "<tr>";
echo	"<th>Nummer</th>";
echo	"<th>Bildname</th>";
echo	"<th>Album &ouml;ffnen</th>";

echo "</tr>";

$aus = mysql_query("select * from Album order by Albumnr");
$ausnr = mysql_num_rows($aus);

$a = 0;
while($a < $ausnr)
{

$ausnum = mysql_result($aus,$a,0);
$ausnam = mysql_result($aus,$a,1);





echo "<tr>";
echo	"<td>$ausnum</td>";
echo	"<td>$ausnam</td>";
echo	"<td>
		<form action=\"bilderalbaus.php\" method=POST>
		<input type=hidden name=\"Albumnr\" value=$ausnum>
		<input type=hidden name=\"Albumname\" value=$ausnam>
		<input type=submit value=\"Album &ouml;ffnen\">	
		</form>
								</td>";

echo "</tr>";



$a++;

}

echo "</table>";

?>


<a href="haupt.php">Hauptseite</a><br>
<a href="../logout.php">Logout</a>
</body>
</html>
