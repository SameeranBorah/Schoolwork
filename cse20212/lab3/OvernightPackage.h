/*
	John F. Lake, Jr. OvernightPackage.h
	Interface for the OvernightPackage class. 
*/
#ifndef OVERNIGHTPACKAGE_H
#define OVERNIGHTPACKAGE_H
#include "Package.h" 


//OvernightPackage class inherits from the Package class
class OvernightPackage : public Package{
	public: 
		OvernightPackage(string="Joe",      //To
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
			      double=7); 	//Extra cost per ounce Fee; 
		double CalculateCost(); 
		double getExtraCostPerOunce(); 
		
	private: 
		double extraCostPerOunce; //New cost for shipping overnight
};
#endif
