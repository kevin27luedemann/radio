<?php

mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Bilder") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

$albumja = $_POST["albumja"];
$albumnr = $_POST["Albumname"];;


if($albumja == 1)
	{
	$albumneu = $_POST["neuAlbumname"];
	mysql_query("insert into Album(Albumname) values('$albumneu')");
	$aus = mysql_query("select albumnr from Album where Albumname = '$albumneu'");
	$albumnr = mysql_result($aus,0,0);

	}





$dateinam = $_FILES['bild']['tmp_name'];
$dateistring = file_get_contents($dateinam);

$datei = base64_encode($dateistring);
$dateiname = $_POST["name"];

if($_FILES['bild']['error'] == 0)
{
	mysql_query("insert into Bild(Bildnam,Bild,Albumnr) values('$dateiname','$datei',$albumnr)");
	echo "Das Bild: ";
	echo "<u>$dateiname</u>";
	echo " ";
	echo "wurde in die Datenbank geschrieben.";
	echo "<br>";
	echo "<a href=\"bildhoch.php\" target=\"haupt\">Zur&uuml;ck</a>";
}

?>