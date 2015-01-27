package League; 
use Player; 
use Team; 

sub new {
	my $class = shift; 
	my $self = {
		_teams => {}
	};
	bless($self, $class); 
	return $self;
} 

sub getRoster{
	my $self = shift; 
	my $teamName = shift; 
	my @roster = $self{'_teams'}{$teamName}->getRoster; 
	return @roster;
}

sub getTeamSalaryTotal{
	my $self = shift; 
	my $teamName = shift; 
	my $salary = $self{'_teams'}{$teamName}->getSumOfPlayersSalary; 
	return $salary; 
}

sub addPlayer{
	my $self = shift; 
	my $teamName = shift;  
	my $player = shift; 
	if(exists $self{'_teams'}{$teamName} ){	
		$self{'_teams'}{$teamName}->addPlayer($player); 				
	}
	else{
		my $myTeam = new Team($teamName); 
		$myTeam->addPlayer($player);
		my $r =  $myTeam->getTeamName; 
		$self{'_teams'}{$teamName} = $myTeam; 
	}	 
}


sub getTeam{
	my $self = shift; 
	my $teamName = shift; 
	return $self{'_teams'}{$teamName}; 
}
sub addTeam{
	my $self = shift; 
	my $teamName = shift; 

}



1;
