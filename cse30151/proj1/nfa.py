#John F. Lake, Jr.
#CSE30151 Project 1
#This program will take in a text file that describes an NFA. 
import sys
import re


#This gets the NFA data and returns a dictionary associated with that NFA.
# Example:
# NFA = {
# 	'alphabet' = ['0','1'],
#	'states' = ['q1','q2','q3'],
#	't' = {dictionary w/transition functions}
#	...etc.
#}
def getNFA(filename):
	numTransitions =0
	trans={}
	n = {}
	fd =  open(filename,'r') 
	for line in fd:
		#read lines one by one:	
		if(line[0] == 'A'):
			#Get the alphabet. 
			alpha = []
			alpha = re.split(',|\n', line[2:-1])
			n['alphabet'] = alpha


		elif(line[0] == 'Q'):
			#Get the states:
			states = []
			states = re.split(',|\n', line[2:-1])
			n['states'] = states


		elif(line[0] == 'T'):
			#Increase the number of transitions by one:
			numTransitions+=1

	
			#Place the transition function inside a list
			# t[0] is the starting point
			# t[1] is the input
			# t[2] is the destination point
			t = []
			t = re.split(',|\n', line[2:-1])
			trans[numTransitions] = t

		
		elif(line[0] == 'S'):
			#Obtain the starting state:
			s = re.split(',|\n', line[2:-1])
			n['start'] = ''.join(s)


		else:
			#Obtain the end states:
			f = []
			f = re.split(',|\n', line[2:-1])
			n['acceptStates'] = f

	fd.close()
	n['transitions'] = trans
	return n


def processInput(nfa):
	#for input, the first line has a number with the inputs:
 	numInputTapes = int(raw_input(""))


	#Get each input tape and delimit it. 
	for i in range(numInputTapes):

		it = raw_input("")
		inputTape = re.split(',',it)
		currentStates = []
		currentStates.append(nfa['start'])
		newStates = []
		print ";",nfa['start']
		for key,el in nfa['transitions'].iteritems():
			if(el[1] == 'e' and (el[0] in currentStates or el[0] in newStates)):
				if(el[2] not in newStates):
					newStates.append(el[2])
					if(el[0] not in newStates):
						newStates.append(el[0])
							
		if(len(newStates)>0):
			currentStates = newStates
		newStates = []
		print currentStates

	
		for input in inputTape:
			hasInput ={}
			for s in currentStates:
				hasInput[s] = 0;
				
			#Move from state to state depending on the transition rule: 
			if input in nfa['alphabet']:
				newVals=1
				#Go through the transition functions: 
				for key,el in nfa['transitions'].iteritems():
					if(el[1]==input and el[0] in currentStates):
						hasInput[el[0]] = 1	
		
					#if the transition function applies, use it on one of the current states
					if(el[0] in currentStates  and el[1] == input):

						#if the state being transferred to is NOT in the new set of states, add it: 
						if(el[2] not in newStates):
							newStates.append(el[2])



				numsToRemove = []
				for state in currentStates:
					if(hasInput[state]==0):
						numsToRemove.append(currentStates.index(state))

				for i in reversed(numsToRemove):
					del currentStates[i]

				#Same thing, just for epsilon transitions:
				while(newVals == 1):	
					newVals = 0
					for key,el in nfa['transitions'].iteritems():

						if(el[1] == 'e' and (el[0] in currentStates or el[0] in newStates)):

							if(el[2] not in newStates):

								newVals = 1
								newStates.append(el[2])

								if(el[0] not in newStates):
									newStates.append(el[0])

						
								#	print newStates
				
			else:
				print "Input not in alphabet for this NFA."
				break;
					
			print input, ";", newStates
			currentStates = newStates
			newStates = []
		
		accept = 0;	
		for cs in currentStates:
			if(cs in nfa['acceptStates']):
				accept = 1
		if(accept == 1):
			print "ACCEPT!"
		else: 
			print "REJECT!"




def main(argv):

	#Nfa is a dictionary. Set it up:
	nfa = {}
	nfa = getNFA(argv[1])	



	if(nfa == -1):
		print "ERROR, INVALID NFA INPUT!"
	else:
		if(nfa != 0):
			#There is a valid NFA: 
			processInput(nfa)



if __name__ == "__main__":
	main(sys.argv);

