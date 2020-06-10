// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/json.h"
#include "helper.h"


using json = nlohmann::json;

TEST_CASE("json tests") {
	json j;

	int a = 12;
	double b = a;

	j["pi"] = 3.13;
	j["name"] = "blub";

	INFO_LOG << j.dump() << std::endl;

	REQUIRE(1 == 1);
	REQUIRE(2 == 2);
}

