<?php

    /*scrivo su DB valore dell'ESP (occupazione oraria) */

    require("config.php"); //connessione al DB


    if(!empty($_GET)){
        $hours = date('h', time()); 

        $specifier = date('a', time());  //am oppure pm
        if(strcmp($specifier, "pm") == 0)
            $hours+=12;

        echo $hours;

        if($hours >= 10 && $hours <= 18) //se l'ora appena passata è quella dell'apertura del museo, cioè da 9:00 a 17:59
        {   
            
            $hours = $hours -1;         //trovo l'orario da registrare (fascia oraria = ora - 1 ) 
            $x = $_GET["value"];        //numero di visite in quest'ora trascorsa

            $sql = "INSERT INTO tab_entrate  (fascia_oraria, numero_visitatori, Data) VALUES ('$hours', '$x', CURRENT_DATE() )";
            $connessione->query($sql);
            
        }
    }

?>