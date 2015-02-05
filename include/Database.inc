<?php


/**
 * Database Object
 *
 * @author Derek Fan <derek@bbst.org>
 * @date Sept. 18. 2014
 * @URL http://www.bigfacestudio.com
 */
class Database implements IConstants
{

    private $connection;
    private static $instance;

    /**
     * Constructor.
     */
    public function __construct()
    {
        $this->connection = new mysqli(Database::DB_HOST, Database::DB_USERID, Database::DB_PASSWORD, Database::DB_NAME);
        if (mysqli_connect_error())
        {
            trigger_error('Failed to connect to MySQL: ' . mysqli_connect_error(), E_USER_ERROR);
        }
    }

    /**
     * Empty clone magic method to prevent duplication. 
     */
    private function __clone()
    {
        
    }

    /**
     * Get the mysqli connection. 
     */
    public function getConnection()
    {
        return $this->connection;
    }

    /**
     * query the MySql DB, and check the return result.
     * @param type $sql_query
     * @return mysqli_result
     */
    public function query($sql_query)
    {
        $mysqli_result = $this->getConnection()->query($sql_query);
        $this->checkQueryResult($sql_query, $mysqli_result);
        return $mysqli_result;
    }

    /**
     * Close the current connection
     */
    public function closeConnection()
    {
        mysqli_close($this->connection);
        $this->connection = NULL;
    }

    /**
     * Serialize an object, also encoded by base64
     * @param type $obj
     * @return string
     */
    public static function _serialize($obj)
    {
        return base64_encode(serialize($obj)); // make sure to encode the serialized object
    }

    /**
     * Un-Serialize an object which has been encoded by base64
     * @param string $str
     * @return Object
     */
    public static function _unserialize($str)
    {
        return unserialize(base64_decode($str));
    }

    /**
     * 
     * @param type $inputStr
     * @return trim+real_escape string
     */
    public static function _real_escape_string($inputStr)
    {
        return trim(self::_getInstance()->getConnection()->real_escape_string($inputStr));
    }

    /**
     * Get an instance of the Database.
     * @return Database 
     */
    public static function _getInstance()
    {
        if (!self::$instance)
        {
            self::$instance = new self();
        }
        return self::$instance;
    }

    /**
     * Check query return result for any errors and display corresponding messages
     * @param string $query
     * @param mysqli_result $result
     */
    private function checkQueryResult($query, $result)
    {
        if (Database::_DEBUG)
        {
            /* @var $result mysqli_result */
            if ($result)
            {
                Util::_printConfirmationMessage("Query: <b>{$query} </b> Succeed! {affected_rows={$this->connection->affected_rows}}" . "<br/>");
            }
            else
            {
                Util::_printErrorMessage("Query: <b>{$query} </b> Failed! " . mysqli_error($this->connection) . "<br/>");
            }
        }
    }

}

//end of class
