/*
	John F. Lake, Jr. CompOvernightPackage.h
	Interface for the CompOvernightPackage class (uses composition)
*/
#ifndef COMPOVERNIGHTPACKAGE_H
#define COMPOVERNIGHTPACKAGE_H
#include "Package.h" 


//CompOvernightPackage class
class CompOvernightPackage{
	public: 
		CompOvernightPackage(double=7); //Default fee for overnight delivery is $7/ounce
		Package packageData; //Object holding the info for this class
		double CalculateCost(); 
		double getExtraCostPerOunce(); 
		void print(); //Tests the class
	private: 
		double extraCostPerOunce; //New cost for shipping overnight
};
#endif
