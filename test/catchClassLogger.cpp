// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"
#include <iostream>

class Logger
{
public:
	Logger();
	~Logger();

	static std::ostream& blub() {
		std::cout << "blub: ";
		return std::cout;
	}

private:

};

#define CATCH_LOG Logger::blub()

Logger::Logger(){
}

Logger::~Logger(){
}

TEST_CASE("test class", "") {
	INFO_LOG << "run driver test" << '\n';
	std::cout << "blub" << '\n';
	CATCH_LOG << "ASDF" << '\n';
}