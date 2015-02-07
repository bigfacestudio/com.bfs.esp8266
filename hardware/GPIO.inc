<?php


/**
 * Customer Object
 *
 * @author Derek Fan <derek@bbst.org>
 * @date Sept. 18. 2014
 * @URL http://www.bigfacestudio.com
 */
class GPIO implements IConstants
{

    const STATE_ON = "ON";
    const STATE_OFF = "OFF";

    private $name="";


    private $state1;
    private $db;
    private $db_connection;
    private $_insert_id;

    
    private static $_instance;
    
    
    /**
     * Constructor
     * @param string $fullname
     * @param string $phoneNumber
     * @param string $email
     * @param string $address
     */
    public function __construct($stat)
    {
        $this->db = Database::_getInstance();
        $this->db_connection = $this->db->getConnection();

        $this->state1 = Database::_real_escape_string($stat);
    }
    
    
     /**
     * Get an instance of the Database.
     * @return Database 
     */
    public static function _getInstance()
    {
        if (!self::$_instance)
        {
            self::$_instance = new self();
        }
        return self::$_instance;
    }


    /**
     * Insert self($this) into DB
     * indexed using customer email
     */
    private function insertRecord()
    {

        $sql = "INSERT INTO " . self::TABLENAME_STATE . "(";
        $sql.=self::DBCOL_STATE_1;
//        $objCustomerStr = Database::_serialize($this);
        $sql.=") VALUES ( '$this->state1' )";

        $this->db->query($sql);
        $this->_insert_id = $this->db_connection->insert_id;
    }

    /**
     * Delete self($this) from DB
     */
    private function deleteRecord()
    {
        $sql = "DELETE FROM " . self::TABLENAME_STATE;
        $sql.= " WHERE " . self::DBCOL_ID_INSERT . "= $this->_insert_id ";

        $this->db->query($sql);
    }

    /**
     * Update self($this) in the DB
     */
    private function updateRecord()
    {
        //$objCustomerStr = Database::_serialize($this);

        $sql = "UPDATE " . self::TABLENAME_STATE;
        $sql.= " SET ";
        $sql.= self::DBCOL_STATE_1 . "='$this->state1'";
//        $sql.= self::DBCOL_CUSTOMER_OBJ . " = '$objCustomerStr' ";
//        $sql.= " WHERE " . self::DBCOL_ID_INSERT . "= $this->_insert_id ";

        $this->db->query($sql);
    }

    /**
     * Initialize Customer Table at the begining, execute only once when setting up
     */
    public static function _createTable()
    {
        $db = Database::_getInstance();

        $sql = "CREATE TABLE " . self::TABLENAME_STATE;
        $id = self::DBCOL_ID_INSERT;
        $sql.= " ($id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY($id),";
        //sql.=self::DBCOL_CUSTOMER_EMAIL . " CHAR(50),";
        $sql.=self::DBCOL_STATE_1 . " CHAR(10))";

        $db->query($sql);
    }

   

    
    public function queryState()
    {
        $sql = "SELECT * FROM " . self::TABLENAME_STATE;

        $result = $this->db->query($sql);
        if ($result->num_rows == 0)
        {
            $this->state1 = self::STATE_OFF;
            $this->insertRecord();

            $sql = "SELECT * FROM " . self::TABLENAME_STATE;
            $result = $this->db->query($sql);
        }


        $row = $result->fetch_assoc();

         $this->state1 = $row [self::DBCOL_STATE_1];
         return  $this->state1 ;
    }

    public function toggleState()
    {
        $this->queryState();
             
        if ($this->state1 == self::STATE_OFF)
        {
            $this->state1 = self::STATE_ON;
        }
        else
        {
            $this->state1 = self::STATE_OFF;
        }
        $this->updateRecord();
        
       return $this->state1;
    }

}

//end of class
