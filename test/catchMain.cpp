// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.h"

int testSerial() {
	int blub = 3;
	return blub;
}

TEST_CASE("TEST1", "[single-file]") {
	REQUIRE(testSerial() == 3);
	REQUIRE(1 == 1);
	REQUIRE(2 == 2);
}

TEST_CASE("TEST2", "[single-file]") {
	REQUIRE(1 == 1);
	REQUIRE(2 == 2);
}

SCENARIO("vectors size test", "[vector]") {
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

// That's it

// Compile implementation of Catch for use with files that do contain tests:
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -c 000-CatchMain.cpp
// - cl -EHsc -I%CATCH_SINGLE_INCLUDE% -c 000-CatchMain.cpp
