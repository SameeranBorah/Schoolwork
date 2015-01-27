/*
	John F. Lake, Jr.  BankAccount.h
	Interface for the BankAccount base class
*/
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>
using namespace std; 

class BankAccount{
	public: 
		//Constructors
		BankAccount(); 
		BankAccount(double,int,int,string); 
		
		//Prints a small message to the user
		void print(); 
	protected:  
		//Inherited variables
		double balance; 
		int PIN;  
		int accountNumber; 
		string bankName; 
};
#endif
