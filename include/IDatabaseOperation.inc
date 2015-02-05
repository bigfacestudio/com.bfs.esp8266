<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 * Description of DatabaseOperation
 *
 * @author bfan
 */
interface  IDatabaseOperation{
    
    
    

    
    public function insertRecord();
    public function updateRecord();
    public function deleteRecord();
    
    public function getInsertId();
    
    
    public static function _createTable(); 
    public static function _displayTable();
    
}
