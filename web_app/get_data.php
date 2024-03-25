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

// Query to fetch latest water level
$sql = "SELECT level FROM water_level ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
  // Output data of each row
  $row = $result->fetch_assoc();
  echo $row["level"];
} else {
  echo "0";
}

$conn->close();
?>
