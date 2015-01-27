#!/usr/bin/perl
#John F. Lake, Jr. 
#Part 2
#grading.pl
#This calculates the final grades of different students 


#Open the file to read from, and make a file to write to. 
open (INFILE, $ARGV[0]); 
open (OUTFILE, ">FinalGrades.tex"); 
my $lineNo = 0; 


#set up the .tex file: 
print OUTFILE "\\documentclass{article}\n"; 
print OUTFILE "\\begin{document}\n"; 
print OUTFILE "\\begin{tabular}{l | l | l | l | l | l}\n";
print OUTFILE "Student Name & Homework & Quiz & Exam1 & Exam2 & Final Grade \\\\ \n"; 


#For each line in the file: 
foreach $line (<INFILE>){
	@wol = split(/,/,$line);  #Split each line into multiple lines. 
	if($lineNo == 0){
		 $lineNo += 1;   #Don't read the first line. 
	}
	else{
		my $name = $wol[0]; 
		my $hwPnts = $wol[1]+$wol[2]+$wol[3]+$wol[4]+$wol[5]+$wol[6]+$wol[7]+$wol[8];
		my $hwAvg = ($hwPnts)/440 * 100; 
		my $quizPnts =$wol[9] + $wol[10];
		my $quizAvg = ($quizPnts) /100 * 100; 
		my $exam1Avg = $wol[11]; 
		my $exam2Avg = $wol[12]; 
		

		$finalAvg = (($hwAvg * 0.5) + ($quizAvg * 0.1) + ($exam1Avg * 0.2) + ($exam2Avg * 0.2));
		
		
		if($finalAvg >= 94){
			$grade = "A"; 
		}
		elsif ($finalAvg <94 && $finalAvg >= 90){
			$grade = "A-"; 
		}
		elsif ($finalAvg <90 && $finalAvg >= 87){
			$grade = "B+"; 
		}
		elsif ($finalAvg <87 && $finalAvg >= 84){
			$grade = "B"; 
		}
		elsif ($finalAvg <84 && $finalAvg >= 80){
			$grade = "B-"; 
		}
		elsif ($finalAvg <80 && $finalAvg >= 77){
			$grade = "C+"; 
		}
		elsif ($finalAvg <77 && $finalAvg >= 74){
			$grade = "C"; 
		}
		elsif ($finalAvg <74 && $finalAvg >= 70){
			$grade = "C-"; 
		}
		elsif ($finalAvg <70 && $finalAvg >= 60){
			$grade = "D"; 
		}
		else{
			$grade = "F"; 
		}
		#Enter information into the .tex file. 
		printf OUTFILE "$name & %.0f\\% & %.0f\\% & %.0f\\% & %.0f\\% & $grade \\\\ \n",$hwAvg, $quizAvg, $exam1Avg, $exam2Avg; 
		
		
		
		
		
	}
	
}

#finish up the .tex file: 
print OUTFILE "\\end{tabular}\n"; 
print OUTFILE "\\end{document}\n"; 
close INFILE; 
close OUTFILE; 

system('pdflatex FinalGrades.tex'); 
