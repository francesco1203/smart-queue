<?php

    /*leggo da file*/
    $f = fopen("occupazione.txt", "r");
    $content = fread($f, filesize("occupazione.txt"));
    fclose($f);


    echo $content;

?>