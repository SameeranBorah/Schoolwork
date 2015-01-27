#!/usr/bin/python
#John F. Lake, Jr. 
#fcalc.py
#HW 11

def main(): 
	print "This program will tell you what percentage of the calories"    #Message telling user what the program does
	print "in a serving of food are from the fat content.\n"
	
	gramsFat = int(input("How many grams of fat are in one serving?   "))	#Get the inputs from the user. 
	totalCals = int(input("How many calories are in one serving?   "))
	
	
	calsFromFat = gramsFat*9		#Get the total calories from the fat (each gram is 9 calories.)
	percentOfCalsFromFat = (calsFromFat*1.0/totalCals) * 100  #1.0 is to prevent the division from being zero
	
	
	#Print the result to the user, with the percentage formatted to one decimal place. 
	print "A food with", gramsFat, "grams of fat and", totalCals, "calories per serving has", "%0.1f" % percentOfCalsFromFat,"% of those calories from fat." 
	


if __name__ == '__main__':
	main()
