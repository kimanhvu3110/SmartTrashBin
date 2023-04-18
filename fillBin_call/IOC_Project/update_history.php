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
 
$UserID  = $_GET['UserID']; 
$OrganicWaste_kg = $_GET['OrganicWaste_kg']; 
$InorganicWaste_kg = $_GET['InorganicWaste_kg']; 

$sql = "INSERT into history(UserID, OrganicWaste_kg	, InorganicWaste_kg) 
        values('$UserID','$OrganicWaste_kg','$InorganicWaste_kg')"; 

if ($conn->query($sql) === TRUE) {
    echo "sensorvaluetb updated successfully";
} else {
    echo "Error updating record: " . $conn->error;
}

$conn->close();
?>
