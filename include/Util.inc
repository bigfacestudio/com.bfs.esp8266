<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 * Description of Util
 *
 * @author bfan
 */
class Util
{

    public static function _getHTMLNameTag($nameTag)
    {
        echo 'name="' . $nameTag . '"';
    }

    public static function _filterInputPOST($name)
    {
        return filter_input(INPUT_POST, $name);
    }

    public static function _printErrorMessage($msg)
    {
        printf("<font color = 'red'> %s </font> <br/>", $msg);
    }

    public static function _printConfirmationMessage($msg)
    {
        printf("<font color = 'green'> %s </font> <br/>", $msg);
    }
    
    public static function _formateErrorMessage($msg)
    {
        return "<font color = 'red'> {$msg} </font> <br/>";
    }

    public static function _formateConfirmationMessage($msg)
    {
        return "<font color = 'green'> {$msg} </font> <br/>";
    }
    
    

    /**
     * For dubug using only
     * @param unknown_type $msg
     * @param unknown_type $var
     */
    public static function _debug_print($msg, $var)
    {
        echo $msg . " :::: " . $var;
        echo "<br/>";
    }

    public static function debug_print_r($msg, $arr)
    {
        echo $msg . " ::::  <br/>";

        echo "<pre>";
        print_r($arr);
        echo "<pre/>";

        echo "<br/>";
    }

    public static function _var_export($obj)
    {
        echo "<tt><pre>" . var_export($obj, TRUE) . "</pre></tt>";
    }

    public static function _redirectTo($url = NULL)
    {
        if ($url != NULL)
        {
            header("Location: {$url}");
//            exit();
        }
    }

    /**
     * 
     * @param array $requiredFieldsNameTags 'tagname' => 'Field Name'
     * @return array
     */
    public static function _validateRequiredFields(array $requiredFieldsNameTags)
    {
        $field_errors = array();
        foreach ($requiredFieldsNameTags as $tag => $value)
        {
            if (!isset($_POST[$tag]) || ($_POST[$tag] == ''))
            {
                $field_errors[$tag] = $tag;
            }
        }
        return $field_errors;
    }

    /**
     * NOT IN USED
     */
    private function getRoot()
    {
        $root = (!empty($_SERVER['HTTPS']) ? 'https' : 'http') . '://' . $_SERVER['HTTP_HOST'] . '/';
        echo $root;


        $domain = $_SERVER['HTTP_HOST'];
        $docRoot = $_SERVER['DOCUMENT_ROOT'];
        $dirRoot = dirname(__FILE__);
        $protocol = isset($_SERVER["HTTPS"]) ? 'https://' : 'http://';
//$urlDir = str_replace('/include', '/',str_replace($docRoot, '', $dirRoot));
        $urlDir = str_replace($docRoot, '', $dirRoot);
        $site_path = $protocol . $domain . $urlDir;

        echo "<br>" . $site_path;
    }

}

//end of class
