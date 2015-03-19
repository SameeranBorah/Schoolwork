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
			n['start'] = s


		elif(line[0] == 'F'):
			#Obtain the end states:
			f = []
			f = re.split(',|\n', line[2:-1])
			if len(f) == 1 and f[0] == "":
				return -1

			n['acceptStates'] = f
		else:
			return -1
	fd.close()
	n['transitions'] = trans
	return n


def processInput(dpda):
	print "This will process the input for the given DPDA"

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

