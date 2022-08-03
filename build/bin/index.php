<!-- Writer: Nima Samadi -->
<?php
$db_host = "localhost";
$db_user = "test";
$db_pass = "123456";
$db_name = "sensors";
$conn = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
if (!$conn) {
  die("Connection failed: " . mysqli_connect_error());
}
?>
<!doctype html>
<html>
<head>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <title>Emb Project Web Server</title>
</head>
<body style="font-size:40px; text-align:center; margin:0; background-color: #4B4B4B">
    <div class="row">
        <div class="w-50 rounded" style="background-color:#007bff; margin-top: 20px; margin-left:auto; margin-right:auto; padding:10px; color: white;">Real-time Embedded Systems Course Project
        </div>
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
        <div class="w-50 rounded" style="background-color:#007bff; font-size:40px; color: white; margin-left: auto; margin-right: auto; margin-top: 30px;">
            Database
        </div>
    </div>
    <div class="row">
        <div class="w-50 shadow rounded" style="border:solid 1px white; margin-left:auto; margin-right:auto; background-color: white; padding: 10px; margin-bottom: 50px" >
            <form method="GET" action="index.php">
                <div style="display: inline-block;">
                    <div class="col form-check">
                      <input class="form-check-input" type="radio" name="table_type" value="camera" id="flexRadioDefault1" style="vertical-align: middle; text-align: center; margin-left: -1px;" checked>
                      <label class="form-check-label" for="flexRadioDefault1" style="font-size: 20px">
                      Camera
                      </label>
                    </div>
                </div>
                <div style="display: inline-block;">
                    <div class="col form-check">
                          <input class="form-check-input" type="radio" name="table_type" value="audio" id="flexRadioDefault2" style="vertical-align: bottom; text-align: center; margin-left: -1px;">
                          <label class="form-check-label" for="flexRadioDefault2" style="font-size: 20px">
                            Audio
                          </label>
                    </div>    
                </div>
                <div class="row" style="margin-top: 20px;">
                    <input class="rounded" type="input" name="db_rows" placeholder="1" style="width: 150px; height: 60px; font-size: 22px; margin-left: auto; margin-right: 30px; margin-top: 0; margin-bottom: 10px; display: block; vertical-align: middle; text-align: center;">
                    <input class="btn btn-primary" style="font-size:22px; width: 150px; height: 50px; margin-right: auto; margin-left: 30px; margin-top: 5px; margin-bottom: 40px; vertical-align: middle;" type="submit" value="show">
                </div>
            </form>
            <div>
                <?php
                    switch($_SERVER["REQUEST_METHOD"]){
                        case 'GET':
                            if (!empty($_GET)){
                                if ($_GET["table_type"] == "camera"){
                                    $sql = $conn->prepare("SELECT * FROM ( SELECT * FROM camera ORDER BY id DESC LIMIT ?) sub ORDER BY id ASC");
                                    $sql->bind_param("s", $_GET['db_rows']);
                                    $sql->execute();
                                    $result = $sql->get_result();
                                    echo '<table class="table table-striped table-hover" style="font-size: 18px">'.
                                         '<thead>'.
                                         '<tr>'.
                                         '<th scope="col">id</th>'.
                                         '<th scope="col">time</th>'.
                                         '<th scope="col">number of faces</th>'.
                                         '</tr>'.
                                         '</thead>'.
                                         '<tbody>';
                                    while($row = mysqli_fetch_assoc($result)){
                                        echo '<tr>'.
                                             '<th scope="row">'.$row['id'].'</th>'.
                                             '<td>'.$row['time'].'</td>'.
                                             '<td>'.$row['num_of_faces'].'</td>'.
                                             '</tr>';
                                    }
                                    echo '</tbody>'. 
                                         '</table>';
                                }
                                elseif ($_GET["table_type"] == "audio"){
                                    $sql = $conn->prepare("SELECT * FROM ( SELECT * FROM sound ORDER BY id DESC LIMIT ?) sub ORDER BY id ASC");
                                    $sql->bind_param("s", $_GET['db_rows']);
                                    $sql->execute();
                                    $result = $sql->get_result();
                                    echo '<table class="table table-striped table-hover" style="font-size: 18px">'.
                                         '<thead>'.
                                         '<tr>'.
                                         '<th scope="col">id</th>'.
                                         '<th scope="col">time</th>'.
                                         '<th scope="col">sound amplitude</th>'.
                                         '</tr>'.
                                         '</thead>'.
                                         '<tbody>';
                                    while($row = mysqli_fetch_assoc($result)){
                                        echo '<tr>'.
                                             '<th scope="row">'.$row['id'].'</th>'.
                                             '<td>'.$row['time'].'</td>'.
                                             '<td>'.$row['amplitude'].'</td>'.
                                             '</tr>';
                                    }
                                    echo '</tbody>'. 
                                         '</table>';

                                }
                                $res = $_GET;
                            }else{
                                $res = 'No request';
                            }
                        break;
                    }
                ?>
                
            </div>
        </div>
    </div>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.0-beta1/dist/js/bootstrap.bundle.min.js" integrity="sha384-pprn3073KE6tl6bjs2QrFaJGz5/SUsLqktiwsUTF55Jfv3qYSDhgCecCxMW52nD2" crossorigin="anonymous"></script>
</body>
</html>
