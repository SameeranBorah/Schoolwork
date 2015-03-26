#John F. Lake, Jr.
#CSE30151 Project 2
#This program will take in a text file that describes a DPDA. 
import sys
import re



#This will get all 6 Parts of the DPDA:
def getDPDA(filename):
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
			if len(alpha) == 1 and alpha[0] == "":
				return -1
		
			print "Alphabet: " + str(alpha)
			n['alphabet'] = alpha
		elif(line[0] == 'Z'):
			#Get the stack alphabet. 
			salpha = []
			salpha = re.split(',|\n', line[2:-1])
			if len(salpha) == 1 and salpha[0] == "":
				return -1
			print "Stack alphabet: " + str(salpha)
			n['salphabet'] = salpha

		elif(line[0] == 'Q'):
			#Get the states:
			states = []
			states = re.split(',|\n', line[2:-1])
			if len(states) == 1 and states[0] == "":
				return -1
			print "States: " + str(states)

			n['states'] = states


		elif(line[0] == 'T'):
			#Increase the number of transitions by one:
			numTransitions+=1
	
			#Place the transition function inside a list
			# t[0] is the starting point
			# t[1] is the input
			# t[2] is the expected item @ top of stack
			# t[3] is the next state
			# t[4] is the item pushed onto stack
			t = []
			t = re.split(',|\n', line[2:-1])
			if len(t) == 1 and t[0] == "":
				return -1
			elif t[0] not in n['states'] or t[3] not in n['states']:
				return -1	
			elif t[1] not in n['alphabet'] and t[1] != 'e':
				return -1
			elif t[2] not in n['salphabet'] and t[2] != 'e':
				return -1
			elif t[4] not in n['salphabet'] and t[4] != 'e':
				return -1
			print "Transition: " + str(t)

			trans[numTransitions] = t

		
		elif(line[0] == 'S'):
			#Obtain the starting state:
			s = []
			s = re.split(',|\n', line[2:-1])
			if len(s) == 1 and s[0] == "":
				return -1

			print "Starting state: " + str(s)
			n['start'] = s


		elif(line[0] == 'F'):
			#Obtain the end states:
			f = []
			f = re.split(',|\n', line[2:-1])
			if len(f) == 1 and f[0] == "":
				return -1
			print "Accepting states: " + str(f)

			n['acceptStates'] = f
		else:
			return -1
	fd.close()
	n['transitions'] = trans
	return n


def processInput(dpda):
	print "This will process the input for the given DPDA"

 	numInputTapes = int(raw_input(""))

	#Get each input tape and delimit it. 
	for i in range(numInputTapes):

		#Get the input: 
		it = raw_input("")
		inputTape = re.split(',',it)
		stack = []

		#Used to make sure the input is valid: 
		validInput=1;

		#Set the css to whatever the start state is: 
		cs = dpda['start'][0]



		if len(inputTape) == 1 and inputTape[0] == "":
			acc = 0;
			if cs in dpda['acceptStates']:
					acc=1;
			if acc == 1:
				print "ACCEPT!\n"
			else:
				print "REJECT!\n"
			continue
				
		for key in dpda['transitions']:
			trans = dpda['transitions'][key]

			#The transition is applicable to the state we are in: 
			if trans[0] == cs:
				if trans[1] == 'e' and trans[2] == 'e':
					stack.reverse()
					print cs+"; "+trans[1]+"; "+trans[2]+"; "+trans[3]+"; "+",".join(stack)+trans[4]
					stack.reverse()
					cs = trans[3]
					if trans[4] is not 'e':
						stack.append(trans[4])
			

		for input in inputTape:
			if input in dpda['alphabet']:
				for key in dpda['transitions']:

					trans = dpda['transitions'][key]

					#The transition is applicable to the state we are in: 
					if trans[0] == cs:

						#Automatic transition (always check first.)
						if trans[1] == 'e' and trans[2] == 'e':
							cs = trans[3]
							if trans[4] is not 'e':
								stack.append(trans[4])
								stack.reverse()
								print cs+"; "+trans[1]+"; "+trans[2]+"; "+trans[3]+"; "+",".join(stack)
								stack.reverse()
	

						#Doesn't matter what's on the stack: 
						elif trans[2] == 'e':
							if trans[1] == input:
								cs = trans[3]
								if trans[4] is not 'e':
									stack.append(trans[4])
								stack.reverse()
								print cs+"; "+trans[1]+"; "+trans[2]+"; "+trans[3]+"; "+",".join(stack)
								stack.reverse()
								break
		
						#Doesn't matter what the input is
						elif trans[1] == 'e':
							stackTop = stack.pop()
							if trans[2] == stackTop:
								cs = trans[3]
								if trans[4] is not 'e':
									stack.append(trans[4])
								stack.reverse()
								print cs+"; "+trans[1]+"; "+trans[2]+"; "+trans[3]+"; "+",".join(stack)
								stack.reverse()
								break
							else:
								stack.append(stackTop)
						
				
						else:
							stackTop = stack.pop()
							if trans[2] == stackTop and trans[1] == input:
								cs = trans[3]
								if trans[4] is not 'e':
									stack.append(trans[4])
								stack.reverse()
								print cs+"; "+trans[1]+"; "+trans[2]+"; "+trans[3]+"; "+",".join(stack)
								stack.reverse()
							else:
								stack.append(stackTop)
			else: 
				print "REJECT: This isn't recognized by the alphabet of this DPDA!"
				



			
		#Either accept or reject the given input: 
		if(validInput == 1):
			accept = 0;	
			if(cs in dpda['acceptStates']):
				accept = 1
			if(accept == 1):
				print "ACCEPT!\n"
			else: 
				print "REJECT!\n"
			
			
				
				
	

def main(argv):
	#DPDA is a dictionary. Set it up:
	dpda = {}
	dpda = getDPDA(argv[1])	



	if(dpda == -1):
		print "ERROR, INVALID DPDA INPUT!"
	else:
		if(dpda != 0):
			#There is a valid NFA: 
			processInput(dpda)



if __name__ == "__main__":
	main(sys.argv);

