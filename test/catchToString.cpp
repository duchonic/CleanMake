// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include "helper.h"

const int spectrumSize = 4;

// Generates a comma sperated string of the spectrum data
std::string toString(const std::array<long, spectrumSize>& spec, const double iRepFactor) {
	// Convert to a string
	// C-String of maximal size
	static char szString[ (10+0) * spectrumSize];
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

// Generates a comma sperated string of the spectrum data
std::string toStringClean(const std::array<long, spectrumSize>& spectrum, const double iRepFactor) {
	std::string returnString{""};
	for (long value : spectrum) {
		// calculate value times RepFactor if value is bigger than zero
		value = value > 0 ? std::floor(value * iRepFactor + 0.5) : 0;
		// add value plus comma
		returnString += std::to_string(value) + ','; 
	}
	// remove the last comma ( 1,2,3, => 1,2,3 )
	returnString.pop_back();
	return returnString;
}



TEST_CASE("test the to Strings Functions") {
	std::array<long, spectrumSize> spectrum{1,2,3,4};
	for (auto factor : { 1.0, 0.1, 1.5 }) {
		std::cout << toStringClean(spectrum, factor) << std::endl;
		REQUIRE(toStringClean(spectrum, factor) == toString(spectrum, factor));
	}
	for (auto factor :{ 1, MAXINT, -1, MAXLONG }) {
		std::cout << toStringClean(spectrum, factor) << std::endl;
		REQUIRE( toStringClean(spectrum, factor) == toString(spectrum, factor) );
	}
}