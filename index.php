<html>
<head>
<title>Test ESP</title>
</head>
<body>
<h2>Panoul de control</h2>

<?php

//$valuesArray = file("values.txt");

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

echo $valuesArray[0] . "," . $valuesArray[1] . "," . $valuesArray[2];

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

<form method="post">
    <input type="range" name="brightness" value="<?php echo $Bright ?>" min="0" max="100" />
	<!--<input type="range" name="numberofleds" value="<?php echo $NumberOfLeds ?>" min="0" max="16" />-->
	<input type="number" name="numberofleds" value="<?php echo $NumberOfLeds ?>" min="0" max="16">
	<select name="colors" value=<?php echo $Color ?>>
		<option value="Red">Red</option>
		<option value="Green">Green</option>
		<option value="Blue">Blue</option>
		<option value="Pink">Pink</option>
		<option value="White">White</option>
	</select>
	<input type="submit" value="Send">
</form>

<div id="Values" style="">
<ol>
	<li id="brightnessValue"><?php echo $Bright ?></li>
	<li id="numberofledsValue"><?php echo $NumberOfLeds ?></li>
	<li id="colorValue"><?php echo $Color ?></li>
</ol>
</div>

<div id="hiddenValues" style="display:none">
<?php echo $Bright . "," . $NumberOfLeds . "," . $Color . ",";?> 
</div>


</body>
</html>