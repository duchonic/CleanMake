// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "helper.h"
#include <vector>
#include <bitset>
#include <array>

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
		//Combi(input, i, 0, 0);
	}
	for (auto i : { 3,2,1 }) {
		std::cout << "\nThe all possible combination of length " << i << " for the given array set:\n";
		//Combi(input, i, 0, 0);
	}
}

const int spectrumSize = 3;
std::array<long, spectrumSize> spec{ LONG_MAX, LONG_MAX, 000 };

// Generates a comma sperated string of the spectrum data
std::string toString(const std::array<long, spectrumSize>& spec, const double iRepFactor) {
	// Convert to a string
	// C-String of maximal size
	static char szString[ (10+1) * spectrumSize];
	// One item in c representation
	static char szDigits[10];
	int uiStringArrayPos = 0;
	int uiDigitArrayPos = 0;
	unsigned int uiValue = 0;
	char chrLocal = 0;

	for (int i = 0; i < spectrumSize; ++i) {

		uiDigitArrayPos = 0;

		double tmp = 0.0;
		if (spec[i] > 0) {
			tmp = spec[i];
		}
		uiValue = static_cast<unsigned int> (floor(tmp * iRepFactor + 0.5));
		// Enforce limit
		uiValue = uiValue < 0x7FFFFFFF ? uiValue : 0x7FFFFFFF;

		// Get and save least significant digit
		while (uiValue > 0) {
			szDigits[uiDigitArrayPos++] = uiValue % 10;
			uiValue /= 10;
		}

		// Build c-style string
		for (int i = uiDigitArrayPos - 1; i >= 0; i--) {
			chrLocal = szDigits[i];
			if (chrLocal >= 0 && chrLocal <= 9) {
				szString[uiStringArrayPos++] = chrLocal + '0';
			}
			//else {
			//  // Skip digit
			//  szString[uiStringArrayPos++] = '@';
			//}
		}

		// Special case zero
		if (uiDigitArrayPos == 0) {
			szString[uiStringArrayPos++] = '0';
		}

		// Separator
		szString[uiStringArrayPos++] = ',';
	}

	// Replace last separator with termination symbol
	szString[uiStringArrayPos - 1] = 0;

	std::string strResult(szString);
	return strResult;
}



TEST_CASE("spectrum to string before") {
	std::cout << "spectrum to string before" << std::endl;

	std::cout << toString(spec,1) << std::endl;
}


// Generates a comma sperated string of the spectrum data
std::string toStringClean(const std::array<long, spectrumSize>& spec, const double iRepFactor) {
	std::string returnString{ "" };

	for (auto val : spec) {
		unsigned int uiValue = 0;
		if (val > 0) {
			uiValue = static_cast<unsigned int> (floor(val * iRepFactor + 0.5));
		}
		else {
			uiValue = 0;
		}
		returnString += std::to_string(uiValue) + ','; // add value plus comma
	}
	returnString.pop_back(); // remove the last comma ( 1,2,3, => 1,2,3 )
	return returnString;
}



TEST_CASE("spectrum to string after") {
	std::cout << "spectrum to string after" << std::endl;
	std::cout << toStringClean(spec, 1) << std::endl;
	REQUIRE( toStringClean(spec, 1) == toString(spec, 1) );
}