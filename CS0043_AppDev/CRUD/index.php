<html>
<head>
    <title>Login</title>
</head>
<body>
    <h2>Login Page</h2>

    <?php
    if (isset($_GET['error'])) {
        echo "<p style='color:red;'>".$_GET['error']."</p>";
    }
    ?>

    <form action="login.php" method="post">
        Username: <input type="text" name="username" required><br><br>
        Password: <input type="password" name="password" required><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>