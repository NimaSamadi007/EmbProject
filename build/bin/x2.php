<?php
switch($_SERVER["REQUEST_METHOD"]){
	case 'GET':
		if (!empty($_GET)){
			$res = $_GET;
		}else{
			$res = 'No request';
		}
		break;
	case 'POST':
		$res = $_POST;
		break;
}
?>
<!DOCTYPE html>
<body>
    <div >
        <div style="width:40%; border:solid 1px black; margin-left:auto; margin-right:auto; padding:10px;">
            <a href="x2.php?x=x_value&y=y_value">GET Link</a>
            <hr/>
            <form method="GET" action="x2.php">
                GET FORM:
                <br/>
                x:
                <input type="text" name="x" value="x_value">
                y:
                <input type="text" name="y" value="y_value">
                <input type="submit">
            </form>
            <hr/>
            <form method="post" action="x2.php">
                POST form:
                <br/>
                x:
                <input type="text" name="x" value="x_value">
                y:
                <input type="text" name="y" value="y_value">
                <input type="hidden" name="hidden_item" value="hidden_item_value">
                <input type="submit">
            </form>
            <hr/>
        </div>
    </div>
    <div>
    	<?php
    		echo '<h1>Request Type: '.$_SERVER["REQUEST_METHOD"].'</h1>';
    		echo '<pre>';
		print_r($res);
		echo '</pre>';
	?>
    </div>
</body>
