// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"


/** Lightsource function definitions */
#include "Lightsource.h"
#include "LightsourceManager.h"

/** FW Profile function definitions */
#include "FwSmConstants.h"
#include "FwSmSCreate.h"
#include "FwSmConfig.h"
#include "FwSmCore.h"



FwSmDesc_t smDesc;


TEST_CASE("create statemachine"){
	/** Define the state machine descriptor (SMD) */
	smDesc = LightsourceCreate(0);

	/** Check that the SM is properly  */
	REQUIRE(FwSmCheckRec(smDesc) == smSuccess);
}


SCENARIO("run statemachine") {
	for (int runs=20;runs>0;runs--) {
		/** Start the SM, send a few transition commands to it, and execute it */
		FwSmStart(smDesc);
		FwSmMakeTrans(smDesc, trigger);
	}
}