<?php
	$url=$_POST['url'];
	$num=$_POST['deluno'];
	if(isset($_REQUEST['imbu_x'])){
#		echo "<br><br>Button pressed<br><br>";
		if($url!="url"){
			$output = shell_exec("mpc add $url");
#			echo "<br>Das ist passier:<br>$url<br>$output<br><br>";
		}
		if($num!="0"){
			$output = shell_exec("mpc del $num");
#			echo "<br>Das ist nr $num:<br>$output<br><br>";
		}
	}
?>
<html>
<head>
<title>Einstellung des Radio</title>
</head>
<body>
<h1>Neue Eintr&auml;ge f&uuml;r das Radio</h1>
<p>Liste der bisherigen Radiosender:
<br><br>
<?php
	$out0 = shell_exec("mpc playlist");
	$out1 = str_replace("Â´","&auml;",$out0);
	$out2 = str_replace("ü","&uuml;",$out1);
	$out3 = str_replace("ö","&ouml;",$out2);
#	$ergeb = explode("\n",$out3);
#	$i=0;
#	$anzahl = count($ergeb);
#	echo "Anzahl: $anzahl<br>";
#	echo "<br>"explode("\n",$out3)"<br>";
#	while($i<count($ergeb){
#		echo "$i\t";#$ergeb[$i]"<br>";
#		$i = $i+1;
#	}
	$out4 = str_replace("\n","<br>",$out3);
	echo "$out4"
?>
</p>
<form action="index.php", method="post">
<p>
Hier kann ein neuer Sender hinzugef&uuml;gt werden:<br>
	Url: <input type="text" name="url" value="url"/><br>
</p>
<p>
Hiermit kann man einen Sender wieder entfernen.<br>
Dazu muss man nur die Nummer des Senders angeben.<br>
Diese sind von 1 an nummerrier.<br>
	Nummer des Senders: <input type="text" name="deluno" value="0"/><br>
	<br>
	<input type="image" src="enter.png" id="imbu" name="imbu" width="200" height="200"/>
	<br>Best&auml;tigen<br>
</p>
</form>
</body>
</html>
