<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Bilder") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

$albumnr = $_POST["Albumnr"];
$albumname = $_POST["Albumname"];

echo "Bilder aus dem Album: <u>$albumname</u> ausgegeben";
echo "<br><br>";

echo "<table border=1>";


echo "<tr>";
echo	"<th>Nummer</th>";
echo	"<th>Bildname</th>";
echo	"<th>Bild</th>";
echo "</tr>";


$aus = mysql_query("select * from Bild where Albumnr = $albumnr");
$ausnr = mysql_num_rows($aus);


$a = 0;
while($a < $ausnr)
{

$ausnum = mysql_result($aus,$a,0);
$ausnam = mysql_result($aus,$a,1);
$ausbild = mysql_result($aus,$a,2);



$dateideco = base64_decode($ausbild);

$a++;
$location = $a . '.jpeg';
$file = fopen($location, "w+");
fwrite($file, $dateideco);


echo "<tr>";
echo	"<td>$ausnum</td>";
echo	"<td>$ausnam</td>";
echo	"<td><img src=\"$location\"width=480 hight=320></td>";
echo "</tr>";

fclose($file);

}


echo "</table>";









?>