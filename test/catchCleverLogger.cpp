// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "customLibs/helper.h"
#include <iostream>
#include <ctime>
#include <iomanip>


//std::time_t getTime() {
//	t = std::time(nullptr);
//	return ;
//}


//#define CATCH_LOG std::cout << "time:" << std::put_time(std::gmtime( 1 ), "%c %Z") << "cleverBlub: "
#define CATCH_ERRLOG std::cerr << "cleverErrorBlob: "



TEST_CASE("test the clever logger", "") {
	INFO_LOG << "run driver test" << '\n';
	
	std::time_t xy = std::time(nullptr);
	//CATCH_LOG << "...123" << '\n';
	CATCH_ERRLOG << "ölkj" << '\n';
}