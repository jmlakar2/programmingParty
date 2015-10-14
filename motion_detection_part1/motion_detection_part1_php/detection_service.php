<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

$fp = fopen("state.txt", 'r') or die ("Can't open file");
$content = fread($fp, filesize("state.txt"));
echo $content;
fclose($fp);