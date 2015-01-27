#!/bin/bash
#John F. Lake, Jr. 
#Shell game
clear					#Clears the screen. 
while [ "1" -eq "1" ] 			#Run continuously  
do
	number=$RANDOM
	let "number %= 7"
	let "number += 1"
	#number is the cup the ball is under

	#Give the user a prompt:
	echo "There are 7 cups.  A ball is under ONE of the cups."
	echo "Which ball is the cup under?"
	read guess

							
	if [ "$guess" -gt "7" ]; then		#if the guess is more than the number of cups, tell the user. 
		echo "There are only 7 cups.  Try again."
	elif [ "$guess" -lt "1" ]; then		#likewise for guesses that are less than 1. 
		echo "You cannot have a guess less than 1."
	else  #Valid entry
		if [ "$guess" -eq "$number" ]; then		#If the guess is equal to $number, they won the game.
			echo "YOU GOT IT RIGHT!"
			exit
		else 
			echo "Incorrect.  The ball was under cup $number"	#If they aren't equal, display the cup the ball is under. 
			echo "Do you want to try again?"			#Ask the user if they want to play again. 
			read again					
			case "$again" in 
				[Yy]es) 
					clear;;
				[Nn]o) 
					echo "Fair enough.  Thanks for playing!"
					exit;;	
				    *)					#If invalid input is entered, simply restart the game.  
					clear
					echo "Invalid input.  Game restarting...";;
			esac				
		fi 
	fi
done


