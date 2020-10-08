// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "helper.h"
#include <string>
#include <array>
#include <sstream>

const int SPECTRUM_SIZE = 3;
typedef double SPEC_VALUE;

TEST_CASE("string to array old") {

	const std::array<std::string, 2> input{ 
		std::string("1,2,3"),
		std::string("1,333333333333333333333,??"), 
	};
	
	for (std::string input : input) {
		
		std::string subStr;
		unsigned int iPos = 0;
		unsigned int iOldPos = 0;
		unsigned int i = 0;
		double dArrLocalValue[SPECTRUM_SIZE];
	
		//while (i < SPECTRUM_SIZE) {
		while(true){
			iPos = input.find(",", iOldPos);
			if (iPos == std::string::npos) {
				// Last element
				subStr = input.substr(iOldPos);
				dArrLocalValue[i++] = static_cast<SPEC_VALUE>(atoi(subStr.c_str()));
				break;
			}
			else {
				subStr = input.substr(iOldPos, iPos - iOldPos);
				dArrLocalValue[i++] = static_cast<SPEC_VALUE>(atoi(subStr.c_str()));
				REQUIRE(i < SPECTRUM_SIZE);
			}
			iOldPos = iPos + 1;
		}

		INFO_LOG << "input was : " << input << "\nresult : " << std::endl;
		for (auto value : dArrLocalValue) {
			std::cout << std::to_string(value) << " ";
		}
		std::cout << '\n';
		REQUIRE(i == SPECTRUM_SIZE);
	}
}

TEST_CASE("string to array new") {

	const std::array<std::string, 2> input{
		std::string("1,2,3"),
		std::string("9999999999999999999,???,1048"),
	};

	for (std::string input : input) {
		std::vector<int> dArrLocalValue;
		std::stringstream ss(input);
		while (!ss.eof()){ //while (ss.good()) { works also fine
			REQUIRE( (dArrLocalValue.size() < SPECTRUM_SIZE) );
			std::string sub;
			std::getline(ss, sub, ',');
			//std::stoi throws a exception if sub is nan or to big,
			//atoi from the old version just inserts a 0 without any feedback
			try{
				dArrLocalValue.push_back(std::stoi(sub));
			}
			catch (const std::exception& e){
				dArrLocalValue.push_back(0);
				ERROR_LOG << e.what() << std::endl;
			}
		}
		INFO_LOG << "input was : " << input << "\nresult : " << std::endl;
		for (auto value : dArrLocalValue) {
			std::cout << std::to_string(value) << " ";
		}
		std::cout << '\n';
		REQUIRE( (dArrLocalValue.size() == SPECTRUM_SIZE) );
	}
}