use dht22_test;

CREATE TABLE dht22_test.temp_humid_twosensors (
 `id` int(11) NOT NULL AUTO_INCREMENT,
 `temp_c1` float DEFAULT NULL,
 `rel_humid1` float DEFAULT NULL,
 `temp_c2` float DEFAULT NULL,
 `rel_humid2` float DEFAULT NULL,
 PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
 ;