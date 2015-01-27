//This file will take user input and produce a sound file 'music.wav' 
//John F. Lake, Jr. 
//Lab 8

#include "wavfile.h"
#include <stdio.h> 
#include <math.h> 

void get_info(char c, double * frequency, double * freqMult, double*noteLength, int*stillGoing, int *validEntry);
void enter_data(FILE * f, short waveform[], int validEntry, int NUM_SAMPLES, int samples_per_sec, double frequency, double freqMult, double volume);


int main(void){

	FILE *f = wavfile_open("music.wav"); 	//Create file to write the sound data
	double frequency; 			//Declare variable that is later used to hold the specified frequency
	int volume = 32000; 			//Specify the volume
	double noteLength = 0.5; 		//Start out with an initial note length of half a second (quarter note) 
	double freqMult = 1; 			//Used in determining octave 
	int stillGoing = 1;			//Used in the loop to determine whether to continue or not



	while(stillGoing){
		int validEntry = 1;        //If the user enters an invalid entry, this will be changed accordingly.

		
		const int NUM_SAMPLES = WAVFILE_SAMPLES_PER_SECOND*noteLength;  	//Number of samples per note for the given notelength 
		short waveform[NUM_SAMPLES];                           			//Declare an array variable for the waveform data
		
		
		char c; 
		printf("Enter input.  End input with the letter 'X'.   "); 	  //Get input from user
		scanf(" %c",&c); 
		if(c=='X'){
			wavfile_close(f); 
			return; 		
		}
		get_info(c,&frequency,&freqMult,&noteLength,&stillGoing,&validEntry); //Interpret the input (varies the frequency, octave, etc.) 
		enter_data(f,waveform,validEntry,NUM_SAMPLES,WAVFILE_SAMPLES_PER_SECOND,frequency,freqMult,volume); //Enter the data 
		
	}
	wavfile_close(f); 
}


//Used to interpret the user's input and change the values accordingly: 
void get_info(char c, double * frequency, double * freqMult, double*noteLength, int*stillGoing, int *validEntry){
	switch(c){
				case 'a': *frequency = 415.3; break;   //A-flat
				case 'A': *frequency = 440.0; break;   //A
				case 'b': *frequency = 466.16; break;  //B-flat
				case 'B': *frequency = 493.88; break;  //B
				case 'C': *frequency = 523.25; break;  //C
				case 'd': *frequency = 554.37; break;  //D-flat
				case 'D': *frequency = 587.33; break;  //D
				case 'e': *frequency = 622.25; break;  //E-flat
				case 'E': *frequency = 659.26; break;  //E
				case 'F': *frequency = 698.46; break;  //F
				case 'g': *frequency = 739.99; break;  //G-flat
				case 'G': *frequency = 783.99; break;  //G
				case '.': *frequency = 0; break; //Silence 
				case '+': *freqMult*=2; break; //Go up an octave.
				case '-': *freqMult/=2; break;  //Go down an octave.
				case '1': *noteLength = 2;  break;  //Make a whole note. 
				case '2': *noteLength = 1; break; //Make a half note. 
				case '4': *noteLength = 0.5; break; //Make a quarter note.
				case '8': *noteLength = 0.25; break; //Make a quarter note. 
				case '6': *noteLength = 0.125; break; //Make a sixteenth note. 
				case 'X': *stillGoing = 0; break; //End file
				default: 
					printf("Invalid entry, try again.\n"); 
					*validEntry = 0; 
		}
}
//Enter the data into the waveform array: 
void enter_data(FILE * f, short waveform[], int validEntry, int NUM_SAMPLES, int samples_per_sec, double frequency, double freqMult, double volume){


	if(validEntry){  //If they enter a value that is expected: 
			int i; 
			int offset = NUM_SAMPLES/6; 
			
			//Loop through the number of samples and alter the values in the waveform (data) array: 
			for(i=offset;i<NUM_SAMPLES-offset;i++){
				double t = (double) i/samples_per_sec; 

				//Altering the waveform to make it sound more like a video game: 
				waveform[i] = volume/2*sin(frequency*freqMult*t*2*M_PI*3)+volume/2*sin(frequency*freqMult*t*2*M_PI*2)+ volume/2*sin(frequency*freqMult*t*2*M_PI); 
			}

			wavfile_write(f,waveform,NUM_SAMPLES); 
		
		}
}



