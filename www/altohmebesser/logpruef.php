<?php
$benut = $_POST["benut"];
$pas = $_POST["pas"];
if ($benut == "Ich" && $pas == "123456")
	{
	echo "<meta http-equiv=\"refresh\" content=\"0; URL=user/haupt.php\">";
	}
else
	{
	echo "<meta http-equiv=\"refresh\" content=\"0; URL=index.php\">";
	}
?>