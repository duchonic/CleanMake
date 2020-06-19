/* Lightsource function definitions */
#include "LightsourceManager.h"

#include "FwSmConstants.h"
#include <iostream>

void onEntry(FwSmDesc_t smDesc) {
	std::cout << "onEntry" << std::endl;
}
void offEntry(FwSmDesc_t smDesc) {
	std::cout << "offEntry" << std::endl;
}
void preheatEntry(FwSmDesc_t smDesc) {
	std::cout << "preheatEntry" << std::endl;
}
void errorEntry(FwSmDesc_t smDesc) {
	std::cout << "errorEntry" << std::endl;
}


FwSmBool_t lightsourceOn(FwSmDesc_t smDesc) {
	return rand()%2==0 ? true : false;
}
FwSmBool_t lightsourceOff(FwSmDesc_t smDesc) {
	return rand() % 2 == 0 ? true : false;
}
FwSmBool_t lightsourcePreheatDone(FwSmDesc_t smDesc) {
	return rand() % 2 == 0 ? true : false;
}
FwSmBool_t lightsourceError(FwSmDesc_t smDesc) {
	return false; //rand() > 0x7fff / 2 ? true : false;
}