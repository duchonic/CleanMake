#include "logger.h"
#include <iostream>

Logger::Logger(){
	std::cout << "constructor" << '\n';
}

Logger::~Logger(){
	std::cout << "deconstructor" << '\n';
}
