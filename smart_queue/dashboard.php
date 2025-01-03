<?php 

	/*gestisce accesso fuori dal login*/ 
    session_start();
	$email=$_SESSION["email"];
    if(!isset($_SESSION['loggato']) && $_SESSION['loggato'] != true ){
        header("location: login_admin.html");
        exit;
    }

	
	require("config.php");

	/*Carico dataPoints per il disegno dell'istogramma*/
	$sql = "SELECT * FROM tab_entrate WHERE tab_entrate.data = CURRENT_DATE()" ;
    $result = $connessione ->query($sql);
	$i = 0;
	while($row = mysqli_fetch_assoc($result))
	{  
		$dataPoints[$i] = array("x"=> $row['fascia_oraria'], "y"=> $row['numero_visitatori']);

		//echo $dataPoints[$i]["x"]." ".$dataPoints[$i]["y"]."   "; (debug)

		$i = $i + 1;
	}

	/*
	Imposto un refresh della pagina corrente dopo 10 secondi 
	*/
	$curpage = $_SERVER['PHP_SELF'];
	header('Refresh: 10; url=' . $curpage);


?>

<!DOCTYPE html>
<html>
<head>
	<!-- GRAFICO A TORTA -->
		<script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>
		<script type="text/javascript" src="//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>

		<script type="text/javascript">
			function drawChart() {
				// call ajax function to get data
				var jsonData = $.ajax({
					url: "data.php",
					dataType: "json",
					async: false
				}).responseText;
				//The DataTable object is used to hold the data passed into a visualization.
				var data = new google.visualization.DataTable(jsonData);

				// To render the pie chart.
				var chart = new google.visualization.PieChart(document.getElementById('chart_container'));
				chart.draw(data, {width: 400, height: 240});
			}
			// load the visualization api
			google.charts.load('current', {'packages':['corechart']});

			// Set a callback to run when the Google Visualization API is loaded.
			google.charts.setOnLoadCallback(drawChart);
		</script>
	
	<!-- GRAFICO A BARRE -->
		<script>
		window.onload = function () {
		
		var chart = new CanvasJS.Chart("chartContainer", {
			animationEnabled: false,
			exportEnabled: true,
			theme: "light1", // "light1", "light2", "dark1", "dark2"
			title:{
				text: "visite per orario"
			},
			axisY:{
				includeZero: true
			},
			data: [{
				type: "column", //change type to bar, line, area, pie, etc
				indexLabel: "{y}", //Shows y value on all Data Points
				indexLabelFontColor: "#5A5757",
				indexLabelPlacement: "outside",   
				dataPoints: <?php echo json_encode($dataPoints, JSON_NUMERIC_CHECK); ?>
			}]
		});
		chart.render();
		
		}
		</script>
	


	<!-- STILE -->
		<link rel="stylesheet" href="style_dashboard.css">

</head>

<body>
<header class="header">
<a href="dashboard.php" class="logo">Smart Queue</a>
    <input class="menu-btn" id="menu-btn" type="checkbox">
    <!-- Bottone effettivo ; checked l'ho aggiunto io-->
    <label for="menu-btn" class="menu-icon">
        <!-- Icona del menù -->
        <span class="nav-icon"></span><!-- Effettiva icona -->
    </label>
    <ul class="menu">
        <li><a href="logout.php">Logout</a></li>
    </ul>
	</header>
	<br>

	<?php echo ' Accesso eseguito da : '. $email;?>
