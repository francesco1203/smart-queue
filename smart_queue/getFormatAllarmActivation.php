<?php

    /* leggo lo stato dell'allarme sul file */
    $f = fopen("allarmActivation.txt", "r");
    $content = fread($f, filesize("allarmActivation.txt"));
    fclose($f);

    /* lo formatto per l'output */
    if($content == "0")
        echo "Spento";
    else
        echo "Acceso";

?>