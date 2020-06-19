/**
 * @file Lightsource.c
 *
 * @author FW Profile code generator version 5.25
 * @date Created on: Jun 19 2020 8:56:30
 */

/* Lightsource function definitions */
#include "Lightsource.h"
#include "LightsourceManager.h"

/* FW Profile function definitions */
#include "FwSmSCreate.h"
#include "FwSmConfig.h"

#include <stdlib.h>

/* ----------------------------------------------------------------------------------------------------------------- */
FwSmDesc_t LightsourceCreate(void* smData)
{
	const FwSmCounterU2_t N_OUT_OF_ON = 2;	/* The number of transitions out of state ON */
	const FwSmCounterU2_t N_OUT_OF_PREHEAT = 2;	/* The number of transitions out of state PREHEAT */
	const FwSmCounterU2_t N_OUT_OF_OFF = 2;	/* The number of transitions out of state OFF */
	const FwSmCounterU2_t N_OUT_OF_ERROR = 0;	/* The number of transitions out of state ERROR */
	const FwSmCounterU2_t CHOICE1 = 1;		/* The identifier of choice pseudo-state CHOICE1 in State Machine Lightsource */
	const FwSmCounterU2_t N_OUT_OF_CHOICE1 = 1;	/* The number of transitions out of the choice-pseudo state CHOICE1 */

	/** Create state machine smDesc */
	FW_SM_INST(smDesc,
		4,	/* NSTATES - The number of states */
		1,	/* NCPS - The number of choice pseudo-states */
		8,	/* NTRANS - The number of transitions */
		4,	/* NACTIONS - The number of state and transition actions */
		4	/* NGUARDS - The number of transition guards */
		);
	FwSmInit(&smDesc);

	/** Configure the state machine smDesc */
	FwSmSetData(&smDesc, smData);
	FwSmAddState(&smDesc, Lightsource_ON, N_OUT_OF_ON, &onEntry, NULL, NULL, NULL);
	FwSmAddState(&smDesc, Lightsource_PREHEAT, N_OUT_OF_PREHEAT, &preheatEntry, NULL, NULL, NULL);
	FwSmAddState(&smDesc, Lightsource_OFF, N_OUT_OF_OFF, &offEntry, NULL, NULL, NULL);
	FwSmAddState(&smDesc, Lightsource_ERROR, N_OUT_OF_ERROR, &errorEntry, NULL, NULL, NULL);
	FwSmAddChoicePseudoState(&smDesc, CHOICE1, N_OUT_OF_CHOICE1);
	FwSmAddTransStaToSta(&smDesc, trigger, Lightsource_ON, Lightsource_ERROR, NULL, &lightsourceError);
	FwSmAddTransStaToSta(&smDesc, trigger, Lightsource_ON, Lightsource_OFF, NULL, &lightsourceOff);
	FwSmAddTransStaToSta(&smDesc, trigger, Lightsource_PREHEAT, Lightsource_ON, NULL, &lightsourcePreheatDone);
	FwSmAddTransStaToSta(&smDesc, trigger, Lightsource_PREHEAT, Lightsource_ERROR, NULL, &lightsourceError);
	FwSmAddTransStaToSta(&smDesc, trigger, Lightsource_OFF, Lightsource_PREHEAT, NULL, &lightsourceOn);
	FwSmAddTransStaToSta(&smDesc, trigger, Lightsource_OFF, Lightsource_ERROR, NULL, &lightsourceError);
	FwSmAddTransIpsToCps(&smDesc, CHOICE1, NULL);
	FwSmAddTransCpsToSta(&smDesc, CHOICE1, Lightsource_OFF, NULL, NULL);

	return &smDesc;
}


