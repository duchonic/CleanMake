// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.h"

#include <libMPSSE_spi.h>
#include <libMPSSE_i2c.h>


int testSerial() {
	int blub = 3;
	return blub;
}

TEST_CASE("TEST MPSSE SPI", "[single-file]") {
	
	FT_STATUS status = FT_OK;
	uint32 channels = 2;
	status = SPI_GetNumChannels(&channels);
	REQUIRE(status == FT_OK);
	REQUIRE(channels == 2);

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