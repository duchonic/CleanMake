// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"
#include "interface/IDriver.h"


class RunDriver : public IDriver {
public:
	void initDriver() {
		INFO_LOG << "init rundriver" << NL;
	};
	void runDriver() {
		INFO_LOG << "run rundriver" << NL;
	}
	void resetDriver();
	//{
	//	INFO_LOG << "reset rundriver" << NL;
	//};
	void closeDriver() {
		INFO_LOG << "close rundriver" << NL;
	};

private:

};

void RunDriver::resetDriver() {
	INFO_LOG << "blub" << NL;
}


class Shape {
public:
	// pure virtual function providing interface framework.
	virtual double getArea() = 0;
	void setWidth(int w) {
		width = w;
	}

	void setHeight(int h) {
		height = h;
	}

protected:
	int width;
	int height;
};

// Derived classes
class Rectanglea : public Shape {
public:
	double getArea() {
		return (width * height);
	}
};

class Triangle : public Shape {
public:
	double getArea() {
		return (width * height) / 2.0;
	}
};

TEST_CASE("interface test", "interface test") {
	Rectanglea Rect;
	Triangle  Tri;

	Rect.setWidth(5);
	Rect.setHeight(7);
	Tri.setWidth(5);
	Tri.setHeight(7);

	INFO_LOG << "catch interface" << NL;

	REQUIRE(Rect.getArea() == (5*7));
	REQUIRE(Tri.getArea() == ( (5*7) / 2.0 ));
}

TEST_CASE("rundriver interface", "blub") {

	RunDriver myRunDriver;

	myRunDriver.initDriver();
	myRunDriver.runDriver();
}