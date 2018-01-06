-- To run this sql script:
-- rm project.db ; sqlite3 < project.sql

---------------------------------------------------------
-- Sqlite can be downloaded from https://sqlite.org/download.html
-- Debian-based linux users run 'apt-get install sqlite3 sqlitebrowser sqlite3-doc'
-- Redhat-based linux users run 'yum install sqlite3 sqlitebrowser sqlite3-doc'
---------------------------------------------------------
-- SQLite is likely used more than all other database engines combined. 
-- Billions and billions of copies of SQLite exist in the wild. 
-- SQLite is found in:
--     Every Android device
--     Every iPhone and iOS device
--     Every Mac
--     Every Windows10 machine
--     Every Firefox, Chrome, and Safari web browser
--     Every instance of Skype
--     Every instance of iTunes
--     Every Dropbox client
--     Every TurboTax and QuickBooks
--     PHP and Python
--     Most television sets and set-top cable boxes
--     Most automotive multimedia systems
--     Countless millions of other applications 

-- Sqlite is an ACID compliant database
--  Atomicity
--  Consistency
--  Isolation
--  Durability
---------------------------------------------------------
-- Sqlite documentation
-- http://www.sqlite.org/docs.html
-- A sqlite3 quick start: http://cs.stanford.edu/people/widom/cs145/sqlite/SQLiteIntro.html
---------------------------------------------------------
.open project.db

PRAGMA foreign_keys = ON;
.headers on
.mode columns

-------------------
-- create schema --
-------------------

CREATE TABLE task (
  taskName           VARCHAR    UNIQUE NOT NULL PRIMARY KEY,
  taskSlots          INTEGER    DEFAULT 1,
  taskPass           VARCHAR    REFERENCES task DEFERRABLE INITIALLY DEFERRED, -- (references table task primary key)
  taskFail           VARCHAR    REFERENCES task DEFERRABLE INITIALLY DEFERRED  -- (references table task primary key)
);

CREATE TABLE item (
  itemName           VARCHAR    UNIQUE NOT NULL PRIMARY KEY,
  itemInstaller      VARCHAR    REFERENCES task,
  itemRemover        VARCHAR    REFERENCES task,
  itemCode           INTEGER    NOT NULL,
  itemDescription    VARCHAR
);

-- foreign keys see: 
-- https://www.sqlite.com/foreignkeys.html
-- http://cs.stanford.edu/people/widom/cs145/sqlite/SQLiteRefIntegrity.html
CREATE TABLE orders (
  orderId            INTEGER    PRIMARY KEY,
  orderCustomer      VARCHAR    NOT NULL,
  orderProduct       VARCHAR    NOT NULL
);

CREATE TABLE orderList (
  orderItem           VARCHAR REFERENCES item,
  orderId             INTEGER,
  FOREIGN KEY(orderId) REFERENCES orders
);


--------------
-- add data --
--------------

BEGIN;
  INSERT INTO task (taskName, taskSlots, taskPass, taskFail) VALUES
    ('INSTALL CPU', 500, 'INSTALL SSD',  'REMOVE CPU'),
    ('REMOVE CPU',  500, 'INSTALL CPU',  NULL),
    ('INSTALL SSD', 500, 'DONE',        'REMOVE SSD'),
    ('REMOVE SSD',  500, 'INSTALL SSD',  NULL),
    ('DONE',        1,   NULL,           NULL),
    ('START',       2,   'INSTALL CPU',  NULL);
COMMIT; -- causes the deferred referential integrity check for taskPass/taskFail to be applied

.print "try to add a task with missing pass/fail task references"
INSERT INTO task (taskName, taskSlots, taskPass, taskFail) VALUES
  ('Bad task',    500, 'missing pass', 'missing fail');

-- Use .width to avoid TEXT and VARCHAR truncating field entries when printing
.width 15 9 15 15
SELECT * FROM task;
.print


