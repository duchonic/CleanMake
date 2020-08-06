/**
 * @file
 * This header file declares the function to create one instance of the Lightsource state machine.
 * The state machine is configured with a set of function pointers representing the non-default
 * actions and guards of the state machine. Some of these functions may also be declared in
 * this header file in accordance with the configuration of the state machine in the FW Profile
 * Editor. In the latter case, the user has to provide an implementation for these functions
 * in a user-supplied body file.
 *
 * This header file has been automatically generated by the FW Profile Editor.
 * The state machine created by this file is shown in the figure below.
 * @image html Lightsource.png
 *
 * @author FW Profile code generator version 5.25
 * @date Created on: Jun 19 2020 15:1:22
 */

 /* Make sure to include this header file only once */
#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

/* FW Profile function definitions */
#include "FwSmConstants.h"

/* State identifiers */
#define Lightsource_ERROR (1)		/**< The identifier of state ERROR in State Machine Lightsource */
#define Lightsource_OFF (2)		/**< The identifier of state OFF in State Machine Lightsource */
#define Lightsource_ON (3)		/**< The identifier of state ON in State Machine Lightsource */
#define Lightsource_PREHEAT (4)		/**< The identifier of state PREHEAT in State Machine Lightsource */

/* The identifiers of transition commands (triggers) */
#define Execute (0) /**< The identifier of the Execute transition trigger */
#define trigger (15)/**< The identifier of the trigger transition trigger */

/**
 * Create a new state machine descriptor.
 * This interface creates the state machine descriptor statically.
 * It creates a single static instance of the state machine.
 * The function should only be called once.
 * If it is called several times, it always reconfigures and returns the same instance.
 * @param smData the pointer to the state machine data.
 * A value of NULL is legal (note that the default value of the pointer
 * to the state machine data when the state machine is created is NULL).
 * @return the pointer to the state machine descriptor
 */
FwSmDesc_t LightsourceCreate(void* smData);

#endif /* Lightsource_H_ */