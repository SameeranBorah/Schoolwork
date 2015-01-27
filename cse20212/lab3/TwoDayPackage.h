/*
	John F. Lake, Jr. TwoDayPackage.h
	Interface for the TwoDayPackage class. 
*/
#ifndef TWODAYPACKAGE_H
#define TWODAYPACKAGE_H
#include "Package.h"

 
//Two day package class: inherits from the Package class
class TwoDayPackage: public Package{
	public: 
		TwoDayPackage(string="Joe",      //To
			      string="Jim",	   //From
			      string="123 Main", //To this address
			      string="456 Main", //From this address
			      string="La Porte",  //To this city
			      string="Notre Dame", //From this city
			      string="IN", 		//To this state
			      string="IN",		//From this state	
			      int=46350,		//To this zip code
			      int=46556,		//From this zip code
			      double=1,		//Weight
			      double=5,		//Cost per ouce
			      double=5); 	//Two Day Fee; 
			  
		double CalculateCost();
		double getTwoDayFee(); 
	private: 
		double twoDayFee;  //Additional fixed cost for sending a package in two days
};
#endif
