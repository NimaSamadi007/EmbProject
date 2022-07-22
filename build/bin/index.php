<html>
<head><title>Request count</title></head>
<body>
<h1>Request count</h1>
<p>There have been requests so far.</p>
<img src="./test.jpg" width="300" height="500">
<form method="GET" action="index.php">
    GET FORM:
    <br/>
    id:
    <input type="text" name="id" value="123">
    <input type="submit">
</form>
<?php
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
?>
</body>
</html>

