#include "helper.h"
#include <iostream>
#include <fstream>
#include <cassert>


Helper::Helper(){
  STATE_LOG << "constructor" << '\n';

  std::string configFile = std::string("communication.json");
  std::string line;
  std::ifstream myfile(configFile);
  //assert(myfile.is_open());

	  while (getline(myfile, line))
	  {
		  std::cout << line << '\n';
	  }
	  myfile.close();
  
  
}

Helper::~Helper(){
  STATE_LOG << "deconstructor" << '\n';
}
