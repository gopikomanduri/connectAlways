/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

DROP TABLE IF EXISTS `UserProfile`;

CREATE TABLE `UserProfile` (
  `userId` VARCHAR(255) NOT NULL PRIMARY KEY,
  `userName` TEXT NULL,
  `emailId` TEXT NULL,
  `phoneNumber` BIGINT UNSIGNED NULL)
 ENGINE=InnoDB;

