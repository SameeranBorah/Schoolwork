#!/usr/bin/perl

#John F. Lake, Jr. 
#baseball2.pl
#Holds information about 3 perl modules- Team, Player, and League
#Just like baseball.pl, but uses League.pm.
use Player;
use League;  
use Team; 


my $file = $ARGV[0];
my %teams = {}; 
my $league = new League; 


#Add all of the team info
while (<>){
	@person = split(/,/,$_);  
	$p = new Player($person[0],$person[1], $person[2],$person[3],$person[4]);
	$name = $p->getFullName; 
	$salary = $p->getSalary; 
	$position = $p->getPosition; 
	$team = $p->getTeam;  
	$league->addPlayer($team,$p);    #add players via the league subroutine addPlayer
} 


my $val = 1;   #loop condition variable
while ($val == 1){

	print "\n\n\nEnter 'getRoster [Teamname]' for a team roster.\n"; 
	print "Enter 'getTeamSalaryTotal [Teamname]' for a team salary.\n";
	print "Enter 'stop' to end the program.\n\n"; 
	$input = <>;
	$count = 1; 
	$teamName = "";
	
	#Correctly get the input (some team names are 2 words; some are 3 words.  This accounts for that.)
	@inputTokens = split(/ /,$input); 
	foreach (@inputTokens){
		chomp($_); 
		if($count == 1){
			$command = $_; 
		}
		elsif($count == 2){
			$teamName = $_; 
		}
		else{
			$teamName = $teamName . " " . $_; 
		}
		$count = $count + 1; 
	} 
	


	#Perform the appropriate command:
	if($command eq 'STOP' or $command eq "stop"){
		$val = 0; 
	}
	elsif ($command eq "getRoster"){    #Two words to every team 
		print "Team Roster for $teamName:\n\n"; 
		@myRoster = $league->getTeam($teamName)->getRoster;          #calls a league subroutine
		foreach (@myRoster){
			chomp($_); 
			print "$_ \n";
		}
	}
	elsif ($command eq "getTeamSalaryTotal"){
		print "Total salary for $teamName:\n\n"; 
		$totalSal = $league->getTeam($teamName)->getSumOfPlayersSalary;    #calls a league subroutine
		print "\$$totalSal\n\n";
		
	}
	else{
		print "ENTER A CORRECTLY FORMATTED INPUT!!!\n"; 
	}
}

#@myRoster = $teams{'Chicago Cubs'}->getRoster; 
#foreach (@myRoster){
	#print "$_  \n";
#}
#$totalSal = $teams{'Chicago Cubs'}->getSumOfPlayersSalary; 
#print "$totalSal\n";

