<?php

$page = $_SERVER['PHP_SELF'];
$sec = "900"; //Refresh page toutes les 15minutes (temps = secondes) (900s =15Min)
header("Refresh: $sec; url=$page");
error_reporting( 0 );

$curl = curl_init();
curl_setopt_array($curl, array(CURLOPT_RETURNTRANSFER => 1,CURLOPT_URL => 'https://api.spark.io/v1/devices/55ff6d065075555319241887/dustVal/?access_token=0e0e6f8b604ce26ec3206c64bbf333b34174498d'));


$resp = curl_exec($curl);
curl_close($curl);
$data = json_decode($resp);

$dust = $data->result;


$dbhost = 'localhost';
$dbuser = 'root';
$dbpass = 'seadiookak38';
$dbbase = 'dustSensor';



$connect = mysql_connect($dbhost, $dbuser, $dbpass) or die ("erreur de connexion");
mysql_select_db($dbbase,$connect) or die ("erreur de connexion base");


if(! $connect )
{
  die('Could not connect: ' . mysql_error());
}







$sql = 'INSERT INTO Dust'.'(Dust, Temps)'.'VALUES('.$dust.', NOW())';

mysql_query($sql); //Appel de la requête.


// Récup Datas
$query = "
  SELECT *
  FROM Dust
  ORDER BY Temps ASC";

$rquery = mysql_query($query);

// Tout est bon?
if ( !$rquery ) {
  // NON
  $message  = 'Invalid query: ' . mysql_error() . "\n";
  $message .= 'Whole query: ' . $query;
  header('HTTP/1.1 500 Internal Server ' . $message);
  die( $message );
}

//Initialisation et Création d'un tableau associatif (Json) compris par Fcharts / AmCharts

$prefix = '';
echo "[\n";
while ( $row = mysql_fetch_assoc( $rquery ) ) {
  echo $prefix . " {\n";
  echo '  "Temps": "' . $row['Temps'] . '",' . "\n";
  echo '  "Dust": ' . $row['Dust']  . "\n";
  echo " }";
  $prefix = ",\n";
}
echo "\n]";

mysql_close($connect);

?>
 
