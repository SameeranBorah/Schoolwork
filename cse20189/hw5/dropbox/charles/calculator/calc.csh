#!/bin/csh
#
## You really did not expect to find a working calc.csh here did you?
#

echo "Input file is: $1"

foreach line ("`cat $1`")
	echo "Input Line: $line"
end
