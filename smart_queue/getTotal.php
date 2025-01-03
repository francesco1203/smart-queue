<?php
    
    /*leggo da DB tutte le entrate orarie giornaliere e le sommo tutte*/
    require("config.php"); //connesione DB

    $sql = "SELECT * FROM tab_entrate WHERE tab_entrate.Data = CURRENT_DATE()";
    $result = mysqli_query($connessione, $sql);

    
    $total=0;

    while($row = mysqli_fetch_assoc($result))
    {  
        $total += $row['numero_visitatori'];
    }

    echo $total;

?>