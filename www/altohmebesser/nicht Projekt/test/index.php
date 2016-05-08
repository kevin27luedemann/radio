<?php
mysql_connect('127.0.0.1','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("ich") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");
$text = $_POST["text"];
?>

<html>
<head>
<title>Meine Seite</title>
</head>
<body>
<form action="index.php" method=post>

<textarea name="text" rows=10 cols=50></textarea>
<input type=submit value="Absenden">
</form>

<?php
mysql_query("insert into ich(ichtext) values ('$text')");
echo $text;
?>

</body>
</html>