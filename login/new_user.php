<?php
function __autoload($class_name)
{
    include "../{$class_name}.inc";
}

if (Login::_DEBUG)
{
    ini_set('display_startup_errors', 1);
    ini_set('display_errors', 1);
    error_reporting(-1);
}
?>

<?php
// START FORM PROCESSING
if (isset($_POST['submit']))
{
    Login::_createUser();
}
?>






<table id="structure">
    <tr>
        <td id="page">
            <h2>Create New User</h2>
<?php if (!empty($message))
{
    echo "<p class=\"message\">" . $message . "</p>";
} ?>
            <?php if (!empty($errors))
            {
                display_errors($errors);
            } ?>
            <form action="new_user.php" method="post">
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
                        <td colspan="2"><input type="submit" name="submit" value="Create" /></td>
                    </tr>
                </table>
            </form>
        </td>
    </tr>
</table>
