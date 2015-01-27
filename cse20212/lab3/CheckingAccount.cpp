/*
	John F. Lake, Jr.  CheckingAccount.cpp
	Implementation for the Checking Account class
*/
#include "CheckingAccount.h"
#include <iostream>
#include <string> 
using namespace std; 

//Default constructor, which initializes unique and inherited variables: 
CheckingAccount::CheckingAccount(){
	balance = 0; 
	PIN = 1234; 
	accountNumber = 12345678; 
	bankName = "Joe's Checks and Balances"; 
	overdraftFee = 25.00; 
	minBalance = 0; 
}
//Non-Default constructor: 
CheckingAccount::CheckingAccount(double b, int p, int a, string bn,double of,double mb){
	balance = b; 
	PIN = p; 
	accountNumber = a; 
	bankName = bn; 
	overdraftFee = of; 
	minBalance = mb; 
}
//Print some information about the account to the user: 
void CheckingAccount::print(){
	cout << "Welcome to "<<bankName<<endl; 
	cout << "This Checking Account is No. " << accountNumber<< " and the PIN is: "<<PIN<<endl; 
	cout << "The balance is $"<<balance<< " which is "<<((balance>minBalance)?"over":"under")<< " the minimum balance."<<endl; 
}
