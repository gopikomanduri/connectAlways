//
// MySQLTest.cpp
//
// $Id: //poco/1.4/Data/MySQL/testsuite/src/MySQLTest.cpp#1 $
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "MySQLTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/String.h"
#include "Poco/Format.h"
#include "Poco/Exception.h"
#include "Poco/Data/Common.h"
#include "Poco/Data/BLOB.h"
#include "Poco/Data/StatementImpl.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include <iostream>


using namespace Poco::Data;
using Poco::Data::MySQL::ConnectionException;
using Poco::Data::MySQL::StatementException;
using Poco::format;
using Poco::NotFoundException;


Poco::SharedPtr<Poco::Data::Session> MySQLTest::_pSession = 0;
Poco::SharedPtr<SQLExecutor> MySQLTest::_pExecutor = 0;


// Parameters for barebone-test
#define MYSQL_USER "root"
#define MYSQL_PWD  "penfish336"
#define MYSQL_HOST "localhost"
#define MYSQL_PORT 3306
#define MYSQL_DB   "test"


// Connection string to POCO
std::string MySQLTest::_dbConnString = "user=root;password=penfish336;db=test;compress=true;auto-reconnect=true";


MySQLTest::MySQLTest(const std::string& name): 
	CppUnit::TestCase(name)
{
	static bool beenHere = false;
	MySQL::Connector::registerConnector();

	if (!beenHere)
	{
		try
		{
			_pSession = new Session(SessionFactory::instance().create(MySQL::Connector::KEY, _dbConnString));
		}catch (ConnectionException& ex)
		{
			std::cout << "!!! WARNING: Connection failed. MySQL tests will fail !!!" << std::endl;
			std::cout << ex.displayText() << std::endl;
		}

		if (_pSession && _pSession->isConnected()) 
			std::cout << "*** Connected to " << '(' << _dbConnString << ')' << std::endl;
		if (!_pExecutor) _pExecutor = new SQLExecutor("MySQL SQL Executor", _pSession);
	}

	beenHere = true;
}


MySQLTest::~MySQLTest()
{
	MySQL::Connector::unregisterConnector();
}


void MySQLTest::testBareboneMySQL()
{
	if (!_pSession) fail ("Test not available.");

	std::string tableCreateString = "CREATE TABLE Test "
		"(First VARCHAR(30),"
		"Second VARCHAR(30),"
		"Third VARBINARY(30),"
		"Fourth INTEGER,"
		"Fifth FLOAT)";

	_pExecutor->bareboneMySQLTest(MYSQL_HOST, MYSQL_USER, MYSQL_PWD, MYSQL_DB, MYSQL_PORT, tableCreateString.c_str());
}


void MySQLTest::testSimpleAccess()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->simpleAccess();
}


void MySQLTest::testComplexType()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->complexType();
}


void MySQLTest::testSimpleAccessVector()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->simpleAccessVector();
}


void MySQLTest::testComplexTypeVector()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->complexTypeVector();
}


void MySQLTest::testInsertVector()
{
	if (!_pSession) fail ("Test not available.");

	recreateStringsTable();
	_pExecutor->insertVector();
}


void MySQLTest::testInsertEmptyVector()
{
	if (!_pSession) fail ("Test not available.");

	recreateStringsTable();
	_pExecutor->insertEmptyVector();
}


void MySQLTest::testInsertSingleBulk()
{
	if (!_pSession) fail ("Test not available.");

	recreateIntsTable();
	_pExecutor->insertSingleBulk();
}


void MySQLTest::testInsertSingleBulkVec()
{
	if (!_pSession) fail ("Test not available.");

	recreateIntsTable();
	_pExecutor->insertSingleBulkVec();
}


void MySQLTest::testLimit()
{
	if (!_pSession) fail ("Test not available.");

	recreateIntsTable();
	_pExecutor->limits();
}


void MySQLTest::testLimitZero()
{
	if (!_pSession) fail ("Test not available.");

	recreateIntsTable();
	_pExecutor->limitZero();
}


void MySQLTest::testLimitOnce()
{
	if (!_pSession) fail ("Test not available.");

	recreateIntsTable();
	_pExecutor->limitOnce();
	
}


void MySQLTest::testLimitPrepare()
{
	if (!_pSession) fail ("Test not available.");

	recreateIntsTable();
	_pExecutor->limitPrepare();
}



void MySQLTest::testPrepare()
{
	if (!_pSession) fail ("Test not available.");

	recreateIntsTable();
	_pExecutor->prepare();
}


void MySQLTest::testSetSimple()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->setSimple();
}


void MySQLTest::testSetComplex()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->setComplex();
}


void MySQLTest::testSetComplexUnique()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->setComplexUnique();
}

void MySQLTest::testMultiSetSimple()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->multiSetSimple();
}


void MySQLTest::testMultiSetComplex()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->multiSetComplex();
}


void MySQLTest::testMapComplex()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->mapComplex();
}


void MySQLTest::testMapComplexUnique()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->mapComplexUnique();
}


void MySQLTest::testMultiMapComplex()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->multiMapComplex();
}


