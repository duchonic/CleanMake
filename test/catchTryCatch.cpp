// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"
#include <iostream>

class TestTwoThrowException {
public:
	std::string msg;
	TestTwoThrowException(std::string message) {
		msg = message;
	}
	std::string what(void) {
		return msg;
	}
};
class TestThreeThrowException {
public:
	std::string msg;
	TestThreeThrowException(std::string message) {
		msg = message;
	}
	std::string what(void) {
		return msg;
	}
};

void throwTestOne(void) {
	throw __FUNCTION__ + std::string("/ test one");
}

void throwTestTwo(void) {
	throw TestTwoThrowException(__FUNCTION__ + std::string("/blubiblib") );
}

void throwTestThree(void) {
	throw TestThreeThrowException(std::string("123 ") + __FUNCTION__ + std::string(" 456"));
}

TEST_CASE("test try one") {
	try{
		throwTestOne();
	}
	catch (std::string& ex){
		ERROR_LOG << ex <<  '\n';
	}
}

TEST_CASE("test try two") {
	try{
		throwTestTwo();
	}
	catch (TestTwoThrowException& msg){
		ERROR_LOG << msg.what() << '\n';
	}
}

TEST_CASE("test try three") {
	try {
		throwTestThree();
	}
	catch(TestThreeThrowException& msg){
		ERROR_LOG << msg.what() << '\n';
	}

}