<?php
if (Login::_DEBUG)
{
    ini_set('display_startup_errors', 1);
    ini_set('display_errors', 1);
    error_reporting(-1);
}

function __autoload($class_name)
{
    include "../{$class_name}.inc";
}
?>


<?php
if (Login::_isLogin())
{
    Util::_redirectTo(Login::LOGIN_REDIRECT_PAGE);
}

// START FORM PROCESSING
if (isset($_POST['submit']))
{ // Form has been submitted.
    Login::_login();
}

else
{ // Form has not been submitted.
    if (isset($_GET['logout']) && $_GET['logout'] == 1)
    {
        $message = "You are now logged out.";
    }
}
?>



<!DOCTYPE html>
<html>
    <head>
        <title>BFS Login</title>
    </head>
    <body>

        <table id="structure">
            <tr>
                <td id="page">
                    <h2>Login</h2>
                    <?php
                    if (!empty($message))
                    {
                        echo "<p class=\"message\">" . $message . "</p>";
                    }
                    ?>
                    <?php
                    if (!empty($errors))
                    {
                        display_errors($errors);
                    }
                    ?>
                    <form action="login.php" method="post">
                        <table>
                            <tr>
                                <td>Username:</td>
                                <td><input type="email" <?php Util::_getHTMLNameTag(Login::LOGIN_USERNAME) ?> maxlength="30"
                                           placeholder="Email Address" /></td>
                            </tr>
                            <tr>
                                <td>Password:</td>
                                <td><input type="password" <?php Util::_getHTMLNameTag(Login::LOGIN_PASSWORD) ?> maxlength="30"
                                           placeholder="Password" /></td>
                            </tr>
                            <tr>
                                <td colspan="2"><input type="submit" name="submit" value="Login" /></td>
                            </tr>
                        </table>
                    </form>
                </td>
            </tr>
        </table>

    </body>
</html>