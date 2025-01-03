<?php

    /* leggo lo stato dell'allarme sul file */
    $f = fopen("allarmActivation.txt", "r");
    $content = fread($f, filesize("allarmActivation.txt"));
    fclose($f);

    echo $content;
    

?>