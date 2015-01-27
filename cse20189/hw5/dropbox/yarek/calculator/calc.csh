#!/bin/csh

#
## You really did not expect to find a working calc.csh here did you?
#

echo "Input file: $1"

foreach line ("`cat $1`")
	set line = ( $line )
	set arg1 = $line[1]
	set arg2 = $line[2]
	set arg3 = $line[3]
	echo "ARGS: $arg1 $arg2 $arg3"
end
