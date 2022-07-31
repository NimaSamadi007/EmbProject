<?php
$db_host = "localhost";
$db_user = "test";
$db_pass = "123456";
$db_name = "sensors";
$conn = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
?>
<!doctype html>
<html>
<head>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <title>Emb Project Web Server</title>
</head>
<body style="font-size:40px; text-align:center; margin:0; background-color: #FFF8DC">
    <div class="row">
        <div class="w-50 rounded" style="background-color:#007bff; margin-top: 20px; margin-left:auto; margin-right:auto; padding:10px; color: white;">Real-time Embedded Systems Course Project</div>
    </div>
    <div class="row">
        <div class="w-50 shadow rounded" style="border:solid 1px white; margin-left:auto; margin-right:auto; padding:10px; background-color: white;">
            <img class="w-75 rounded" src="./img.jpg" style="border: solid #007bff 2px;">
            <form method="GET" action="index.php">
                <input type="hidden" name="update" value="true">
                <input class="btn btn-primary" style="font-size:18px" type="submit" value="Update image">
            </form>
        </div>
    </div>
    <div class="row">
        <div class="w-50 shadow rounded" style="margin-left:auto; margin-right:auto; background-color: white; margin-top: 30px;">
            <div class="col w" style="background-color:#007bff; font-size:40px; color: white; margin-left: auto; margin-right: auto;">
                Database
            </div>
            <div class="col w-50"> 
                <form method="GET" action="index.php">
                    <input class="w-25 h-25 rounded" type="input" name="num_of_faces" placeholder="1">
                    <input class="btn btn-primary" style="font-size:18px" type="submit" value="show">
                </form>
            </div>
            <div class="col w-50"> 
                <form method="GET" action="index.php">
                    <input class="w-25 h-25 rounded" type="input" name="num_of_faces" placeholder="1">
                    <input class="btn btn-primary" style="font-size:18px" type="submit" value="show">
                </form>
            </div>
        </div>
    </div>

    <?php
        switch($_SERVER["REQUEST_METHOD"]){
            case 'GET':
                if (!empty($_GET)){
                    if ($_GET["update"] == "true"){
                    }
                    $res = $_GET;
                }else{
                    $res = 'No request';
                }
            break;
        }
    ?>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/js/bootstrap.bundle.min.js" integrity="sha384-pprn3073KE6tl6bjs2QrFaJGz5/SUsLqktiwsUTF55Jfv3qYSDhgCecCxMW52nD2" crossorigin="anonymous"></script>
</body>
</html>
