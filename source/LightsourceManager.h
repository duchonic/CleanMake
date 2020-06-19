#ifndef ASDF
#define ASDF

#include "FwSmConstants.h"

void onEntry(FwSmDesc_t);
void offEntry(FwSmDesc_t);
void preheatEntry(FwSmDesc_t);
void errorEntry(FwSmDesc_t);

FwSmBool_t lightsourceOn(FwSmDesc_t);
FwSmBool_t lightsourceOff(FwSmDesc_t);
FwSmBool_t lightsourcePreheatDone(FwSmDesc_t);
FwSmBool_t lightsourceError(FwSmDesc_t);

#endif