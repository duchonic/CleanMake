# toString

convert a array of long/integer to a string

input:
```
std::array<long,4> spec{12, 4, -6, 1}
```
output:
```
std::cout << "spectrum: " << toString(spec, 10) << '\n';
$ spectrum: "120,40,0,10";
```

## before 
```cpp
// Generates a comma sperated string of the spectrum data
std::string toString(const std::array<long, spectrumSize>& spec, const double iRepFactor) {
	// Convert to a string
	// C-String of maximal size
	static char szString[ (10) * spectrumSize];
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
```


## why
code crashed at:

```cpp
	// Replace last separator with termination symbol
	szString[uiStringArrayPos - 1] = 0;  => Unhandled exception at 0x00E6EA47 in testing.exe: RangeChecks instrumentation code detected an out of range array access. occurred
```
## conclusion

* Plan A was to bugfix the old code with a ```+1``` at the right place (leave the pseudo c++ mess)
* Plan B refactor the code to c++ (lots of testing because code behaves differently)
	```cpp
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
	```


# toArray

convert a string to double array 

input:
```
std::string array{"1,2,3"}
```
output:
```
double dArrValue[3]
```

## before, the old days

```cpp
TEST_CASE("string to array old") {

	const std::array<std::string, 2> input{ 
		std::string("1,2,3"),
		std::string("1,333333333333333333333,??"), 
	};
	
	for (std::string input : input) {
		
		std::string subStr;
		unsigned int iPos = 0;
		unsigned int iOldPos = 0;
		unsigned int i = 0;
		double dArrLocalValue[SPECTRUM_SIZE];
	
		//while (i < SPECTRUM_SIZE) {
		while(true){
			iPos = input.find(",", iOldPos);
			if (iPos == std::string::npos) {
				// Last element
				subStr = input.substr(iOldPos);
				dArrLocalValue[i++] = static_cast<SPEC_VALUE>(atoi(subStr.c_str()));
				break;
			}
			else {
				subStr = input.substr(iOldPos, iPos - iOldPos);
				dArrLocalValue[i++] = static_cast<SPEC_VALUE>(atoi(subStr.c_str()));
				REQUIRE(i < SPECTRUM_SIZE);
			}
			iOldPos = iPos + 1;
		}

		INFO_LOG << "input was : " << input << "\nresult : " << std::endl;
		for (auto value : dArrLocalValue) {
			std::cout << std::to_string(value) << " ";
		}
		std::cout << '\n';
		REQUIRE(i == SPECTRUM_SIZE);
	}
}
```
## new style
```cpp
TEST_CASE("string to array new") {

	const std::array<std::string, 2> input{
		std::string("1,2,3"),
		std::string("9999999999999999999,???,1048"),
	};

	for (std::string input : input) {
		std::vector<int> dArrLocalValue;
		std::stringstream ss(input);
		while (!ss.eof()){ //while (ss.good()) { works also fine
			REQUIRE( (dArrLocalValue.size() < SPECTRUM_SIZE) );
			std::string sub;
			std::getline(ss, sub, ',');
			//std::stoi throws a exception if sub is nan or to big,
			//atoi from the old version just inserts a 0 without any feedback
			try{
				dArrLocalValue.push_back(std::stoi(sub));
			}
			catch (const std::exception& e){
				dArrLocalValue.push_back(0);
				ERROR_LOG << e.what() << std::endl;
			}
		}
		INFO_LOG << "input was : " << input << "\nresult : " << std::endl;
		for (auto value : dArrLocalValue) {
			std::cout << std::to_string(value) << " ";
		}
		std::cout << '\n';
		REQUIRE( (dArrLocalValue.size() == SPECTRUM_SIZE) );
	}
}
```
## conclusion
Get rid of these iPos, iOldPos and i.

Also have c++ check the input string sub with ```std::stoi``` for exceptions (nan, or too big).

Get rid of the ```while(true)``` loop.

