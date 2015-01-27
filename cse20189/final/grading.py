#!/usr/bin/python
#John F. Lake, Jr. 
#Part 2
#grading.py
#This calculates the final grades of different students 
import sys
import subprocess
import os



#Open the file to read from, and make a file to write to. 
INFILE = open(sys.argv[1],"r"); 
OUTFILE = open("FinalGrades.tex","wr"); 
lineNo = 0; 


#set up the .tex file: 


OUTFILE.write("\\documentclass{article}\n"); 
OUTFILE.write( "\\begin{document}\n"); 
OUTFILE.write( "\\begin{tabular}{l | l | l | l | l | l}\n");
OUTFILE.write( "Student Name & Homework(\%) & Quiz(\%) & Exam1(\%) & Exam2(\%) & Final Grade \\\\ \n"); 


#For each line in the file: 
for line in INFILE:	
	
	wol = line.split(","); 
	if(lineNo == 0):
		 lineNo += 1;   #Don't read the first line. 
	
	else:
		name = wol[0]; 
		hwPnts = int(wol[1])+int(wol[2])+int(wol[3])+int(wol[4])+int(wol[5])+int(wol[6])+int(wol[7])+int(wol[8]);
		hwAvg = (hwPnts*1.0)/440 * 100; 
		quizPnts =int(wol[9]) + int(wol[10]);
		quizAvg = (quizPnts*1.0) /100 * 100; 
		exam1Avg = int(wol[11]); 
		exam2Avg = int(wol[12]); 
		

		finalAvg = ((hwAvg * 0.5) + (quizAvg * 0.1) + (exam1Avg * 0.2) + (exam2Avg * 0.2));
		
		
		if(finalAvg >= 94):
			grade = "A"; 
		
		elif (finalAvg <94 and finalAvg >= 90):
			grade = "A-"; 
		
		elif (finalAvg <90 and finalAvg >= 87):
			grade = "B+"; 
		
		elif (finalAvg <87 and finalAvg >= 84):
			grade = "B"; 
		
		elif (finalAvg <84 and finalAvg >= 80):
			grade = "B-"; 
		
		elif (finalAvg <80 and finalAvg >= 77):
			grade = "C+"; 
		
		elif (finalAvg <77 and finalAvg >= 74):
			grade = "C"; 
		
		elif (finalAvg <74 and finalAvg >= 70):
			grade = "C-"; 
		
		elif (finalAvg <70 and finalAvg >= 60):
			grade = "D"; 
		
		else:
			grade = "F"; 
		myIn = "%s & %.0f & %.0f & %.0f & %.0f & %s \\\\ \n" % (name,hwAvg,quizAvg,exam1Avg,exam2Avg,grade); 
		OUTFILE.write(myIn); 
		#Enter information into the .tex file. 
		



#finish up the .tex file: 
OUTFILE.write( "\\end{tabular}\n"); 
OUTFILE.write( "\\end{document}\n"); 
INFILE.close(); 
OUTFILE.close();



subprocess.call(["pdflatex", "FinalGrades.tex"]);


