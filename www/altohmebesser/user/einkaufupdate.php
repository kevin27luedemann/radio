<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Einkaufsliste") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

$aus = mysql_query("select * from Liste");
$au = mysql_num_rows($aus);
$a = 0;

while($a < $au)
{
if (isset($_POST["los$a"]))
	{
	$ab = $_POST["los$a"];
	mysql_query("delete from Liste where Nummer = \"$ab\"");
	echo "L&ouml;schen erfolgreich: $ab";
	echo "<br>";
	}


$a++;
}


echo "<a href=\"Einkaufsliste.php\" target=\"haupt\">zur&uuml;ck</a><br>";



?>