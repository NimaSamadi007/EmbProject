<html>
<head>
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <title>Emb Project Web Server</title>
</head>
<body>
    <div>
        <div style="width:40%; border:solid 1px black; margin-left:auto; margin-right:auto; padding:10px;">
            <form method="GET" action="index.php">
                Update image:
                <input type="hidden" name="update" value="true">
                <input type="submit">
            </form>
            <hr/>
        </div>
    </div>
    <div>
        <img src="./img.jpg">
    </div>
    <?php
        switch($_SERVER["REQUEST_METHOD"]){
            case 'GET':
                if (!empty($_GET)){
                    if ($_GET["update"] == "true"){
                        print_r("Updating image...");
                    }
                    $res = $_GET;
                }else{
                    $res = 'No request';
                }
            break;
        }
    ?>
</body>
</html>
