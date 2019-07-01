// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"
#include "customLibs/misc.h"

TEST_CASE("check inf and nan") {
	INFO_LOG << "check float: " << checkIfNanOrInf(23.3) << '\n';
	INFO_LOG << "check doubl: " << checkIfNanOrInf(double(123)) << '\n'; 
	//INFO_LOG << "check inf: " << checkIfNanOrInf(1.0/0) << '\n';

	double test1 = std::nan("1");
	INFO_LOG << "test1: " << test1 << '\n';
	INFO_LOG << "test1: " << std::hex << test1 << '\n';
	double test2 = std::nan("2");
	INFO_LOG << "test2: " << test2 << '\n';

	INFO_LOG << "check test1: " << checkIfNanOrInf(test1) << '\n';
	INFO_LOG << "check test2: " << checkIfNanOrInf(test2) << '\n';
}

