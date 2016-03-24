<?php include('../auth.php'); ?>
<?php
mysql_connect('localhost','root') OR DIE ("Konnte nicht mit MySQL verbinden.");
@mysql_select_db("philo") OR DIE ("Konnte nicht mit Datenbank auf MySQL verbinden.");

?>

<html>
<head>
<title>Neus Dokument</title>
</head>
<body>
<h1>Neues Dokument erstellen</h1>
Hiermit k&ouml;nnen neue Dokumente erstellt werden. Es murr beachtet werden, das die Textformatierung
nur durch HTML Tags erreicht werden kann.<br><br>

<form action="eintrneu.php" method=POST>

Art des Dokumentes: 
<select name="wahl">
<option> Philosophie
<option> Gedichte
</select><br><br>

Name des Dokumentes: 
<input name="name"><br><br>

Inhalt/ Text des Dokumentes: <br>
<textarea name="text" rows=20 cols=60></textarea><br><br>

<input type=submit value="Eintragen"><br>
<a href="haupt.php">Hauptseite</a><br>
<a href="../logout.php">Logout</a>
</form>
</body>
</html>
