package Player; 

sub new {
	my $class = shift; 
	my $self = {
		_teamName => shift, 
		_lastName => shift,
		_firstName => shift, 
		_salary => shift, 
		_position => shift, 
	};
	bless($self, $class); 
	
	
	return $self;
} 

sub getSalary{
	my $self = shift; 
	return $self->{_salary}; 
}

sub getFullName{
	my $self = shift; 
	my $first = $self->{_firstName}; 
	my $last = $self->{_lastName}; 
	my $fullName = "$first $last"; 
	return $fullName; 
}

sub getPosition{
	my $self = shift; 
	return $self->{_position}; 
}

sub getTeam{
	my $self = shift; 
	return $self->{_teamName}; 
}
1;
