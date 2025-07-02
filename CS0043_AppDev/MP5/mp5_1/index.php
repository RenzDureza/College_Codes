<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>MP5_1</title>
</head>
<body>
    <div class="container">
        <h2>Using $_POST Method</h2>
        <form method="post" action="<?php echo $_SERVER['PHP_SELF'];?>">
            <label>
                First Name <input type="text" name="fname">
            </label>
            <label>
                Middle Initial <input type="text" name="mname">
            </label>
            <label>
                Last Name <input type="text" name="lname">
            </label>
            <label>
                Date of Birth <input type="date" name="dob">
            </label>
            <label>
                Address <input type="text" name="address">
            </label>
            <input type="submit" value="Submit">
        </form> 
    </div>
    <?php
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $full_name = $_POST['fname'] . ' ' . $_POST['mname'] . '. ' . $_POST['lname'];
            $dob = $_POST['dob'];
            $address = $_POST['address'];
            echo "<div class='display_info'>";
            if (empty($_POST['fname']) && empty($_POST['mname']) && empty($_POST['lname'])) {
                echo "A part of name is missing";
            } elseif (empty($address)) {
                echo "Please include your address";
            } else {
                echo "<table>";
                echo "<tr><td><strong>Full Name:</strong></td><td>" . $full_name . "</td></tr>";
                echo "<tr><td><strong>Date of Birth:</strong></td><td>" . $dob . "</td></tr>";
                echo "<tr><td><strong>Address:</strong></td><td>" . $address . "</td></tr>";  
                echo "</table>";
            }
            echo "</div>";
        }
    ?>
        
    <div class="container">
        <h2>Using $_GET Method</h2>
        <form method="get" action="<?php echo htmlspecialchars($_SERVER['PHP_SELF']); ?>">
            <label>
                First Name <input type="text" name="fname_get">
            </label>
            <label>
                Middle Initial <input type="text" name="mname_get">
            </label>
            <label>
                Last Name <input type="text" name="lname_get">
            </label>
            <label>
                Date of Birth <input type="date" name="dob_get">
            </label>
            <label>
                Address <input type="text" name="address_get">
            </label>
            <input type="submit" value="Submit">
        </form>

        <?php
        if ($_SERVER["REQUEST_METHOD"] == "GET" && isset($_GET['fname_get'])) {
            $fname = trim($_GET['fname_get']);
            $mname = trim($_GET['mname_get']);
            $lname = trim($_GET['lname_get']);
            $dob = $_GET['dob_get'];
            $address = trim($_GET['address_get']);
            $middle = !empty($mname) ? $mname . '. ' : '';
            $full_name = $fname . ' ' . $middle . $lname;

            echo "<div class='display_info'>";
            if (empty($fname) || empty($lname)) {
                echo "A part of name is missing (GET)";
            } elseif (empty($address)) {
                echo "Please include your address (GET)";
            } else {
                echo "<table>";
                echo "<tr><td><strong>Full Name:</strong></td><td>" . htmlspecialchars($full_name) . "</td></tr>";
                echo "<tr><td><strong>Date of Birth:</strong></td><td>" . htmlspecialchars($dob) . "</td></tr>";
                echo "<tr><td><strong>Address:</strong></td><td>" . htmlspecialchars($address) . "</td></tr>";
                echo "</table>";
            }
            echo "</div>";
        }
        ?>
    </div>
</body>
</html>