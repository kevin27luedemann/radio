<?php include('../auth.php'); ?>
<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("Fahrtenbuch") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");
?>
<html>
<head>
<title>mitupdateueber</title>
</head>
<body>

<?php
$aus = mysql_query("select * from Mitfahrer");
$au = mysql_num_rows($aus);
$a = 0;

while($a < $au)
{
if (isset($_POST["losc$a"]))
	{
	$ab = $_POST["losc$a"];
	mysql_query("delete from Mitfahrer where Mkuerzel = \"$ab\"");
	echo "L&ouml;schen erfolgreich: $ab";
	echo "<br>";
	}


$a++;
}
?>

<a href="haupt.php>Hauptseite</a><br>
<a href="Mitfahrerupdate.php">zur&uuml;ck</a><br>

</body>
</html>
