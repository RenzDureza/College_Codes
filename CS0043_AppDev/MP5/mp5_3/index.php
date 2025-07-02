<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>MP5_3</title>
</head>
<body>
    <div class="container">
        <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
            <label>Favorite Color 1: <input type="text" name="col1"></label>
            <label>Favorite Color 2: <input type="text" name="col2"></label>
            <label>Favorite Color 3: <input type="text" name="col3"></label>
            <label>Favorite Color 4: <input type="text" name="col4"></label>
            <label>Favorite Color 5: <input type="text" name="col5"></label>
            <input type="submit" value="Submit">
        </form>

        <?php
        if ($_SERVER['REQUEST_METHOD'] == 'POST') {
            $colors = [
                $_POST['col1'],
                $_POST['col2'],
                $_POST['col3'],
                $_POST['col4'],
                $_POST['col5']
            ];

            if (in_array('', $colors)) {
                echo "<p style='color:red;'>Fill all the inputs</p>";
            } else {
                echo "<table class='fav_col'>";
                echo "<tr><th colspan=3>My Favorite Colors</th></tr>";
                echo "<tr><th>Label</th><th>Color Name</th><th>Color Preview</th></tr>";

                foreach ($colors as $index => $color) {
                    $label = "Favorite Color " . ($index + 1);
                    echo "<tr>";
                    echo "<td>$label</td>";
                    echo "<td>" . htmlspecialchars($color) . "</td>";
                    echo "<td><span class='color-box' style='background-color: " . htmlspecialchars($color) . ";'></span></td>";
                    echo "</tr>";
                }

                echo "</table>";
            }
        }
        ?>
    </div>
</body>
</html>