CREATE DATABASE PANA;

USE PANA;

CREATE TABLE `image` (
    `id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY ,
    `url` VARCHAR( 127 ) NOT NULL ,
    INDEX ( `id` )
);

INSERT INTO image VALUES (1,'images/Big_ben_equirectangular.jpg');
INSERT INTO image VALUES (2,'images/Earthmap720x360_grid.jpg');
INSERT INTO image VALUES (3,'Land_shallow_topo_2048.jpg');