<div class="row">
	<div class="leftcolumn">
    
		<div class="card">
			<h2>OCCUPAZIONE ATTUALE</h2>
	  
			<div class="row">
				<div class="leftcolumn2">
				
					<h5>su un totale di </h5>
				</div>
		
				<form action="setCardinalityThreshold.php" method="get">
					<div class="centralcolumn2">
						
							<input type="text" id="userSetThreshold" name="userSetThreshold" >
							
						
					</div>
			
					<div class="rightcolumn2">
						<span>
							<input type="submit" id="tresholdSetButton" value="">
						</span>
						
						<div class="dropdown-content">
							<p>Cambia la capienza massima</p>
						</div>
					
					</div>
				</form>
			</div>
	  
			<div class="row">
				<div class="fakeimg" style="height:100px; padding-top:20px; padding-bottom:20px;  padding-left:140px"  >

					<div>
						<h3><?php require("getOccupation.php"); ?> su <?php require("getCardinalityThreshold.php"); ?></h3>
					</div>
			    </div>
			</div>
		</div>
		
		<div class="card">
			 <img src="museo.jpg" alt="museo" style="width:100%;height:200px;">
		</div>

		<div class="card">
			developed by Schettini Francesco, Turco Francesco
			<br><br><br>
			<img src="logoVanvitelli.png" alt="logoUni" style="width:80%;height:150px;">
			
			
		</div>
	</div>
  
	<div class="rightcolumn">
	
		<div class="row">
			<div class="leftcolumn3">
				<div class="card">
					<h2>Lista allarmi</h2>
					<?php
                     $sql="SELECT* FROM tab_allarme";
					 if($result = $connessione->query($sql)){
					  	if($result -> num_rows > 0){
							echo'
							  <table style="font-family: arial, sans-serif;
							  border-collapse: collapse;
							  width: 100%;
							  border: 2px solid #dddddd;
							  text-align: left;
							  padding: 1px;
							  background-color: #5c5858;
							  ">
							  <thead>
							  <tr style = "border: 2px solid #dddddd">
							  <th style = "border: 2px solid #dddddd">Allarme</th>
							  <th style = "border: 2px solid #dddddd">data ora fine allarme</th>
							  <th style = "border: 2px solid #dddddd">durata</th>
							  </tr></thead>';

							  while($row = $result->fetch_array()){
								echo'
								<tr>
								<td style = "border: 2px solid #dddddd">'. $row['id_allarme'] . '</td> 
								<td style = "border: 2px solid #dddddd">'. $row['data_ora_fine_allarme'] . '</td> 
								<td style = "border: 2px solid #dddddd">'. $row['durata'] . '</td> 
								</tr>';
								}
								
								echo'
								</table>';

							}
							else
							{
							echo "Non ci sono allarmi";
							}
						}
					?>
						
				</div>
			</div>
			
			<div class="rightcolumn3">
				<div class="card">
					<h3 id="headerDisattivaAllarme">Disattiva allarme</h3>
					
					<div class="row">
					
						<div class="leftcolumn4">
						
							<div class="leftcolumn5">
								stato: 
							</div>	

							<div class="rightcolumn5">
								<?php require("getFormatAllarmActivation.php"); ?>
							</div>

							<form action="setAllarmActivation.php" method="get">
								<input type="submit" class="disableAllarmButton" name="setActivation" value="disattiva/attiva">
							</form>
						</div>
							
						<div class="rightcolumn4">			
							<img src="sirena.png" alt="sirena" style="width:100%;height: 90px;padding-top: 20px; padding-left: 10px">
						</div>		
						
						
					</div>
					
				</div>
				
				<div class="card">
					<img src="esternomuseo.jpg" alt="esterno" style="width:100%;height:80px;">
				</div>
			</div>
			
		</div>
		
		<div class="card">
			<div class="fakeimg" style="height:490px;">
				<h2 id="graphicsHeader">Occupazione giornaliera per fasce orarie</h2>

				<div class="leftcolumn6">
					<div class="row">
						<div id="chart_container"></div>
					</div>

					<div class="card" style="width: 80%;">
						<h3>Su un totale di:  <?php require("getTotal.php") ?></h3>
					</div>
				</div>
					
				<div class="rightcolumn6">
					<script src="https://cdn.canvasjs.com/canvasjs.min.js"></script>
					<div id="chartContainer" style="height: 370px; width: 100%;"></div>
				</div>
			</div>

			<br>
			Nota: orario 'N' indica la fascia oraria 'N' - 'N+1' (es 9 -> 9:00 - 9:59)
		</div>
		
  </div>
</div>

</body>
</html>
