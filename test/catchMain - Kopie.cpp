// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.h"
#include "customLibs/helper.h"
#include <array>
#include "Sample.h"
#include "json.h"

class Spectrum {
public:
	static const size_t SIZE = 64;
	Spectrum();

	void reset();
	void addValue(size_t, double);
	double getValue(size_t index);

private:
	std::array<double, SIZE> values;
};

Spectrum::Spectrum() {
}

void Spectrum::reset() {
	INFO_LOG << "reset blub e" << '\n';
}

void Spectrum::addValue(size_t index, double value) {
	values.at(index) = value;
}

double Spectrum::getValue(size_t index) {
	return values.at(index);
}


static const std::string TEST_CHECK{ "123" };
static const std::string INPUT_CHECK{ "123" };

void checkCheck(void) {
	if (INPUT_CHECK != TEST_CHECK) {
		return;
	}

	if (INPUT_CHECK != TEST_CHECK) {
		DEBUG_LOG << "check";
	}
}

TEST_CASE("test lint") {
	checkCheck();
}


TEST_CASE("load json", "load json") {
	//Helper myHelper;
}


TEST_CASE("array of class", "array of class") {
	std::array<Spectrum, 8> mySpecs;
	//REQUIRE(mySpecs.size() == (size_t)(8));

	mySpecs.at(0).reset();
	mySpecs.at(1).addValue(1, 1.0);
	REQUIRE(mySpecs.at(1).getValue(1) == 1.0);
	mySpecs.at(3).addValue(3, 81.0);
	REQUIRE(mySpecs.at(3).getValue(3) == 81.0);
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

	//REQUIRE(switchTest(0) == 0);
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
				//REQUIRE(v.size() == 0);
				//REQUIRE(v.capacity() == 4);
				REQUIRE(1 == 1);
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


class Point {
public:
	Point(std::pair<int, int> startPoint) {
		point = startPoint;
	}
	int xPos() const {return point.first;}
	int yPos() const {return point.second;}

	Point& operator*=(const std::pair<int,int>& rhs)
	{
		this->point.first *= rhs.first;
		this->point.second *= rhs.second;
		return *this;
	}

	bool operator==(const Point &checkPoint) {
		if (this->xPos() == checkPoint.point.first ) {
			std::cout << "test:" << checkPoint.xPos() << std::endl;
			return true;
		}
		else {
			return false;
		}
	}

	bool operator==(const std::pair<int, int>& checkPoint) {
		if (this->xPos() == checkPoint.first) {
			return true;
		}
		else {
			return false;
		}
	}


	void show(void) {
		std::cout << "x:" << point.first << " y:" << point.second << std::endl;
	}
private:
	std::pair<int, int> point;

};

SCENARIO("TEST POINTS") {
	std::cout << "\n\n << test some points >> " << std::endl;
	
	Point first(std::make_pair(3, 4));
	Point second(std::make_pair(3, 8));

	if (first == std::make_pair(3, 4)) {
		std::cout << "equal" << std::endl;
	}

	if (first == second) {
		std::cout << "equal again" << std::endl;
	}

	//REQUIRE( first == std::make_pair(3,4))

}


SCENARIO("struct") {
	std::cout << std::endl << "some tests with structs" << std::endl;

	// constants
	enum SlopeEnum {
		ALG_SLOPE_UNKOWN,
		ALG_SLOPE_POSITIVE,
		ALG_SLOPE_NEGATIVE,
	};

	// filtered data
	struct AllData : Sample {
		int iPolynomeApproxValue;
		SlopeEnum eSlope;

		AllData() :
			iPolynomeApproxValue(0),
			eSlope(SlopeEnum::ALG_SLOPE_UNKOWN)
		{}

		AllData& operator+=(AllData a) {
			iPolynomeApproxValue += a.iPolynomeApproxValue;
			return *this;
		}

		void reset(int test) {
			iPolynomeApproxValue = test;
		};
	};

	AllData testA, testB;

	testA.iPolynomeApproxValue = 11;
	testA.eSlope = ALG_SLOPE_POSITIVE;
	testA.measValue = 22;
	testA.refValue = 33;

	testB = testA;
	testB += testA;

	REQUIRE(testA.refValue == testB.refValue);
	//REQUIRE(testA.refValue == 33);
	//REQUIRE(testA.iPolynomeApproxValue == 11);
}



SCENARIO("json stuff") {
	
	// for convenience
	using json = nlohmann::json;

	// read a JSON file
	std::ifstream i("pretty.json");
	json CommParameter;
	i >> CommParameter;
	std::string out = CommParameter.dump(2);
	INFO_LOG << out << std::endl;


	CommParameter.emplace("1", "3");

	for (json::iterator it = CommParameter["HEATER_PARAMETERS"].begin(); it != CommParameter["HEATER_PARAMETERS"].end(); ++it) {
		INFO_LOG << it.key() << ":" << it.value() << std::endl;
	}

	for (auto item : CommParameter.items()) {
		INFO_LOG << item.key() << ":" << item.value() << std::endl;
	}

	// write prettified JSON to another file
	std::ofstream o("pretty.json");
	o << std::setw(2) << CommParameter << std::endl;
}