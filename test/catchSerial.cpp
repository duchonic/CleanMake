// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"
#include "source/serial.h"
#include <functional>

Serial mySerial;

int test2() {
	int blub = 3;
	return blub;
}

std::function<int()> f = nullptr;


TEST_CASE("TEST3", "[single-file]") {

	try {
		f();
	}
	catch (const std::bad_function_call & e) {
		TEST_LOG << "e.what(): " << e.what() << '\n';
	}

	REQUIRE( mySerial.write(std::string("1234567890")) == false);
	REQUIRE( mySerial.write(std::string("12345678901")) == true);

	REQUIRE(test2() == 3);
	REQUIRE(1 == 1);
	REQUIRE(2 == 2);
}

TEST_CASE("TEST4", "[single-file]") {
	REQUIRE(1 == 1);
	REQUIRE(2 == 2);
}

SCENARIO("vectors size test2", "[vector]") {
	GIVEN("a vector with som eitems") {
		std::vector<int> v(4);

		WHEN("size is reduced") {
			v.resize(0);

			THEN("size changes ") {
				REQUIRE(v.size() == 0);
				REQUIRE(v.capacity() == 4);
			}
		}
	}
}
