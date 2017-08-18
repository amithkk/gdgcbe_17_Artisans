<?php
    session_start();

    if(isset($_SESSION['id'])) {
        $username = $_SESSION['username'];
        $userId = $_SESSION['id'];
        //echo "Welcome, {$username}!";
    } else {
        header('Location: index.php');
        die();
    }

?>
<!DOCTYPE html>
<html >
<head>
  <meta charset="UTF-8">
  <title>Welcome To IoT Pod Console</title>
  
  </script>
</head>

<body>

  <script src='http://cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js'></script>
<script src='http://cdnjs.cloudflare.com/ajax/libs/modernizr/2.8.3/modernizr.min.js'></script>

    <script src="js/index_landing.js"></script>
</body>
</html>
