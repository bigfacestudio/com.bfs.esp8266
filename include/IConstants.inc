<?php


/**
 * Description of Constants
 *
 * @author bfan
 */

interface IConstants
{

    /**
     * Global Debug tag
     */
//    const _DEBUG = False;
    const _DEBUG = TRUE;

    /**
     * Database.inc
     */
    const DB_HOST = "localhost";
    const DB_USERID = "root";
    const DB_PASSWORD = "bobosoft";
    const DB_NAME = "create_vip";
//    const DB_HOST = "";
//    const DB_USERID = "";
//    const DB_PASSWORD = "";
//    const DB_NAME = "";


    /* All table */
    const DBCOL_ID_INSERT = "ID";
    
    
    const TABLENAME_CUSTOMER = "customers";
    const TABLENAME_PROJECT = "projects";
    const TABLENAME_VIP = "vips";
    const TABLENAME_LOGIN = "logins";


    /* table vips */
    //   const DBCOL_VIP_PROJECT_ID = 'ProjectID';
    const DBCOL_VIP_OBJ = 'ObjVip';

    /* table customers */
    const DBCOL_CUSTOMER_EMAIL = "Email";
    const DBCOL_CUSTOMER_OBJ = "ObjCustomer";
//    const DBCOL_CUSTOMER_FULLNAME = "FullName";
//    const DBCOL_CUSTOMER_PHONE = "Phone";
//    const DBCOL_CUSTOMER_ADDRESS = "Address";



    /**
     * Login.inc
     */
    const LOGIN_USERNAME = "username";
    const LOGIN_PASSWORD = "password";
    const DBCOL_LOGIN_USERNAME = "username";
    const DBCOL_LOGIN_PASSWORD_HASHED = "hashedPassword";
    const LOGIN_PAGE = "util/login/login.php";
    const LOGIN_REDIRECT_PAGE = "../../admin_console.php";

}
