
<?php
// Connect to database
//$db_host = "localhost";
//$db_user = "client";
//$db_pass = "123456";
//$db_name = "soap";
//$conn = mysqli_connect($db_host, $db_user, $db_pass, $db_name);

switch($_SERVER["REQUEST_METHOD"]){
	case 'GET':
		// Retrive Products
		if(!empty($_GET["id"])){
			echo "GET: id = ".$_GET["id"];
			// get_item($conn, $_GET["id"]);
		}else{
			echo "GET: id is empty";
			// get_items($conn,);
		}
		break;
	default:
		// Invalid Request Method
		header("HTTP/1.0 405 Method Not Allowed");
		break;
}

function get_items($conn){
	$sql="SELECT * FROM fruits";
	$response=array();
	$result=mysqli_query($conn, $sql);
	while($row=mysqli_fetch_array($result)){
		$response[]=$row;
	}
	header('Content-Type: application/json');
	echo json_encode($response);
}

function get_item($conn, $id=0){
	$sql="SELECT * FROM fruits";
	if($id != 0){
		$sql.=" WHERE id=".$id." LIMIT 1";
	}
	$response=array();
	$result=mysqli_query($conn, $sql);
	$response=mysqli_fetch_array($result);
	header('Content-Type: application/json');
	echo json_encode($response);
}
?>