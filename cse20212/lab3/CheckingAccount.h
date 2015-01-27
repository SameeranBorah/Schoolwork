/*
	John F. Lake, Jr. CheckingAccount.h
	Interface for CheckingAccount class (A derived class from BankAccount.h)
*/
#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include <string>
#include "BankAccount.h"
using namespace std; 

class CheckingAccount: public BankAccount{
	public: 
		//Constructors
		CheckingAccount(); 
		CheckingAccount(double, int, int, string,double,double); 
		
		//Prints info
		void print(); 
	private: 
		//Unique to the derived class: 
		double overdraftFee;  
		double minBalance; 
		
};
#endif
