// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "helper.h"
#include <vector>
#include <bitset>

void Combi(std::vector<int> input, int reqLen, int currentBit, int currLen)
// print the all possible combination of given array set
{
	static std::bitset<8> check;

	std::cout << "reqlen:" << reqLen << " currentBit:" << currentBit << " currLen:" << currLen << " check:" << check << std::endl;

	if (currLen > reqLen)
		return;
	else if (currLen == reqLen) {
		std::cout << "\t" << check << " ";

		for (   int i = 0; i < input.size(); i++) {
			if (check.test(i)) {
				std::cout << input[i] << " ";
			}
		}
		std::cout << "\n";
		return;
	}
	if (currentBit == input.size()) {
		return;
	}
	check.set(currentBit);
	Combi(input, reqLen, currentBit + 1, currLen + 1);
	//recursively call Combi() with incremented value of ‘currLen’ and ‘currentBit’.
	check.reset(currentBit);
	Combi(input, reqLen, currentBit + 1, currLen);
	// recursively call Combi() with only incremented value of ‘currentBit’.
}


void doStuff(std::vector<int> &in) {
	DEBUG_LOG << "size: " << in.size() << std::endl;
	if (in.size()) {
		in.pop_back();
		doStuff(in);
	}
}

void showStuff(std::vector<int>& input) {
	std::cout << "input: ";
	for (auto nr : input) {
		std::cout << nr << " ";
	}
	std::cout << std::endl;
}

TEST_CASE("do some recursion") {
	DEBUG_LOG << "first test" << std::endl;
	std::vector<int> v = { 1, 2, 3, 4 };
	
	showStuff(v);
	doStuff(v);

	INFO_LOG << "size after function: " << v.size() << std::endl;
}


TEST_CASE("combi from tutorialspoint.com") {
	
	
	std::vector<int> input{5,2,3,4};
	std::cout << "\n";
	for ( auto i: {1,2,3} ) {
		std::cout << "\nThe all possible combination of length " << i << " for the given array set:\n";
		Combi(input, i, 0, 0);
	}
	for (auto i : { 3,2,1 }) {
		std::cout << "\nThe all possible combination of length " << i << " for the given array set:\n";
		Combi(input, i, 0, 0);
	}
}