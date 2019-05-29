// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"
#include "interface/IDriver.h"
#include "interface/IDriverManager.h"
#include "interface/ISingleton.h"

class AbsDriverManager : public IDriverManager{

protected:
	AbsDriverManager();
public:
	~AbsDriverManager();
	void addDriver(int driverNr);
	void runDrivers();

private:
	// The driver vector
	std::vector<int> _vecDrivers;
};

AbsDriverManager::AbsDriverManager(){
}

AbsDriverManager::~AbsDriverManager(){
}

void AbsDriverManager::addDriver(int driverNr) {
	_vecDrivers.push_back(driverNr);
}

void AbsDriverManager::runDrivers()
{
	for (size_t i = 0; i < _vecDrivers.size(); ++i) {
		INFO_LOG << "rundriver nr: " << _vecDrivers[i] << '\n';
	}
}

TEST_CASE("Run drivers", "") {
	INFO_LOG << "run driver test" << '\n';
}