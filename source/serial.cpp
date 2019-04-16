#include "serial.h"
#include <iostream>

Serial::Serial(){
	std::cout << "constructor" << '\n';
}

Serial::~Serial(){
	std::cout << "deconstructor" << '\n';
}
