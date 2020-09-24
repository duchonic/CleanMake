// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include <iostream>
#include <map>

SCENARIO("some tests with paramters") {
	
	std::map<std::string, int> intMap;
	std::map<std::string, bool> boolMap;
	std::map<std::string, float> floatMap;
	std::map<std::string, std::string> stringMap;

	GIVEN("fill some paramters in a set") {

		intMap.insert( std::make_pair("first", 1) );
		//intMap.insert( std::make_pair("second", 2) );
		boolMap.insert( std::make_pair("first", 2) );
		floatMap.insert( std::make_pair("first", 1.1f) );
		stringMap.insert( std::make_pair("first", "first") );
		//stringMap.insert(std::make_pair("first", 0));




		WHEN("size is reduced") {

			try{
				std::cout << intMap["first"] << std::endl;
				std::cout << intMap.at("") << std::endl;
				std::cout << boolMap["first"] << std::endl;
				std::cout << floatMap["first"] << std::endl;
				std::cout << stringMap["first"] << std::endl;
				
				THEN("size changes ") {

				}

			}
			catch (const std::exception&)
			{
				std::cout << "some problems occured" << std::endl;
			}


		}
	}
}
