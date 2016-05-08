<?php include('../auth.php'); ?>
<html>
<head>
<title>Hauptseite</title>
</head>
<body>
<font>
<h1>Hauptseite</h1>

Dies ist die Hauptseite des Interfaces, mit welchen auf die wichtigsten Funktionen, 
des mordernen Hauses zugegriffen werden kann.<br>

<form action="Fahrtenbuch.php" method=POST>
<input type=submit value="Fahrtenbuch">
</form><br>
<form action="Budget.php" method=POST>
<input type=submit value="Budget">
</form>

<a href="haupt.php" >Hauptseite</a><br><br>
<a href="webcam.php" >&Uuml;berwachungskamera</a><br><br>
<a href="../ampel/index.php" >Ampelseite</a><br><br>

<a href="Fahrtenbuch.php" >Fahrtenbuch</a><br><br>
<a href="neueseite.php" >Neues Dokument</a><br><br>
<a href="Fahrtenbuchausgabe.php" >Fahrtebuchausgabe</a><br><br>
<a href="Fahrtenbuchselektiert.php" >Fahrtenbuch selekt</a><br><br>
<a href="Fahrtenbuchupdate.php" >Fahrtenbuchupdate</a><br><br>

<a href="Mitfahrerupdate.php" >Mitfahrerupdate</a><br><br>

<a href="philo.php" >Philosophie</a><br><br>
<a href="gedichte.php" >Gedichte</a><br><br>

<a href="Einkaufsliste.php" >Einkaufsliste</a><br><br>

<a href="bildhoch.php" >Bild Hoch</a><br><br>
<a href="Bilderaus.php" >Bilderausgabe</a><br><br>
<a href="../logout.php" >Logout</a><br><br>
</font>
</body>
</html>
