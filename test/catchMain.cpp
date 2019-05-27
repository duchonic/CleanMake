// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.h"
#include "customLibs/helper.h"
#include <array>


class Spectrum {
public:
	static const int SIZE = 64;
	Spectrum();

	void reset();
	void addValue(int, int);
	int getValue(int index);

private:
	std::array<double, SIZE> values;
};

Spectrum::Spectrum() {
}

void Spectrum::reset() {
	INFO_LOG << "reset blub e" << '\n';
}

void Spectrum::addValue(int index, int value) {
	values.at(index) = value;
}

int Spectrum::getValue(int index) {
	return values.at(index);
}


TEST_CASE("array of class", "array of class") {
	std::array<Spectrum, 8> mySpecs;
	REQUIRE(mySpecs.size() == 8);

	mySpecs.at(0).reset();
	mySpecs.at(1).addValue(1, 1);
	REQUIRE(mySpecs.at(1).getValue(1) == 1);
	mySpecs.at(3).addValue(3, 81);
	REQUIRE(mySpecs.at(3).getValue(3) == 81);
}


int testSerial() {
	int blub = 3;
	return blub;
}


int switchTest(int i) {
	switch (i){
		default:
			return 99;
		case 0:
			break;
		case 1:
			return 1;
		case 2:
			return 2;
		case 898:
			break;
	}
}

SCENARIO("BITARRAY", "BITARRAY") {
	GIVEN("create a bitArray") {
		std::array<bool, 8> bitArray;

		bitArray.at(0) = false;
		WHEN("check some array features") {
			INFO_LOG << "bitArray.at(0): " << bitArray.at(0) << '\n';
			INFO_LOG << "bitArray.at(7): " << bitArray.at(7) << '\n';
			bitArray.at(3) = true;
		}
	}


}

SCENARIO("ARRAYS", "[array]") {
	GIVEN("lets do some array stuff") {
		const int size{ 63 };
		std::array<double, size> testArray;
		std::vector<int> testVector;
		

		WHEN("edit some elements") {
			testArray[4] = 12.4;
			testArray[5] = 0;
			testArray[5] += 11.1;

			for (int entries = 10; entries > 0; entries--) {
				testVector.push_back(entries);
			}
			INFO_LOG << "testVector size: " << testVector.size() << '\n';
			INFO_LOG << "testVector at 0: " << testVector[0] << '\n';
			INFO_LOG << "testVector at 9: " << testVector.at(9) << '\n';
			//INFO_LOG << "testVector at 10" << testVector.at(19) << '\n';

			for (auto entries : testVector) {
				std::cout << entries << '\n';
			}

			for (auto s : testArray) {
				std::cout << s;
			}

			THEN("size changes ") {
				REQUIRE(testArray.at(4) == 12.4);
				REQUIRE(testArray.at(5) == 11.1);
				//REQUIRE(testArray.at(23123) == 123);
				
			}
		}
	}
}


TEST_CASE("Test Switch", "[single]") {
	DEBUG_LOG << "switchTest(0):" << switchTest(0) << '\n';
	DEBUG_LOG << "switchTest(1):" << switchTest(1) << '\n';
	DEBUG_LOG << "switchTest(2):" << switchTest(2) << '\n';
	DEBUG_LOG << "switchTest(3):" << switchTest(3) << '\n';
	DEBUG_LOG << "switchTest(898):" << switchTest(898) << '\n';

	REQUIRE(switchTest(0) == 0);
	REQUIRE(switchTest(1) == 1);
	REQUIRE(switchTest(2) == 2);
	REQUIRE(switchTest(3) == 99);
	REQUIRE(switchTest(898) == 898);
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