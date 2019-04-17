#pragma once

#include <string>
#include <stdexcept>

// Forward declaration
class ISingleton;

class SingletonCollector {

public:

    // Constructor
    SingletonCollector();

    // Destructor
    virtual ~SingletonCollector();

	// Add a singleton to the collection
	void addSingleton(ISingleton* pSingleton);

	// Delete all singleton's in the collection
	void deleteAll();

	// Check if the object is available
	static bool available();

	// Get the one and only one instance
	static SingletonCollector* getInstance();

protected:

	static SingletonCollector* _instance;

};

///////////
//Exception:
class SingletonCollectorInstanceAlreadyExist: public std::logic_error {
	public:
		// Constructor
		SingletonCollectorInstanceAlreadyExist(const std::string& message)
			: logic_error(message) {
			}
};
