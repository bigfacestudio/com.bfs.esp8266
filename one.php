<?php

function __autoload($class_name)
{
    include "./include/{$class_name}.inc";
}

include './hardware/GPIO.inc';


$gpio = GPIO::_getInstance();

if (array_key_exists('state', $_GET))
{
    printf($gpio->queryState());
}
else
{
    ?>


    <form id="swtich" action="<?php $_SERVER["PHP_SELF"] ?>" method="post">
        <input class="button buzz-out color-red size_up"  name="switch"  type="submit" value="Switch"> <br/>
    </form>

    <?php
    if(filter_input(INPUT_POST, "switch"))
    {
       $state=  $gpio->toggleState();
        printf("Current State >>> %s", $state);
        
    }
    else
    {
        printf("Welcome to the ESP8266 switch board");
    }
    
}
?>


