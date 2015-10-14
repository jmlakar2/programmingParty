
<?php
if (isset($_GET['yes'])) {
    $fp = fopen("detection.txt", 'w') or die ("Can't open file");
    fwrite($fp, "yes");
}

if (isset($_GET['no'])) {
    $fp = fopen("detection.txt", 'w') or die ("Can't open file");
    fwrite($fp, "no");
}
