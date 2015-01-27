#!/usr/bin/perl

#John F. Lake, Jr. 
#baseball.pl
#Holds information about 2 perl modules- Team and Player
use Player; 
use Team; 


my $file = $ARGV[0];
my %teams = {}; 

while (<>){
	@person = split(/,/,$_);  
	$p = new Player($person[0],$person[1], $person[2],$person[3],$person[4]);
	$name = $p->getFullName; 
	$salary = $p->getSalary; 
	$position = $p->getPosition; 
	$team = $p->getTeam;  
		
		
	#team exists in the list
	if(exists($teams{$team})){	
		$teams{$team}->addPlayer($p); 				
	}
	else{
		my $myTeam = new Team{$team}; 
		$myTeam->addPlayer($p);
		$r = $myTeam->getTeamName; 
		$teams{$team} = $myTeam; 
	}	
}

my $val = 1; 
while ($val == 1){
	print "\n\n\nEnter 'roster [Teamname]' for a team roster.\n"; 
	print "Enter 'totalSalary [Teamname]' for a team salary.\n";
	print "Enter 'EXIT' to end the program.\n\n"; 
	$input = <>;
	$count = 1; 
	$teamName = "";
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

	
	if($command eq 'EXIT' or $command eq "exit"){
		$val = 0; 
	}
	elsif ($command eq "roster"){    #Two words to every team 
		print "Team Roster for $teamName:\n\n"; 
		@myRoster = $teams{$teamName}->getRoster; 
		foreach (@myRoster){
			chomp($_); 
			print "$_ \n";
		}
	}
	elsif ($command eq "totalSalary"){
	
		print "Total salary for $teamName:\n\n"; 
		$totalSal = $teams{$teamName}->getSumOfPlayersSalary; 
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