void MySQLTest::testSelectIntoSingle()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->selectIntoSingle();
}


void MySQLTest::testSelectIntoSingleStep()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->selectIntoSingleStep();
}


void MySQLTest::testSelectIntoSingleFail()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->selectIntoSingleFail();
}


void MySQLTest::testLowerLimitOk()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->lowerLimitOk();
}


void MySQLTest::testSingleSelect()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->singleSelect();
}


void MySQLTest::testLowerLimitFail()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->lowerLimitFail();
}


void MySQLTest::testCombinedLimits()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->combinedLimits();
}


void MySQLTest::testRange()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->ranges();
}


void MySQLTest::testCombinedIllegalLimits()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->combinedIllegalLimits();
}



void MySQLTest::testIllegalRange()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->illegalRange();
}


void MySQLTest::testEmptyDB()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonTable();
	_pExecutor->emptyDB();
}


void MySQLTest::testBLOB()
{
	if (!_pSession) fail ("Test not available.");
	
	const std::size_t maxFldSize = 65534;
	_pSession->setProperty("maxFieldSize", Poco::Any(maxFldSize-1));
	recreatePersonBLOBTable();

	try
	{
		_pExecutor->blob(maxFldSize);
		fail ("must fail");
	}
	catch (DataException&) 
	{
		_pSession->setProperty("maxFieldSize", Poco::Any(maxFldSize));
	}

	recreatePersonBLOBTable();
	_pExecutor->blob(maxFldSize);

	recreatePersonBLOBTable();

	try
	{
		_pExecutor->blob(maxFldSize+1);
		fail ("must fail");
	}
	catch (DataException&) { }
}


void MySQLTest::testBLOBStmt()
{
	if (!_pSession) fail ("Test not available.");

	recreatePersonBLOBTable();
	_pExecutor->blobStmt();
}


void MySQLTest::testFloat()
{
	if (!_pSession) fail ("Test not available.");

	recreateFloatsTable();
	_pExecutor->floats();
}


void MySQLTest::testDouble()
{
	if (!_pSession) fail ("Test not available.");

	recreateFloatsTable();
	_pExecutor->doubles();
}


void MySQLTest::testTuple()
{
	if (!_pSession) fail ("Test not available.");

	recreateTuplesTable();
	_pExecutor->tuples();
}


void MySQLTest::testTupleVector()
{
	if (!_pSession) fail ("Test not available.");

	recreateTuplesTable();
	_pExecutor->tupleVector();
}


void MySQLTest::testInternalExtraction()
{
	if (!_pSession) fail ("Test not available.");

	recreateVectorsTable();
	_pExecutor->internalExtraction();
}


void MySQLTest::testNull()
{
	if (!_pSession) fail ("Test not available.");

	recreateVectorsTable();
	_pExecutor->doNull();
}


void MySQLTest::dropTable(const std::string& tableName)
{
	try
	{
		*_pSession << format("DROP TABLE %s", tableName), now;
	}
	catch (StatementException& )
	{
		//throw;
	}
}


void MySQLTest::recreatePersonTable()
{
	dropTable("Person");
	try { *_pSession << "CREATE TABLE Person (LastName VARCHAR(30), FirstName VARCHAR(30), Address VARCHAR(30), Age INTEGER)", now; }
	catch(ConnectionException& ce){ std::cout << ce.displayText() << std::endl; fail ("recreatePersonTable()"); }
	catch(StatementException& se){ std::cout << se.displayText() << std::endl; fail ("recreatePersonTable()"); }
}


void MySQLTest::recreatePersonBLOBTable()
{
	dropTable("Person");
	try { *_pSession << "CREATE TABLE Person (LastName VARCHAR(30), FirstName VARCHAR(30), Address VARCHAR(30), Image BLOB)", now; }
	catch(ConnectionException& ce){ std::cout << ce.displayText() << std::endl; fail ("recreatePersonBLOBTable()"); }
	catch(StatementException& se){ std::cout << se.displayText() << std::endl; fail ("recreatePersonBLOBTable()"); }
}


void MySQLTest::recreateIntsTable()
{
	dropTable("Strings");
	try { *_pSession << "CREATE TABLE Strings (str INTEGER)", now; }
	catch(ConnectionException& ce){ std::cout << ce.displayText() << std::endl; fail ("recreateIntsTable()"); }
	catch(StatementException& se){ std::cout << se.displayText() << std::endl; fail ("recreateIntsTable()"); }
}


void MySQLTest::recreateStringsTable()
{
	dropTable("Strings");
	try { *_pSession << "CREATE TABLE Strings (str VARCHAR(30))", now; }
	catch(ConnectionException& ce){ std::cout << ce.displayText() << std::endl; fail ("recreateStringsTable()"); }
	catch(StatementException& se){ std::cout << se.displayText() << std::endl; fail ("recreateStringsTable()"); }
}


void MySQLTest::recreateFloatsTable()
{
	dropTable("Strings");
	try { *_pSession << "CREATE TABLE Strings (str FLOAT)", now; }
	catch(ConnectionException& ce){ std::cout << ce.displayText() << std::endl; fail ("recreateFloatsTable()"); }
	catch(StatementException& se){ std::cout << se.displayText() << std::endl; fail ("recreateFloatsTable()"); }
}


