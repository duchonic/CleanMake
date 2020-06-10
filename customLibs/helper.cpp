#include "helper.h"
#include <iostream>
#include <fstream>
#include <cassert>

Helper::Helper(){
  STATE_LOG << "constructor" << '\n';

  std::string configFile = std::string("communication.json");
  std::string line;
  std::ifstream myfile(configFile);

	while (getline(myfile, line))
	{
	  std::cout << line << '\n';
	}
	myfile.close();
}

Helper::~Helper(){
  STATE_LOG << "deconstructor" << '\n';
}

void Helper::test(void) 
{
	bool input = true;
	bool test = true;

	if (input != test) {
		return;
	}

	if (input != test) {
		DEBUG_LOG << "a" << std::endl;
	}
	else {
		DEBUG_LOG << "b" << std::endl;
	}
}
