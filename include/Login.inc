<?php


/**
 * Description of Login
 *
 * @author bfan
 */
class Login implements IConstants
{

    public static function _isLogin()
    {
        if (!isset($_SESSION))
        {
            session_start();
        }

        if (isset($_SESSION[self::LOGIN_USERNAME]))
        {
            return true;
        }
        return false;
    }

    /**
     * Check whether an user if logged in
     * If not logged in, will redirect to the login page
     */
    public static function _confirmLogin()
    {
        if (!self::_isLogin())
        {
            Util::_redirectTo(self::LOGIN_PAGE);
        }
    }

    /**
     * login 
     * Automatically retrieve username (Login::LOGIN_USERNAME) and password (Login::LOGIN_PASSWORD) from _POST[]
     */
    public static function _login()
    {
        if (!isset($_SESSION))
        {
            session_start();
        }

        $db = Database::_getInstance();
        $errors = array();

        // perform validations on the form data
        $required_fields = array(
            self::LOGIN_USERNAME=>self::LOGIN_USERNAME,
            self::LOGIN_PASSWORD=>self::LOGIN_PASSWORD
        );
        $errors = array_merge($errors, Util::_validateRequiredFields($required_fields));

        $username = Database::_real_escape_string(Util::_filterInputPOST(self::LOGIN_USERNAME));
        $password = Database::_real_escape_string(Util::_filterInputPOST(self::LOGIN_PASSWORD));
        $hashedPassword = sha1($password);

        if (count($errors) == 0)
        {
            // Check database to see if username and the hashed password exist there.
            $query = "SELECT " . self::DBCOL_LOGIN_USERNAME;
            $query .= " FROM " . self::TABLENAME_LOGIN;
            $query .= " WHERE " . self::DBCOL_LOGIN_USERNAME . "= '{$username}' ";
            $query .= " AND " . self::DBCOL_LOGIN_PASSWORD_HASHED . " = '{$hashedPassword}' ";
            $query .= " LIMIT 1";

            /* @var $result mysqli_result */
            $result = $db->query($query);

            if ($result->num_rows == 1)
            {
                // username/password authenticated
                // and only 1 match
                $found_user = $result->fetch_assoc();

                echo ">>2";
                // Store in a session
                // $_SESSION['user_id'] = $found_user['id'];
                $_SESSION[self::LOGIN_USERNAME] = $found_user[self::DBCOL_LOGIN_USERNAME];

                Util::_redirectTo(self::LOGIN_REDIRECT_PAGE);
            }
            else
            {
                // username/password combo was not found in the database
                Util::_printErrorMessage("Username/password combination incorrect, Please try it again.");
            }
        }
        else
        {
            Util::_printErrorMessage("Error(s) in the form");
        }
    }

    public static function _createUser()
    {
        $db = Database::_getInstance();
        $errors = array();

        // perform validations on the form data
        $required_fields = array(
            self::LOGIN_USERNAME=>self::LOGIN_USERNAME,
            self::LOGIN_PASSWORD=>self::LOGIN_PASSWORD
        );
        $errors = Util::_validateRequiredFields($required_fields);
        $username = Database::_real_escape_string(Util::_filterInputPOST(self::LOGIN_USERNAME));
        $password = Database::_real_escape_string(Util::_filterInputPOST(self::LOGIN_PASSWORD));
        $hashedPassword = sha1($password);

        Util::_var_export($errors);
        Util::_var_export($_POST);

        if (count($errors) == 0)
        {
            $dbcol_username = self::DBCOL_LOGIN_USERNAME;
            $dbcol_password_hased = self::DBCOL_LOGIN_PASSWORD_HASHED;

            $query = "INSERT INTO " . self::TABLENAME_LOGIN;
            $query .= "({$dbcol_username}, {$dbcol_password_hased}) ";
            $query .= "VALUES ('{$username}', '{$hashedPassword}')";

            $db->query($query);
        }
        else
        {
            Util::_printErrorMessage("Error(s) in the form");
        }
    }

    public static function _createTable()
    {
        $db = Database::_getInstance();

        $sql = "CREATE TABLE " . self::TABLENAME_LOGIN;
        $id = self::DBCOL_ID_INSERT;
        $sql.= "($id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY($id),";
        $sql.=self::DBCOL_LOGIN_USERNAME . " CHAR(20),";
        $sql.=self::DBCOL_LOGIN_PASSWORD_HASHED . " CHAR(60) )";

        $db->query($sql);
    }

}

//end of class
