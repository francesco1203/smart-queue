<?php 

     /*scrivo su DB valore dell'ESP (durata) */

    require("config.php"); //connessione al DB



    if(!empty($_GET)){

        $x = $_GET["value"];

        $sql = "INSERT INTO tab_allarme  (data_ora_fine_allarme, durata) VALUES (current_timestamp(), '$x')";
        $connessione->query($sql); 
    } 

?>