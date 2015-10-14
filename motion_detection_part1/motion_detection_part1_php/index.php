<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html>
    <head>
        <meta charset="UTF-8">
        <title>MOTION DETECTION</title>
    </head>
    <body>
        TURN DETECTION ON/OFF: <br>
		<?php
		$fp = fopen("state.txt", 'r') or die ("Can't open file");
		$content = fread($fp, filesize("state.txt"));
		fclose($fp);
		$fp = fopen("detection.txt", 'r') or die ("Can't open file");
		$detection = fread($fp, filesize("detection.txt"));
		fclose($fp);
		?>
    <form action="./data_change.php" method="get">
        <input type="text" name="on" id="on" value="on" hidden="true"/>
        <input type="submit" value="Turn on" <?php if($content==="TUON") echo "hidden=true"; ?>/>
    </form>
       <br>
    <form action="./data_change.php" method="get">
        <input type="text" name="off" id="off" value="off" hidden="true"/>
        <input type="submit" value="Turn off" <?php if($content==="TUOF") echo "hidden=true"; ?>/>
    </form>
	<?php
	if ($content === "TUON") {
		if ($detection === "yes") echo "<p style='color:red'>There is someone in the room </p>";
		else if ($detection ==="no") echo "<p>There is no one in the room</p>";
	}
	?>
    </body>
</html>
