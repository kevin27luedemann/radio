<?php include('../auth.php'); ?>
<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Einkaufsliste") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

$aus = mysql_query("select * from liste");
$au = mysql_num_rows($aus);
$a = 0;

while($a < $au)
{
if (isset($_POST["los$a"]))
	{
	$ab = $_POST["los$a"];
	mysql_query("delete from liste where Nummer = \"$ab\"");
	echo "L&ouml;schen erfolgreich: $ab";
	echo "<br>";
	}


$a++;
}


echo "<a href=\"Einkaufsliste.php\">zur&uuml;ck</a><br>";



?>
