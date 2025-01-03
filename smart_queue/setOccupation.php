<?php 

    /*scrivo su file dato da ESP*/
    if(!empty($_GET)){
        $f = fopen("occupazione.txt", "w");
        fwrite($f, $_GET["value"]);
        fclose($f);
    } 



?>