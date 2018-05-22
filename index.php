<!DOCTYPE html>
<html>
<head>
	<title>LED CONTROL PANEL</title>
	<link rel="stylesheet" type="text/css" href="style.css">
	<link href="https://fonts.googleapis.com/css?family=Oswald" rel="stylesheet">
</head>
<body>

<?php

$handle = fopen("values.txt","rb");
if ($handle)
{
	while (($line = fgetcsv($handle, 0 ,"\n")) !== false)
	{
		foreach ($line as $value)
			$valuesArray[] = $value;
	}
	fclose($handle);
}

$Bright = $valuesArray[0];
$NumberOfLeds = $valuesArray[1];
$Color = $valuesArray[2];

if(isset($_POST['brightness']))
		$Bright = $_POST['brightness'];
if(isset($_POST['numberofleds']))
		$NumberOfLeds = $_POST['numberofleds'];
if(isset($_POST['colors']))
		$Color = $_POST['colors'];

$valuesArray[0] = $Bright;
$valuesArray[1] = $NumberOfLeds;
$valuesArray[2] = $Color;

// echo $valuesArray[0] . "," . $valuesArray[1] . "," . $valuesArray[2];

$handle = fopen("values.txt","wb");
if ($handle)
{
	foreach ($valuesArray as $value)
	{
		$value .= "\n";
		fwrite($handle,print_r($value,TRUE));
	}

	fclose($handle);
}

?>

<div id="wrapper">
	<h1>Control panel</h1>
	<form method="post">
	<div class="brightness">
		<p>Brightness</p>
		<input type="range" name="brightness" value="<?php echo $Bright ?>" min="0" max="100" />
		<!--<input type="range" name="numberofleds" value="<?php echo $NumberOfLeds ?>" min="0" max="16" />-->
	</div>
	<div class="numleds">
		<p>Number of LEDs</p>
		<input type="number" name="numberofleds" value="<?php echo $NumberOfLeds ?>" min="0" max="16">
	</div>
	<div class="colors">
		<p>Choose color</p>
		<select name="colors">
			<option <?php if( $Color == "Red" ) echo "selected" ?> value="Red">Red</option>
			<option <?php if( $Color == "Green" ) echo "selected" ?> value="Green">Green</option>
			<option <?php if( $Color == "Blue" ) echo "selected" ?> value="Blue">Blue</option>
			<option <?php if( $Color == "Pink" ) echo "selected" ?> value="Pink">Pink</option>
			<option <?php if( $Color == "White" ) echo "selected" ?> value="White">White</option>
		</select>
	</div>
	<div class="results">
		<input type="submit" value="Send" id="submit">
		<div id="Values">
			<p>System actual values: Brightness to <?php echo $Bright . "%, " . $NumberOfLeds . " leds, " .  $Color . " color" ?></p> 
		</div>
	</div>
	</form>
</div>

<div id="hiddenValues" style="display:none">
	<?php echo $Bright . "," . $NumberOfLeds . "," . $Color . ",";?> 
</div>


</body>
</html>