void MySQLTest::recreateTuplesTable()
{
	dropTable("Tuples");
	try { *_pSession << "CREATE TABLE Tuples "
		"(i0 INTEGER, i1 INTEGER, i2 INTEGER, i3 INTEGER, i4 INTEGER, i5 INTEGER, i6 INTEGER, "
		"i7 INTEGER, i8 INTEGER, i9 INTEGER, i10 INTEGER, i11 INTEGER, i12 INTEGER, i13 INTEGER,"
		"i14 INTEGER, i15 INTEGER, i16 INTEGER, i17 INTEGER, i18 INTEGER, i19 INTEGER)", now; }
	catch(ConnectionException& ce){ std::cout << ce.displayText() << std::endl; fail ("recreateTuplesTable()"); }
	catch(StatementException& se){ std::cout << se.displayText() << std::endl; fail ("recreateTuplesTable()"); }
}


void MySQLTest::recreateVectorsTable()
{
	dropTable("Vectors");
	try { *_pSession << "CREATE TABLE Vectors (i0 INTEGER, flt0 FLOAT, str0 VARCHAR(30))", now; }
	catch(ConnectionException& ce){ std::cout << ce.displayText() << std::endl; fail ("recreateVectorsTable()"); }
	catch(StatementException& se){ std::cout << se.displayText() << std::endl; fail ("recreateVectorsTable()"); }
}


void MySQLTest::setUp()
{
}


void MySQLTest::tearDown()
{
	dropTable("Person");
	dropTable("Strings");
}


CppUnit::Test* MySQLTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("MySQLTest");

	CppUnit_addTest(pSuite, MySQLTest, testBareboneMySQL);
	CppUnit_addTest(pSuite, MySQLTest, testSimpleAccess);
	CppUnit_addTest(pSuite, MySQLTest, testComplexType);
	CppUnit_addTest(pSuite, MySQLTest, testSimpleAccessVector);
	CppUnit_addTest(pSuite, MySQLTest, testComplexTypeVector);
	CppUnit_addTest(pSuite, MySQLTest, testInsertVector);
	CppUnit_addTest(pSuite, MySQLTest, testInsertEmptyVector);
	CppUnit_addTest(pSuite, MySQLTest, testInsertSingleBulk);
	CppUnit_addTest(pSuite, MySQLTest, testInsertSingleBulkVec);
	CppUnit_addTest(pSuite, MySQLTest, testLimit);
	CppUnit_addTest(pSuite, MySQLTest, testLimitOnce);
	CppUnit_addTest(pSuite, MySQLTest, testLimitPrepare);
	CppUnit_addTest(pSuite, MySQLTest, testLimitZero);
	CppUnit_addTest(pSuite, MySQLTest, testPrepare);
	CppUnit_addTest(pSuite, MySQLTest, testSetSimple);
	CppUnit_addTest(pSuite, MySQLTest, testSetComplex);
	CppUnit_addTest(pSuite, MySQLTest, testSetComplexUnique);
	CppUnit_addTest(pSuite, MySQLTest, testMultiSetSimple);
	CppUnit_addTest(pSuite, MySQLTest, testMultiSetComplex);
	CppUnit_addTest(pSuite, MySQLTest, testMapComplex);
	CppUnit_addTest(pSuite, MySQLTest, testMapComplexUnique);
	CppUnit_addTest(pSuite, MySQLTest, testMultiMapComplex);
	CppUnit_addTest(pSuite, MySQLTest, testSelectIntoSingle);
	CppUnit_addTest(pSuite, MySQLTest, testSelectIntoSingleStep);
	CppUnit_addTest(pSuite, MySQLTest, testSelectIntoSingleFail);
	CppUnit_addTest(pSuite, MySQLTest, testLowerLimitOk);
	CppUnit_addTest(pSuite, MySQLTest, testLowerLimitFail);
	CppUnit_addTest(pSuite, MySQLTest, testCombinedLimits);
	CppUnit_addTest(pSuite, MySQLTest, testCombinedIllegalLimits);
	CppUnit_addTest(pSuite, MySQLTest, testRange);
	CppUnit_addTest(pSuite, MySQLTest, testIllegalRange);
	CppUnit_addTest(pSuite, MySQLTest, testSingleSelect);
	CppUnit_addTest(pSuite, MySQLTest, testEmptyDB);
	//CppUnit_addTest(pSuite, MySQLTest, testBLOB);
	CppUnit_addTest(pSuite, MySQLTest, testBLOBStmt);
	CppUnit_addTest(pSuite, MySQLTest, testFloat);
	CppUnit_addTest(pSuite, MySQLTest, testDouble);
	CppUnit_addTest(pSuite, MySQLTest, testTuple);
	CppUnit_addTest(pSuite, MySQLTest, testTupleVector);
	CppUnit_addTest(pSuite, MySQLTest, testInternalExtraction);
	CppUnit_addTest(pSuite, MySQLTest, testNull);

	return pSuite;
}
