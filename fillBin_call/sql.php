<?php
$servername = "localhost";
$username = "root";
$password = "";
$database = "smart_trash_bin";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $database);

$mysqli_query = "SELECT BinID FROM fill_level where status = 1";

$result = mysqli_query($conn, $mysqli_query);

while($row = mysqli_fetch_assoc($result)){
    $jsonresult[] = $row;
}
print(json_encode($jsonresult));

mysqli_close($conn);
?>
