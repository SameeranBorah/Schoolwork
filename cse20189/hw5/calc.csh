#!/bin/csh
#John F. Lake, Jr. 
#Performs the calculations stored in calc_input


#Cycle through every line and perform the calculation: 

@ line_number = 0 


foreach line("`cat /afs/nd.edu/coursesp.14/cse/cse20189.01/files/hw5/calc_input`")
	 @ line_number++
	#if the third input has not been set (only 1 number) or there are more than 2 numbers:
	if (`echo "$line" | wc -w` != 3) then
		echo "Error: Line: $line_number : invalid input on this line."
	else
		set argv = ( $line ) #used so that $3 returns the third item on each line.  
		switch("$3")
			case "+":	
				@ sum = $1 + $2
				echo "The sum of $1 and $2 is $sum."
				breaksw
			case "-":
				@ diff = $1 - $2
				echo "The difference between $1 and $2 is $diff."
				breaksw             
			case "x":
                                set var = `expr $1 \* $2`
                                echo "The product of $1 and $2 is $var."
                                breaksw
			case "X":
				set var = `expr $1 \* $2`
				echo "The product of $1 and $2 is $var."
				breaksw                    
			case "/":
				if($2 == 0)then
					echo "Error: Line: $line_number : division by zero."
				else 
					@ quotient = $1 / $2
					echo "The quotient of $1 and $2 is $quotient."
				endif
				breaksw
			case "%":	
				@ mod = $1 % $2
				echo "$1 modulo $2 is $mod."
				breaksw
			default: 
				echo "Error: Line: $line_number : invalid operator."   #If none of the above cases are met, it's an invalid operator.  
		endsw
	endif
end








