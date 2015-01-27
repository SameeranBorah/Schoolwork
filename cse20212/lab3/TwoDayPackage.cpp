/*
	John F. Lake, Jr.  TwoDayPackage.cpp
	Implementation for the TwoDayPackage class
*/
#include "Package.h"
#include "TwoDayPackage.h"
#include <iostream> 
 

//Constructor, which uses member initialization list syntax to implement the base class Constructor
TwoDayPackage::TwoDayPackage(string toN, 
			     string fromN,
			     string toA,
			     string fromA,
			     string toC,
			     string fromC,
			     string toS, 
			     string fromS,
			     int toZ, 
			     int fromZ,
			     double w, 
			     double c,
			     double tD): Package(toN,fromN,toA,fromA,toC,fromC,toS,fromS,toZ,fromZ,w,c){ //MIL syntax
	//Check if the fee is greater than or equal to zero.  
	if(tD>=0){
		twoDayFee = tD; 
	}
	else{
		twoDayFee = 0; 
		cout<<"The two day fee cannot be negative!"<<endl; 
	}
}

//Accessor method for the two day fee
double TwoDayPackage::getTwoDayFee(){
	return twoDayFee; 
}

//Calculate the cost, based on weight and the two day flat rate. 
double TwoDayPackage::CalculateCost(){
	double cost = Package::CalculateCost(); //Using the base class function.  
	cost+=getTwoDayFee(); 
	return cost; 
}



