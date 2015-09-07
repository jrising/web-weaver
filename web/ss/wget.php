<?php

/* Get arguments:
 *   ww_url = full url to post to
 *   ww_cookie = cookie to send
 *   ww_noxhtml = don't translate html for cross-domains
 *   ww_noscript = remove javascripts
 *   ww_noxform = don't redirect forms to wget
 *   ww_post = ignore _POST, and use this
 *
 * NOTE: Later will include a flag whether or not to send back headers.
 */

$UserDir = "/Users/jrising";
set_include_path($UserDir . "/pear/share/pear" . PATH_SEPARATOR . get_include_path());
$pear_user_config = $UserDir . "/.pearrc";

require_once("Net/URL2.php");

// Modified from http://davidwalsh.name/execute-http-post-php-curl

// url-ify the data for the POST
if ($_GET['ww_post']) {
  $fields_string = $_GET['ww_post'];
  $fields_count = substr_count($fields_string, '&') + 1;
} else {
  $fields_string = "";
  foreach ($_POST as $key=>$value)
    $fields_string .= $key . '=' . urlencode($value) . '&';
  rtrim($fields_string, '&');
  $fields_count = count($_POST);
}

$url = $_GET['ww_url'];
if (!$url)
  $url = $_POST['ww_url'];

// url-ify the data for GET
$urlargs = "";
foreach ($_GET as $key=>$value) {
  if (strpos($key, 'ww_') === 0)
    continue;
  $urlargs .= $key . '=' . urlencode($value) . '&';
}
rtrim($urlargs, '&');
if (strlen($urlargs) > 0)
  $url .= (strpos($url, '?') ? '&' : '?') . $urlargs;

// create a new cURL resource
$ch = curl_init();

// set URL and other appropriate options
curl_setopt($ch, CURLOPT_URL, $url);
curl_setopt($ch, CURLOPT_HEADER, 1);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($ch, CURLOPT_POST, TRUE);
curl_setopt($ch, CURLOPT_POSTFIELDS, $fields_string);
if ($_GET['ww_cookie'])
  curl_setopt($ch, CURLOPT_HTTPHEADER, array('Cookie: ' . $_GET['ww_cookie'],
                                             'User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_6_8) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/30.0.1599.69 Safari/537.36'));
else
  curl_setopt($ch, CURLOPT_HTTPHEADER, array('User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_6_8) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/30.0.1599.69 Safari/537.36', 'DNT: 1'));

// grab URL and pass it to the browser
$result = curl_exec($ch);

// Extract cookies
preg_match('/^Set-Cookie: (.*?);/m', $result, $m);
$cookie = $m[1];

$info = curl_getinfo($ch);
if ($info['http_code'] == 302) {
  $redirect = $info['redirect_url'];
}

// close cURL resource, and free up system resources
curl_close($ch);

if ($_GET['ww_noxhtml']) {
  echo $result;
  exit(1);
}

ini_set("memory_limit","120M");

require_once("simple_html_dom.php");

$html = str_get_html($result);

// Replace relatives with absolute
$uri = new Net_URL2($url); // URI of the resource
$baseURI = $uri;
foreach ($html->find('base[href]') as $elem)
  $baseURI = $uri->resolve($elem->href);

foreach ($html->find('*[src]') as $elem)
  $elem->src = $baseURI->resolve($elem->src)->__toString();

foreach ($html->find('*[href]') as $elem) {
  if (strtoupper($elem->tag) === 'BASE') continue;
  $elem->href = $baseURI->resolve($elem->href)->__toString();
}

if ($_GET['ww_noxform']) {
  foreach ($html->find('form[action]') as $elem) {
    $elem->action = $baseURI->resolve($elem->action)->__toString();
  }
} else {
  foreach ($html->find('form[action]') as $elem) {
    $oldact = $elem->action;
    $elem->action = $_SERVER['PHP_SELF'];
    $elem->innertext .= '<input type="hidden" name="ww_url" value="' . htmlspecialchars($baseURI->resolve($oldact)->__toString()) . '" />';
  }
}

if ($_GET['ww_noscript']) {
  foreach ($html->find('script') as $elem)
    $elem->outertext = "";
}

$body = $html->find('body', 0);
if ($body) {
  if ($cookie)
    $body->innertext .= '<div id="wget_cookie" style="display: none">' . $cookie . '</div>';
  if ($redirect)
    $body->innertext .= '<div id="wget_redirect" style="display: none">' . $redirect . '</div>';
} else {
  if ($cookie)
    $html .= '<div id="wget_cookie" style="display: none">' . $cookie . '</div>';
  if ($redirect)
    $html .= '<div id="wget_redirect" style="display: none">' . $redirect . '</div>';
}

echo $html;

?>
