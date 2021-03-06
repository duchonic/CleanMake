// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "helper.h"
#include <vector>
#include <bitset>
#include <array>

unsigned long smalestQuantum = MAXINT;


void showVec(std::vector<int> data, std::string title) {
	std::cout << title << " : " ;
	for (int val : data) {
		std::cout << val << " ";
	}
	std::cout << std::endl;
}


void Combi(std::vector<int> input, int reqLen, int currentBit, int currLen)
// print the all possible combination of given array set
{
	static std::bitset<29> check;
	if (currLen > reqLen)
		return;
	else if (currLen == reqLen) {
		//std::cout << check << " " << std::endl;
		
		int sum=0;
		std::vector<int> output;
		std::vector<int> rest;

		for (   int i = 0; i < input.size(); i++) {
			if (check.test(i)) {
				output.push_back( input[i] ) ;
				sum += input[i];
			}
			else {
				rest.push_back( input[i] );
			}
		}
		if (sum == 20) {
			std::cout << "found a solution: " << std::endl;
			showVec(output, " out: ");
			showVec(rest, " rest: ");
			Combi(rest, 3, 0, 0);
		}
		else {

		}
		return;
	}
	if (currentBit == input.size()) {
		return;
	}
	check.set(currentBit);
	Combi(input, reqLen, currentBit + 1, currLen + 1);
	//recursively call Combi() with incremented value of �currLen� and �currentBit�.
	check.reset(currentBit);
	Combi(input, reqLen, currentBit + 1, currLen);
	// recursively call Combi() with only incremented value of �currentBit�.
}




TEST_CASE("combi from tutorialspoint.com") {
	std::vector<int> input{1,2,3,4,5,7,8,9,10,11};
	//std::vector<int> input{ 1,2,3,5,7,13,17,19,23,29,31,37,41,43,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113};
	
	int sum=0;
	for (auto val : input) {
		sum+=val;
	}
	std::cout << "sum is:" << sum << " third:" << sum/2 << std::endl;

	std::cout << "\n";
	for ( auto i: {2} ) {
		std::cout << "\nThe all possible combination of length " << i << " for the given array set:\n";
		Combi(input, i, 0, 0);
	}
	

}

