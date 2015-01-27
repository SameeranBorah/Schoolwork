/*
	John F. Lake, Jr.  main.cpp
	Driver for lab 3 - Tests all parts
*/
#include "BankAccount.h" 
#include "Package.h" 
#include "TwoDayPackage.h"
#include "CheckingAccount.h" 
#include "OvernightPackage.h"
#include "CompTwoDayPackage.h"
#include "CompOvernightPackage.h"
#include "IRA.h"
#include <iostream> 
using namespace std; 


int main(){
	//PART 1:  (Just added to show that the bank accounts work)
	cout <<"PART 1:"<<endl; 
	//Making instances of the base class and each derived class, and calling the print function from each: 
	BankAccount bank;  //Base class default constructor
	bank.print(); 
	
	cout <<endl<<endl; 
	
	//Default Constructor call: 
	CheckingAccount acct;
	acct.print();
	 
	cout<<endl<<endl; 
	
	//Default constructor: 
	IRA newIRA; 
	newIRA.print(); 
	
	
	//PART 2:  (Shows/displays the contents of each derived package class.)
	cout<<endl<<"Part 2:"<<endl; 
	//Declare objects of each package type with the default constructor: the base class, and the two derived classes. 
	Package r; 
	TwoDayPackage d; 
	OvernightPackage o; 

	//Each call to CalculateCost() will return a different value, even though the default values (weight, etc) are the same.  
	cout<<"The cost of sending a standard package is $"<< r.CalculateCost() <<endl; 
	cout <<"The cost of sending it in 2 days is $"<< d.CalculateCost() <<endl; 
	cout <<"The overnight cost is $"<< o.CalculateCost() <<endl;


	//PART 3A: (Composition with the CompTwoDayPackage and CompOvernightPackage classes): 
	cout<<endl<<"Part 3A (Composition):"<<endl;
	CompTwoDayPackage compD;
	CompOvernightPackage compO;  
	compD.print();
	compO.print();
	
	//PART 3B: (Object pointers)
	cout <<endl<<"Part 3B (Polymorphism):"<<endl; 
	Package* packages[6]; //Creates a static array of 6 base class pointers 
	
	int cost=0; 
	//Initialize the first 3 to be TwoDayPackage objects: 
	for(int i=0;i<3;i++){
		TwoDayPackage p; 
		packages[i] = &p;
		cost+=packages[i]->CalculateCost(); //Calls the derived class (TwoDayPackage::CalculateCost();)
	}
	//Initialize the others to be OvernightPackage objects: 
	for(int i=3;i<6;i++){
		OvernightPackage pa; 
		packages[i] = &pa;
		cost+=packages[i]->CalculateCost(); //Calls OvernightPackage::CalculateCost();
	}

	//Print the result
	cout<<"The total cost to ship 3 overnight packages and 3 two day packages is $"<<cost<<endl; 
}
