// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.h"
#include "customLibs/helper.h"
#include <array>
#include <vector>

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


class AlgHelper
{
public:
	AlgHelper();
	~AlgHelper();
	void setNr(int nrInput = 12) {
		nr = nrInput;
	}
	int getNr() {
		return nr;
	}

private:
	int nr;
	std::string name;
};

AlgHelper::AlgHelper()
{
	DEBUG_LOG << "constructor" << NL;
}

AlgHelper::~AlgHelper()
{
	DEBUG_LOG << "deconstructor" << NL;
}

TEST_CASE("alghelper", "blub") {
	AlgHelper h,i;
	h.setNr();
	i.setNr(898);
	INFO_LOG << "alghelper h nr: " << h.getNr() << NL;
	INFO_LOG << "alghelper i nr: " << i.getNr() << NL;
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
			break;
		case 0:
			return 0;
			break;
		case 1:
			return 1;
			break;
		case 2:
			return 2;
			break;
		case 898:
			return 898;
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

			//for (auto entries : testVector) {
			//	std::cout << entries << '\n';
			//}

			//for (auto s : testArray) {
			//	std::cout << s;
			//}

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

TEST_CASE("no parent > don't do it!", "blub") {
	REQUIRE( (7 > 2 * 3)   == 1 );
	REQUIRE( (7 > (2 * 3)) == 1 );
	REQUIRE( ((7 > 2) * 3) == 3 );
	INFO_LOG << "(7 > 2 * 3) = "   << (7 >  2 * 3)  << '\n';
	INFO_LOG << "(7 > (2 * 3)) = " << (7 > (2 * 3)) << '\n';
	INFO_LOG << "(7 > 2) * 3 = "   << (7 >  2)* 3   << '\n';
}


#define doubleA 4.4
#define integerA 4

TEST_CASE("variable declaration") {
	{
		int a = integerA;
		INFO_LOG << "a: " << a << " should be: " << integerA << '\n';
		REQUIRE(a == integerA);
	}
	{
		int a(doubleA);
		INFO_LOG << "a: " << a << " should be: " << doubleA << '\n';
		REQUIRE(a == integerA);
	}
	{
		int a{ integerA };
		INFO_LOG << "a: " << a << " should be: " << integerA << '\n';
		REQUIRE(a == integerA);
	}
	{
		auto a{ doubleA };
		INFO_LOG << "a: " << a << " should be: " << doubleA << '\n';
		REQUIRE(int(a) == integerA);
		REQUIRE(a == doubleA);
	}
}

void setSlope(int value) {
	(void)value;
}


TEST_CASE("variable declaration place") {
	bool negativeSlope = true;

	if (negativeSlope) {
		int min = 12;
		for (const auto &i : { 0, 1, 2}) {
			setSlope(min);
			INFO_LOG << "for loop: " << i << '\n';
		}	
		for (auto i : { 12, 13, 14 }) {
			i %= 2;
			INFO_LOG << "fol loop: " << i << '\n';
		}
	}
	else {
		int max = 23;
		setSlope(max);
	}

	std::vector<bool> vi(20, 1); /** 20 items with value 1 */
	INFO_LOG << "vector size: " << vi.size() << '\n';
	for (auto nr : vi) {
		INFO_LOG << nr << '\n';
		//INFO_LOG << "blub";
	}
	INFO_LOG << '\n';
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


TEST_CASE("FOR loops", "[]") {
	INFO_LOG << "test case for loops" << '\n';

	int soll = 0;
	for (int ist = 0; ist < 12; ist+=1) {
		REQUIRE(soll++ == ist);
	}
}

TEST_CASE("modulo zero", "") {
	INFO_LOG << "MODULO" << '\n';

	INFO_LOG << "FMOD(0,0): " << fmod(0, 0) << '\n';
}
