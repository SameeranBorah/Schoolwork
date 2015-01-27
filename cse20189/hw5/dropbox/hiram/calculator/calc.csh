#!/bin/csh
set BASE="/afs/nd.edu/coursesp.14/cse/cse20189.01/files/hw5"
#
## You really did not expect to find a working calc.csh here did you?
#

# This one simulates prompting for a filename 
# # (someone did not read instructions)
# BUT it will not hang and wait for a filename...it will just error out.

echo "Please provide an input file name: "

set filename = "$BASE/input.txt"
foreach line ("`cat $filename`")
	echo "Input Line: $line"
end
