<?php
/* Change for your username and password for phpMyAdmin*/
define('DB_SERVER', 'classmysql.engr.oregonstate.edu');
define('DB_USERNAME', 'cs340_hartjack');
define('DB_PASSWORD', 'rubberfuckycoding');
define('DB_NAME', 'cs340_hartjack');
 
/* Attempt to connect to MySQL database */
$link = mysqli_connect(DB_SERVER, DB_USERNAME, DB_PASSWORD, DB_NAME);
 
// Check connection
if($link === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}
?>
