/*
	John F. Lake, Jr.  CompTwoDayPackage.cpp
	Implementation for the CompTwoDayPackage class
*/
#include "Package.h"
#include "CompTwoDayPackage.h"
#include <iostream> 
 

//Constructor
CompTwoDayPackage::CompTwoDayPackage(double fee){  //Checks if the fee is legitimate
	if(fee>0){
		twoDayFee = fee; 
	}
	else{
		twoDayFee = 0; 
		cout << "Cannot have a negative fee!!!"<<endl; 
	}
}

double CompTwoDayPackage::getTwoDayFee(){
	return twoDayFee; 
}

//Calculate the cost, based on weight and the two day flat rate. 
double CompTwoDayPackage::CalculateCost(){
	double cost = packageData.Package::CalculateCost(); //Using the base class function in the Package object 
	cost+=getTwoDayFee(); 
	return cost; 
}

	//Tests that the composition is working. 
void CompTwoDayPackage::print(){
	cout << "This 2 day package is going to " << packageData.getToAddress() << " and will cost $"<< CalculateCost()<<endl;
}



