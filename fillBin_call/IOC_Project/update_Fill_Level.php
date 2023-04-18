<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "smart_trash_bin";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
 
$BinID  = $_GET['BinID']; 
$Fill_Level = $_GET['Fill_Level']; 

$sql = "UPDATE fill_level
        SET Fill_Level = '$Fill_Level'
        WHERE BinID = $BinID;"; 

if ($conn->query($sql) === TRUE) {
    echo "sensorvaluetb updated successfully";
} else {
    echo "Error updating record: " . $conn->error;
}

$conn->close();
?>
