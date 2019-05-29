#ifndef IDRIVERMANAGER_H
#define IDRIVERMANAGER_H

//
// IDriverManager
// Place a description of the class here
// @author Matthias Künzi
//
class IDriverManager {

public:

    // Destructor
    virtual ~IDriverManager() {}

    // initialize all drivers
    virtual void initDrivers() = 0;

    // run all drivers
    virtual void runDrivers() = 0;

    // close all drivers
    virtual void resetDrivers() = 0;

    // close all drivers
    virtual void closeDrivers() = 0;
};

#endif //#ifndef IDRIVERMANAGER_H
