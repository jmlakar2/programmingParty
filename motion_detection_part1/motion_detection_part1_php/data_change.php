<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
if (isset($_GET['on'])) {
    $fp = fopen("state.txt", 'w') or die ("Can't open file");
    fwrite($fp, "TUON");
}

if (isset($_GET['off'])) {
    $fp = fopen("state.txt", 'w') or die ("Can't open file");
    fwrite($fp, "TUOF");
}

fclose($fp);

$adress = 'index.php';
header ("Location: $adress");