INSERT INTO item (itemName, itemInstaller, itemRemover, itemCode, itemDescription) VALUES
  ('I5',             'INSTALL CPU', 'REMOVE CPU', 500, 'Intel I5 CPU'),
  ('I7',             'INSTALL CPU', 'REMOVE CPU', 500, 'Intel I7 CPU'),
  ('Kingston 256GB', 'INSTALL SSD', 'REMOVE SSD', 500, 'Kingston 256GB SSD'),
  ('Kingston 512GB', 'INSTALL SSD', 'REMOVE SSD', 500, 'Kingston 512GB SSD'),
  ('Kingston 1TB',   'INSTALL SSD', 'REMOVE SSD', 500, 'Kingston 1TB SSD');

.print "try to add a order with a missing item references"
INSERT INTO item (itemName, itemInstaller, itemRemover, itemCode, itemDescription) VALUES
  ('I8',             'missing INSTALLER', 'missing REMOVER', 500, 'bad item');
.width 15 15 15 9 50
SELECT * FROM item;
.print

---------------------------------------------------------
-- PROBLEM: automatically figure out orderId:
--      -- We need to know the id and foreign key values.
--      -- A primary key is used as the rowid key for a table.
--      -- last_insert_rowid() returns the rowid key for the last insert.
--      -- Another insert updates last_insert_rowid() to the rowid key for that insert, not the rowid for the other table insert.
--      -- The problem is the command prompt program 'sqlite3' does not support local variables.  
------------------------------------
-- SOLUTION: automatically figure out orderId:
--      -- Use a temporary table to store variable values.
--      -- Insert into orders.
--      -- Fetch last_insert_rowid() and store it in the temporary table.
--      -- Insert (the item, orderId fetched from the temporary table) into orderList.
------------------------------------

CREATE TEMP TABLE IF NOT EXISTS KVList (Key VARCHAR PRIMARY KEY, Value VARCHAR); -- an in-memory table

INSERT INTO orders (orderCustomer,orderProduct)  VALUES('Tom', 'Dual CPU server');
INSERT OR REPLACE INTO KVList (Key,Value) VALUES ('rowid', last_insert_rowid());
INSERT INTO orderList (orderItem,orderId) VALUES 
  ('I7',           (SELECT Value FROM KVList WHERE Key = 'rowid') ),
  ('I7',           (SELECT Value FROM KVList WHERE Key = 'rowid') ),
  ('Kingston 1TB', (SELECT Value FROM KVList WHERE Key = 'rowid') );

INSERT INTO orders (orderCustomer,orderProduct) VALUES('Joe', 'Desktop');
INSERT OR REPLACE INTO KVList (Key,Value) VALUES ('rowid', last_insert_rowid());
INSERT INTO orderList (orderItem,orderId) VALUES 
  ('I7',             (SELECT Value FROM KVList WHERE Key = 'rowid') ),
  ('Kingston 512GB', (SELECT Value FROM KVList WHERE Key = 'rowid') );


INSERT INTO orders (orderCustomer,orderProduct) VALUES('Moe', 'Laptop');
INSERT OR REPLACE INTO KVList (Key,Value) VALUES ('rowid', last_insert_rowid());
INSERT INTO orderList (orderItem,orderId) VALUES 
  ('I5',             (SELECT Value FROM KVList WHERE Key = 'rowid') ),
  ('Kingston 256GB', (SELECT Value FROM KVList WHERE Key = 'rowid') );

.print "try to add a order with a missing item references"
INSERT INTO orders (orderCustomer,orderProduct) VALUES('Toe', 'Laptop');
INSERT OR REPLACE INTO KVList (Key,Value) VALUES ('rowid', last_insert_rowid());
INSERT INTO orderList (orderItem,orderId) VALUES 
  ('I5',             (SELECT Value FROM KVList WHERE Key = 'rowid') ),
  ('Kingston 256GB', (SELECT Value FROM KVList WHERE Key = 'rowid') ),
  ('I6',             (SELECT Value FROM KVList WHERE Key = 'rowid') );

DROP TABLE KVList; -- all done inserting orders.

.width 7 20 20 20 
SELECT orderId, orderCustomer, orderProduct, orderItem
       FROM orders
       JOIN orderList USING ( orderId );
