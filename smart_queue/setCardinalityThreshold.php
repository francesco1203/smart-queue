<?php 


    if(!empty($_GET)){ //se cliccato sulla matita

        if($_GET["userSetThreshold"] > 0){  //fa un controllo se maggiore di 0 (soglia valida)
            $f = fopen("soglia.txt", "w");
            fwrite($f, $_GET["userSetThreshold"]);
            fclose($f);
        }
        
    } 

    header("Location: dashboard.php");
    
?>