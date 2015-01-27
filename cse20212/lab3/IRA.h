/*
	John F. Lake, Jr.  IRA.h
	Interface for the IRA class (Individual Retirement Account), derived from BankAccount.h
*/
#ifndef IRA_H
#define IRA_H
#include <string>
#include "BankAccount.h"
using namespace std; 
 
 
class IRA: public BankAccount{
	public: 
		//Constructors
		IRA(); 
		IRA(double, int, int, string,double,double);
		
		//Print to the user
		void print(); 
	private: 
		//Unique to the derived IRA class
		double tradeFee; 
		double maxContribution;  
};
#endif 
