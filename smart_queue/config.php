
<?php

/*realizza la connessione al database */ 

$host= "127.0.0.1";
$user= "root";
$password ="";
$db= "smart_queue";

$connessione = new mysqli($host,$user,$password,$db);

if($connessione == false){
    die("Errore durante la connessione" . $connessione->connect_error);
}

?>