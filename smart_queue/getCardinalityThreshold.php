<?php

    /* leggo la soglia da file */
    $f = fopen("soglia.txt", "r");
    $content = fread($f, filesize("soglia.txt"));
    fclose($f);


    echo $content;

?>