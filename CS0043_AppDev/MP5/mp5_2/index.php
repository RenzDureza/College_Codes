<?php
setcookie("firstname", "Aldrin", time() + 3600);
setcookie("middlename", "Sangil", time() + 3600);
setcookie("lastname", "Dureza", time() + 3600);
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Personal Info with Cookies</title>
    <style>
        .cookie {
            font-size: 20px;
            margin-top: 10px;
            display: none;
        }
    </style>
</head>
<body>
    <h1>Welcome to My Personal Info Page</h1>
    <p>Cookies will be shown after 10, 20, and 30 seconds.</p>

    <div id="firstname" class="cookie"></div>
    <div id="middlename" class="cookie"></div>
    <div id="lastname" class="cookie"></div>

    <script>
        
        function getCookie(name) {
            const value = "; " + document.cookie;
            const parts = value.split("; " + name + "=");
            if (parts.length === 2) return parts.pop().split(";").shift();
        }

        
        setTimeout(() => {
            document.getElementById("firstname").textContent = "Firstname: " + getCookie("firstname");
            document.getElementById("firstname").style.display = "block";
        }, 10000); 

        setTimeout(() => {
            document.getElementById("middlename").textContent = "Middlename: " + getCookie("middlename");
            document.getElementById("middlename").style.display = "block";
        }, 20000); 

        setTimeout(() => {
            document.getElementById("lastname").textContent = "Lastname: " + getCookie("lastname");
            document.getElementById("lastname").style.display = "block";
        }, 30000); 
    </script>
</body>
</html>