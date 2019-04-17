#include "SingletonCollector.h"

SingletonCollector::SingletonCollector()
{}

SingletonCollector::~SingletonCollector()
{}

void SingletonCollector::addSingleton(ISingleton* pSingleton)
{}

void SingletonCollector::deleteAll()
{}

bool SingletonCollector::available()
{
	return false;
}

SingletonCollector* SingletonCollector::getInstance()
{
	return 0;
}
