#!/usr/bin/perl
#John F. Lake, Jr. 
#HW 9
my $file = $ARGV[0];
my %portCounts = (); 


#Put the values in the hash
foreach (`cat $file`){
	$_ =~ /DPT=(\d+)/;
	$portCounts{ $1 } = $portCounts{$1} + 1; 
}

#Sort them and print to the screen
foreach (sort {$a <=> $b } keys %portCounts){
	print"Connection attempts on port $_ : $portCounts{$_} \n";

}


