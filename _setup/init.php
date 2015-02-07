<?php


function __autoload($class_name)
{
    include "../include/{$class_name}.inc";
}


include '../hardware/GPIO.inc';




if (IConstants::_DEBUG)
{
    ini_set('display_startup_errors', 1);
    ini_set('display_errors', 1);
    error_reporting(-1);
}
?>

<?php

GPIO::_createTable();

?>