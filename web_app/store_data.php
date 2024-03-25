<?php
$servername = "localhost";
$username = "your_username";
$password = "your_password";
$dbname = "your_database";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Get water level from POST data
$waterLevel = $_POST["water_level"];

// Insert data into database
$sql = "INSERT INTO water_level (level) VALUES ('$waterLevel')";
if ($conn->query($sql) === TRUE) {
  echo "Data stored successfully";
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
?>
