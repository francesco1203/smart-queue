<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Errore!</title>
</head>
<body>



<?php


    require("config.php");

    /*prendo email e password inseriti dall'utente*/
    $email = $_POST['email'];
    $password = $_POST['password'];

    /*confronto con dati del database*/
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $sql = "SELECT * FROM tab_admin WHERE email = '$email'";

        if($result = $connessione ->query($sql)){
            if($result->num_rows == 1)
            {
                $row = $result->fetch_array(MYSQLI_ASSOC);  //creo un array associativo prelevando dal database

                if($password == $row['password']) //password corretta
                {     
                    //login a buon fine
                    session_start();
                    $_SESSION['loggato'] = true;
                    $_SESSION['email'] = $row['email'];

                    header("location: dashboard.php");  //mi reinderizza alla pagina dashboard.php
                }
                else
                {
                    echo"La password non e' corretta";
                }
            }
            else
            {                                            //non ha trovato quell'email (result è null)
                echo"Non ci sono account con quella email";
            }
        }
        else
        {
                echo"Errore in fase di login!";
        }

        $connessione ->close();
    }



?>

            <h1 style="color:white; margin-top:40px; font-size:40px;">Username o Password errata!</h1>
            <br></br>
            <a href="../login_admin.html">Ritorna al Login</a>

    </div>

        
</body>
</html>
