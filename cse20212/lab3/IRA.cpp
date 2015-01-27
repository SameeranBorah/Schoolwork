/*
	John F. Lake, Jr.  IRA.cpp
	Implementation for the IRA class
*/
#include "IRA.h"
#include <string> 
#include <iostream>
using namespace std; 

//Default constructor; initializes inherited AND unique variables
IRA::IRA(){
	tradeFee = 7; 
	maxContribution = 5000; 
	balance = 0;
	PIN = 1234; 
	accountNumber = 12345678; 
	bankName = "Infrared Accounts"; 
}
//Non-default constructor: 
IRA::IRA(double openingBal, int p, int acctNum, string bName, double tf, double mc){
	tradeFee = tf;
	maxContribution = mc; 
	balance = openingBal; 
	PIN = p; 
	accountNumber = acctNum; 
	bankName = bName; 	
}

void IRA::print(){
	cout << "This IRA account at "<<bankName << " contains $"<<balance<<endl; 
	cout << "The max contribution per year is $"<<maxContribution<<endl; 
	cout << "It costs $"<<tradeFee << " to make trades on this account."<<endl; 

}
