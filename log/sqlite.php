<?php
        $dbhandle = sqlite_open('log');

        if ($dbhandle == false)
        {
                die ('Unable to open database');
        }
         else 
         {
                echo 'Database created.';
        }

        $dbquery = ' SELECT * FROM tbl1';

        $dbresult = sqlite_query($dbhandle, $dbquery);

        while (sqlite_has_more($dbresult))
        {
                $dbrow = sqlite_fetch_single($dbquery);
                print_r ($dbrow);
        }

        sqlite_close($dbhandle);
?>
