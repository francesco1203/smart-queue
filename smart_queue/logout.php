<?php
require("config.php");
if(isset($_SESSION["email"]) && isset($_SESSION['loggato'])){
    $_SESSION['loggato']=false;
    $_SESSION['email']=null;
}
session_start();
$_SESSION = array();
session_destroy();
header("location: login_admin.html");
exit;
?>