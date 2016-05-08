<?php include('../auth.php'); ?>
<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Bilder") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title></title>
</head>
<body>
<h1>Dateien hochladen</h1>
<p>Mit diesem Interface werden Bilder in ein Album geladen<p>


<form action="bildhochver.php" method=POST enctype="multipart/form-data">


<input type=radio name=albumja checked value=0	>Album vorhanden?<br>
<input type=radio name=albumja value=1		>Neuen Albumnamen eingeben:  
<input name="neuAlbumname"><br><br>
Name des Album: 
<?php

$aus = mysql_query("select * from Album");
$ausnum = mysql_num_rows($aus);

$a = 0;

echo	"<select name=\"Albumname\">";

while($a < $ausnum)
{
$Albumname = mysql_result($aus,$a,1);
$Albumnr = mysql_result($aus,$a,0);
echo	"<option value=$Albumnr> $Albumname";
$a++;
}
echo	"</select>";
echo	"<br><br>";





?>

Name des Bildes: 
<input name="name"><br>
Bilddatei: <input type="file" name="bild" size="50" maxlength="1000000000" accept="image/*"><br><br>
<input type=submit value="Bild hochladen"><br>


</form>
<a href="haupt.php">Hauptseite</a><br>
<a href="../logout.php">Logout</a>
</body>
</html>
