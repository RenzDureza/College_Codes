<?php
  function change_vowels($name) {
    $modified = "";
    $lower = strtolower($name);
    for ($i = 0; $i < strlen($lower); $i++) {
      $char = $lower[$i];
      $modified .= ($char == 'a' || $char == 'e' || $char == 'i' || $char == 'o' || $char == 'u') ? '@' : $name[$i];
    }
    return $modified;
  }

  function upperclass_first($name) {
    return str_replace($name[0], strtoupper($name[0]), $name);
  }

  $names = [
    "alice",
    "bob",
    "charlie",
    "diana",
    "ethan",
    "fiona",
    "george",
    "hannah",
    "ian",
    "julia",
    "kevin",
    "laura",
    "michael",
    "nina",
    "oliver",
    "paula",
    "quentin",
    "rachel",
    "steven",
    "tina"
  ];
?>

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="style.css">
  <title>MP4_2</title>
</head>
<body>
  <table>
    <tr>
      <th colspan="6">List of names</th>
    </tr>
    <tr>
      <td>Name</td>
      <td>Number of characters</td>
      <td>Uppercase first character</td>
      <td>Replace vowels with @</td>
      <td>Chech position of character 'a'</td>
      <td>Reverse name</td>
    </tr>
    <?php
      foreach ($names as $i) {
        echo "<tr>
          <td>$i</td>
          <td>" . strlen($i) . "</td>
          <td>" . ucfirst($i) . "</td>
          <td>" . change_vowels($i) . "</td>
          <td>" . strpos($i, 'a') . "</td>
          <td>" . strrev($i) . "</td>
        </tr>";
      }
    ?>
  </table>
</body>
</html>
