/*
	John F. Lake, Jr. CompTwoDayPackage.h
	Interface for the CompTwoDayPackage class - uses composition instead of inheritance
*/
#ifndef COMPTWODAYPACKAGE_H
#define COMPTWODAYPACKAGE_H
#include "Package.h"

 
//Two day package class: inherits from the Package class
class CompTwoDayPackage{
	public: 
		CompTwoDayPackage(double=5);	
		Package packageData; //Composition - "has-a" relationship with the Package class
		double CalculateCost();
		double getTwoDayFee(); 
		void print(); //Used to test the class
	private: 
		double twoDayFee;  //Additional fixed cost for sending a package in two days
};
#endif
