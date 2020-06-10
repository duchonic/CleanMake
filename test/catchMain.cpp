// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.h"


TEST_CASE("main running") {

	std::vector<int> myVec5{ 1,2,3,4,5,6,7,8,9,10 };
	std::cout << std::setw(20) << std::left << "myVec5: i->i*i   ";
	//std::for_each(myVec5.begin(), myVec5.end(), );

	auto lambda = [](int& i) {i = i + 1.2; };

	std::for_each( myVec5.begin(), myVec5.end(), lambda );
	for (auto v : myVec5) std::cout << std::setw(6) << std::left << v;
	std::cout << "\n";

}


TEST_CASE("test") {


	std::string copy{"original"};
	std::string ref{"original"};

	auto lambda = [copy, &ref]{std::cout << copy << " " << ref << std::endl;};

	lambda();
	copy = "changed";
	ref = "changed";
	lambda();

}


TEST_CASE("SUBSTRING") {

	const std::string& strController1{"algh"};
	std::cout << strController1.substr(0,3) << std::endl;

	const std::string& strController2{ "alg" };
	std::cout << strController2.substr(0, 3) << std::endl;

	const std::string& strController3{ "al" };
	std::cout << strController3.substr(0, 3) << std::endl;
}