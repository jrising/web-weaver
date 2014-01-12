<?php
// create a new cURL resource
$ch = curl_init();

// set URL and other appropriate options
curl_setopt($ch, CURLOPT_URL, $_GET['url']);
curl_setopt($ch, CURLOPT_HEADER, 1);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);

// grab URL and pass it to the browser
$result = curl_exec($ch);

// Extract cookies
preg_match('/^Set-Cookie: (.*?);/m', curl_exec($ch), $m);
$cookie = $m[1];

// close cURL resource, and free up system resources
curl_close($ch);

mkdir($_GET['dir']);
$filepath = $_GET['dir'] + '/' + $_GET['file'];
file_put_contents($filepath, $result);
return $filepath;

?>