#include "OperationFactory.h"
#include "SysOperation.h"

// Constructor
OperationFactory::OperationFactory() {
}

// Destructor
OperationFactory::~OperationFactory() {
}

// Get the active IOperation
IOperation* OperationFactory::getOperation() {
	return SysOperation::getInstance();
}


