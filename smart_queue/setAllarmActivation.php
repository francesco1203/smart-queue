<?php

    header("Location: dashboard.php");

    if(!empty($_GET)){ //get che viene eseguita se ho cliccato sul bottone "attiva/disattiva"


        /* leggo lo stato dell'allarme sul file */
        $f = fopen("allarmActivation.txt", "r");
        $content = fread($f, filesize("allarmActivation.txt"));
        fclose($f);

        /* in base allo stato attuale, devo cambiarlo nel suo opposto  */
        $toWrite="";

        if(strcmp($content, "1") == 0)  //è acceso -> devo spegnere
            $toWrite = "0";            
        else                            //è spento -> devo accendere
            $toWrite = "1";    

        $f = fopen("allarmActivation.txt", "w");
        fwrite($f, $toWrite);
        fclose($f);
    }

?>