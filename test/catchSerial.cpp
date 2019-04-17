// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"

Helper myHelper;

int test2() {
	int blub = 3;
	return blub;
}

TEST_CASE("TEST3", "[single-file]") {

  DEBUG_LOG << "test3 running" << '\n';

	REQUIRE(myHelper.DATE == 2019);
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
