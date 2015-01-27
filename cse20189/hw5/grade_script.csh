#!/bin/csh
#John F. Lake, Jr. 
#This script will check and grade the assignments of the students in the dropbox directory


#check if there is a calculator directory
find ./dropbox | grep -Ev '(calculator)|(calc\.csh)|(dropbox)$' > names
foreach name ("`cat names`")	
	set student = "`echo $name | sed  's/^\..*\///g'`"  	 #Uses sed to get the actual name of the student for printing purposes
	if(!(-e "$name/calculator" )) then			 #If the calculator directory doesn't exist, make it and make a comments file
		mkdir $name/calculator   			
		echo "/calculator was not in the directory of $student ; this was created by a script." > $name/calculator/comments
	else if(!(-e "$name/calculator/calc.csh")) then          #If the calc.csh file is not present, make a comments file stating it isn't present
		set date = `date +"%m-%d-%y"`
		echo "No submission from $student at $date" > $name/calculator/comments
	else							 #If the file exists, test if it's executable and then put the results in a file
		if(!(-x $name/calculator/calc.csh))then
			echo "Not executable. -5 points. " > $name/calculator/comments
			echo "Results for $student calculator script:" > $name/calculator/results
			csh $name/calculator/calc.csh /afs/nd.edu/coursesp.14/cse/cse20189.01/files/hw5/calc >> $name/calculator/results
			echo "Testing complete for $student" >> $name/calculator/results
		else
			echo "Results for $student calculator script:" > $name/calculator/results
			$name/calculator/calc.csh /afs/nd.edu/coursesp.14/cse/cse20189.01/files/hw5/calc >> $name/calculator/results	
			echo "Testing complete for $student" >> $name/calculator/results
		endif
	endif
end
rm names  #remove temp file used above. 





