// In a Catch project with multiple files, dedicate one file to compile the
// source code of Catch itself and reuse the resulting object file for linking.

#include "catch.h"
#include <iostream>

using namespace std;

class Account {
public:
	Account(double d)
	{
		cout << "account constructor" << endl;
		_balance = d;
	}
	virtual ~Account()
	{
		cout << "account deconstructor" << endl;
	}
	virtual double GetBalance()
	{
		cout << "GetBalance from account" << endl;
		return _balance;
	}
	virtual void PrintBalance()
	{
		cerr << "Error. Balance not available for base type." << endl;
	}
private:
	double _balance;
};

class CheckingAccount : public Account
{
public:
	CheckingAccount(double d) : Account(d) 
	{
		cout << "constructor checkingAccount" << endl;
	}
	void PrintBalance()
	{
		cout << "Checking account balance: " << GetBalance() << endl;
	}
};

class SavingsAccount : public Account {
public:
	SavingsAccount(double d) : Account(d) 
	{
		cout << "constructor savingAccount" << endl;
	}
	void PrintBalance()
	{ 
		cout << "Savings account balance: " << GetBalance() << endl;
	}
};


TEST_CASE("virtuals 1") {
	// Create objects of type CheckingAccount and SavingsAccount.
	CheckingAccount checking(100.00);
	SavingsAccount  savings(1000.00);

	// Call PrintBalance using a pointer to Account.
	Account* pAccount = &checking;
	pAccount->PrintBalance();

	// Call PrintBalance using a pointer to Account.
	pAccount = &savings;
	pAccount->PrintBalance();
}

SCENARIO("virtuals 2") {
	GIVEN("a vector with som eitems") {
		WHEN("size is reduced") {
			THEN("size changes ") {

			}
		}
	}
}
