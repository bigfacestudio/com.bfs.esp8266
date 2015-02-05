<?php


/**
 * Customer Object
 *
 * @author Derek Fan <derek@bbst.org>
 * @date Sept. 18. 2014
 * @URL http://www.bigfacestudio.com
 */
class State implements IDatabaseOperation, IConstants
{

    private $state1;
    
    
    private $db;
    private $db_connection;
    private $_insert_id;

    /**
     * Constructor
     * @param string $fullname
     * @param string $phoneNumber
     * @param string $email
     * @param string $address
     */
    public function __construct($fullname, $phoneNumber, $email, $address)
    {
        $this->db = Database::_getInstance();
        $this->db_connection = $this->db->getConnection();

        $this->fullname = Database::_real_escape_string($fullname);
        $this->phoneNumber = Database::_real_escape_string($phoneNumber);
        $this->email = Database::_real_escape_string($email);
        $this->address = Database::_real_escape_string($address);
    }

    /**
     * Insert self($this) into DB
     * indexed using customer email
     */
    public function insertRecord()
    {

        $sql = "INSERT INTO " . self::TABLENAME_CUSTOMER . "(";
        $sql.=self::DBCOL_CUSTOMER_EMAIL . "," . self::DBCOL_CUSTOMER_OBJ;
        $objCustomerStr = Database::_serialize($this);
        $sql.=") VALUES ( '$this->email', '$objCustomerStr' )";

        $this->db->query($sql);
        $this->_insert_id = $this->db_connection->insert_id;
    }

    /**
     * Delete self($this) from DB
     */
    public function deleteRecord()
    {
        $sql = "DELETE FROM " . self::TABLENAME_CUSTOMER;
        $sql.= " WHERE " . self::DBCOL_ID_INSERT . "= $this->_insert_id ";

        $this->db->query($sql);
    }

    /**
     * Update self($this) in the DB
     */
    public function updateRecord()
    {
        $objCustomerStr = Database::_serialize($this);

        $sql = "UPDATE " . self::TABLENAME_CUSTOMER;
        $sql.= " SET ";
        $sql.= self::DBCOL_CUSTOMER_EMAIL . "='$this->email', ";
        $sql.= self::DBCOL_CUSTOMER_OBJ . " = '$objCustomerStr' ";
        $sql.= " WHERE " . self::DBCOL_ID_INSERT . "= $this->_insert_id ";

        $this->db->query($sql);
    }

    /**
     * populate the <HTML>drop-down-list for all customers.
     */
    public static function _populateDropdownList()
    {
        /* @var $db Database */
        $db = Database::_getInstance();
        $query = "SELECT * FROM " . self::TABLENAME_CUSTOMER;
        /* @var $result mysqli_result */
        $result = $db->query($query);

        echo "<select name='customer_id_dropdown'>";
        echo "<option></option>";

        while ($row = $result->fetch_assoc())
        {
            /* @var $objCustomer Customer */
            $objCustomer = Database::_unserialize($row[self::DBCOL_CUSTOMER_OBJ]);
            $output = "<option value='" . $row[self::DBCOL_ID_INSERT] . "'>";
            $output.= $row[self::DBCOL_ID_INSERT] . " ... " . $objCustomer->getFullname() . " ... " . $objCustomer->getEmail() . " ... " . $objCustomer->getPhoneNumber();
            $output.="</option>";
            echo $output;
        }
        echo "</select>";
        $result->free();
    }

    /**
     * Initialize Customer Table at the begining, execute only once when setting up
     */
    public static function _createTable()
    {
        $db = Database::_getInstance();

        $sql = "CREATE TABLE " . self::TABLENAME_CUSTOMER;
        $id = self::DBCOL_ID_INSERT;
        $sql.= "($id INT NOT NULL AUTO_INCREMENT, PRIMARY KEY($id),";
        $sql.=self::DBCOL_CUSTOMER_EMAIL . " CHAR(50),";
        $sql.=self::DBCOL_CUSTOMER_OBJ . " TEXT )";

        $db->query($sql);
    }

    /**
     * Display all customers in DB as <HTML> Table
     */
    public static function _displayTable()
    {
        $db = Database::_getInstance();

        $query = "SELECT * FROM " . self::TABLENAME_CUSTOMER;
        /* @var $result mysqli_result */
        $result = $db->query($query);
        echo "<table id=table_summary_customer>
                <tr>
                    <th>Customer ID</th>
                    <th>Full Name</th>
                    <th>Phone</th>
                    <th>Email</th>
                    <th>Address</th>
                </tr>";

        while ($row = $result->fetch_assoc())
        {
            /* @var $objCustomer Customer */
            $objCustomer = Database::_unserialize($row[self::DBCOL_CUSTOMER_OBJ]);
            echo "<tr>";
            echo "<td> {$row [self::DBCOL_ID_INSERT]} </td>";
            echo "<td> {$objCustomer->getFullname()} </td>";
            echo "<td> {$objCustomer->getPhoneNumber()} </td>";
            echo "<td> {$objCustomer->getEmail()} </td>";
            echo "<td> {$objCustomer->getAddress()} </td>";
            echo "</tr>";
        }
        echo "</table>";
        $result->free();
    }

    /**
     * Retrive Customer Object from a customer ID
     * @param string $customerId
     * @return Customer
     */
    public static function _getCustomerObj($customerId)
    {
        $db = Database::_getInstance();

        $query = "SELECT * FROM " . self::TABLENAME_CUSTOMER;
        $query .= " WHERE " . self::DBCOL_ID_INSERT . "={$customerId}";

        /* @var $result mysqli_result */
        $result = $db->query($query);
        $row = $result->fetch_assoc(); //only one row should be returned.
        $objCustomer = Database::_unserialize($row[Customer::DBCOL_CUSTOMER_OBJ]);

        $result->free();
        return $objCustomer;
    }

    public function getFullname()
    {
        return $this->fullname;
    }

    public function getPhoneNumber()
    {
        return $this->phoneNumber;
    }

    public function getEmail()
    {
        return $this->email;
    }

    public function getAddress()
    {
        return $this->address;
    }

    public function getInsertId()
    {
        return $this->_insert_id;
    }

    public function setFullname($fullname)
    {
        $this->fullname = Database::_real_escape_string($fullname);
    }

    public function setPhoneNumber($phoneNumber)
    {
        $this->phoneNumber = Database::_real_escape_string($phoneNumber);
    }

    public function setEmail($email)
    {
        $this->email = Database::_real_escape_string($email);
    }

    public function setAddress($address)
    {
        $this->address = Database::_real_escape_string($address);
    }

}//end of class
