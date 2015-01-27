package Team; 
use Player; 

sub new {
	my $class = shift; 
	my $self = {}; 
	bless($self, $class);
	
	$self->{
		_players => (),
		_name => shift,
	}; 
	 
	return $self;
} 

sub addPlayer{
	my $self = shift; 
	my $a = shift; 
	push @{$self->{'_players'}}, $a; 
	
}

sub getSumOfPlayersSalary{
	my $self = shift; 
	my $sum = 0; 
	foreach (@{$self->{'_players'}}){
		$sum += $_->getSalary; 
	}
	return $sum;
}

sub getRoster {
	my $self = shift; 
	my @roster = ();
	foreach (@{$self->{'_players'}}){
		$teamMember =  $_->getFullName . ": " .$_->getPosition;
		push (@roster,$teamMember);  
	}
	return @roster;
}
sub getTeamName{
	my $self = shift; 
	my $name = $self{'_name'}; 
	return $name; 
}
1;
