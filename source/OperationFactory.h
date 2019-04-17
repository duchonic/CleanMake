#pragma once

// forward declarations
#include "interface/IOperation.h"


class OperationFactory {

public:

	// Get the active IOperation
	static IOperation* getOperation();

protected:

    // Constructor
    OperationFactory();

    // Destructor
    virtual ~OperationFactory();

};
