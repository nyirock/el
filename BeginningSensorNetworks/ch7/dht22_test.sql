CREATE DATABASE dht22_test;

use dht22_test;

mysql> CREATE TABLE dht22_test.temp_humid (
 `id` int(11) NOT NULL AUTO_INCREMENT,
 `temp_c` float DEFAULT NULL,
 `rel_humid` float DEFAULT NULL,
 PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
 ;