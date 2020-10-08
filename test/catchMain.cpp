// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

// Let Catch provide main():
#define CATCH_CONFIG_MAIN

#include "catch.h"
#include <array>

TEST_CASE(R"(cpp17/20 tests)"){
	//auto input = std::to_array("123"); // cpp20
	std::array<char,3> input{ '1','2,','3' }; // cpp11
	int sum = 0;
	for (auto val : input){
		std::cout << val;
	}
	std::cout << std::endl;
}

TEST_CASE("LAMBDAS") {
	std::cout << "lambda test" << std::endl;
	int x = 898;
	// 1. the simplest lambda:
	[] {};

	// 2. with two params:
	[](float f, int a) { return a * f; };
	[](int a, int b) { return a < b; };

	// 3. trailing return type:
	//[](MyClass t) -> int { auto a = t.compute(); print(a); return a; };

	// 4. additional specifiers:
	[x](int a, int b) mutable { ++x; return a < b; };
	[](float param) noexcept { return param * param; };
	[x](int a, int b) mutable noexcept { ++x; return a < b; };

	// 5. optional ()
	auto a = [x](int add) { 
		std::cout << "test:" << x + add; 
		std::cout << std::endl; 
	}; // no () needed
	
	   //[x] mutable { ++x; };    // won't compile!
	[x]() mutable { ++x; };  // fine - () required before mutable
	//[] noexcept {};        // won't compile!
	[]() noexcept {};      // fine

	a(2);
}

TEST_CASE("bfilipek day1") {
	int x = 30;
	int y = 12;
	auto foo = [z = x + y]() { std::cout << z << '\n'; };
	const auto bar = [z = x + y]() { std::cout << z << '\n'; };
	auto change = [&x,&y]() {std::cout << x + y << '\n'; };
	x = 0;
	y = 0;
	foo();
	bar();
	change();
}

std::string day("bfilipek day2");


TEST_CASE(day) {
	std::cout << day << ":\n";
	day = day + "123";
	int x = 2;
	int y = 3;

	const auto l1 = []() { return 1; };          // No capture
	const auto l2 = [=]() { return x; };         // All by value (copy)
	const auto l3 = [&]() { return y; };         // All by ref
	const auto l4 = [x]() { return x; };         // Only x by value (copy)
	// const auto lx = [=x]() { return x; };     // wrong syntax, no need for
												 // = to copy x explicitly
	const auto l5 = [&y]() { return y; };        // Only y by ref
	const auto l6 = [x, &y]() { return x * y; }; // x by value and y by ref
	const auto l7 = [=, &x]() { return x + y; }; // All by value except x 
												 // which is by ref
	const auto l8 = [&, y]() { return x - y; };  // All by ref except y which 
												 // is by value
	//const auto l9 = [this]() {};                 // capture this pointer
	//const auto la = [*this]() {};                // capture a copy of *this 
													 // since C++17


	std::cout << l1() << std::endl;
	std::cout << l2() << std::endl;
	std::cout << l3() << std::endl;
	std::cout << l4() << std::endl;
	std::cout << l5() << std::endl;
	std::cout << l6() << std::endl;
	std::cout << l7() << std::endl;
	std::cout << l8() << std::endl;

	std::string str{ "Hello World" };
	
	auto foo = [str]() mutable { str += "123"; std::cout << str << '\n'; };
	auto bar = [str]() {std::cout << str << '\n'; };
	//auto cur = [day]() mutable { day += std::string(" and some additions"); std::cout << day << '\n'; };
	auto cur = [=]() mutable { day += std::string(" and some additions"); std::cout << day << '\n'; };
	foo();
	bar();
	cur();
}

