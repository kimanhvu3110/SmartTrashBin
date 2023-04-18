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
$fill_percentage = $_GET['fill_percentage']; 

$sql = "INSERT INTO fill_level_history(BinID, fill_percentage) 
        VALUES ('$BinID', '$fill_percentage');"; 

if ($conn->query($sql) === TRUE) {
    echo "sensorvaluetb updated successfully";
} else {
    echo "Error updating record: " . $conn->error;
}

$conn->close();
?>
