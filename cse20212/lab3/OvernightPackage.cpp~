/*
	John F. Lake, Jr.  OvernightPackage.cpp
	Implementation for the OvernightPackage class
*/
#include "Package.h" 
#include "OvernightPackage.h"
#include <iostream> 

//Constructor, which uses member initialization list syntax to implement the base class Constructor
OvernightPackage::OvernightPackage(string toN, 
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
			     double eC): Package(toN,fromN,toA,fromA,toC,fromC,toS,fromS,toZ,fromZ,w,c){ //MIL syntax
			     
	//Check if the extra cost per ounce is greater than or equal to zero:
	if(eC>=0){
		extraCostPerOunce= eC; 
	}
	else{
		extraCostPerOunce = 0; 
		cout<<"The extra fee cannot be negative!"<<endl; 
	}
}
//Accessor method to get the extra cost per ounce 
double OvernightPackage::getExtraCostPerOunce(){
	return extraCostPerOunce; 
}

//Calculate the cost for the package, using the original method AND the extra cost per ounce 
double OvernightPackage::CalculateCost(){
	double cost = Package::CalculateCost(); //Call the base class method
	cost+= getWeight()*getExtraCostPerOunce(); 
	return cost; 
}
