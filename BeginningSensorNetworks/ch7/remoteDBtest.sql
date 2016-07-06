use dht22;

CREATE TABLE temp_humid_2sensors_timestamp (
 `id` int(11) NOT NULL AUTO_INCREMENT,
 `event_date` timestamp,
 `temp_c1` float DEFAULT NULL,
 `rel_humid1` float DEFAULT NULL,
 `temp_c2` float DEFAULT NULL,
 `rel_humid2` float DEFAULT NULL,
 PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
 ;