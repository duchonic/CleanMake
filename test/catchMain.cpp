// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.h"
#include <array>

TEST_CASE(R"(cpp20 tests)"){
	auto input = std::to_array("123");
	int sum = 0;
	for (auto val : input){
		std::cout << val;
	}
	std::cout << std::endl;
}