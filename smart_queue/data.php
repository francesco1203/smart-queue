<?php 
// MySQL database connection code
$connection = mysqli_connect("localhost","root","","smart_queue") or die("Error " . mysqli_error($connection));
//Fetch data
$sql = "SELECT * FROM tab_entrate WHERE tab_entrate.Data = CURRENT_DATE()";
$result = mysqli_query($connection, $sql) or die("Error in Selecting " . mysqli_error($connection));
//create an array
$array = array();
$i = 0;
while($row = mysqli_fetch_assoc($result))
{  
    $orgname = $row['fascia_oraria'];
    $count = $row['numero_visitatori'];
    $array['cols'][] = array('type' => 'string'); 
    $array['rows'][] = array('c' => array( array('v'=> $orgname), array('v'=>(int)$count)) );
}
$data = json_encode($array);
echo $data;
?>