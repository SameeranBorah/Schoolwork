#!/bin/sh
BASE="/afs/nd.edu/coursefa.14/cse/cse30264.01/files/program1/"
STR="Testing program with a command line string instead of a file"
PBASE="/afs/nd.edu/coursefa.14/cse/cse30264.01/"
DASH="===================================================================="

cd /afs/nd.edu/coursefa.14/cse/cse30264.01/dropbox

echo "What is your afsid? "
read i

   echo "Testing $i"
   if [ -d $PBASE/dropbox/$i/prog1 ] ; then
      cd $PBASE/dropbox/$i/prog1
      if [ ! -d my_grade ] ; then
	mkdir my_grade
	touch my_grade/prog1_output
      else
	echo ""
        echo "removing directory my_grade in 5 seconds.  CONTROL-C to exit"
	sleep 5
	rm -rf my_grade
	mkdir my_grade
        if [ -e my_grade/prog1_output ] ; then
	  rm prog1_output
        fi
	touch my_grade/prog1_output
      fi

      if [ -e udpclient.c ] ; then
         cp udpclient.c my_grade/
         cc -o my_grade/udpclient udpclient.c >>my_grade/prog1_output 2>&1
      elif [ -e udpclient.cpp ] ; then
         cp udpclient.cpp my_grade/
         g++ -o my_grade/udpclient udpclient.cpp >>my_grade/prog1_output 2>&1
      else
         echo "NO UDPCLIENT.C OR UDPCLIENT.CPP FILE FOR $i" >>my_grade/prog1_output
	 exit 0
      fi

      cd my_grade
      for server in woodstock.cselab.nd.edu whiz.cse.nd.edu
      do
         for FILE in File1.txt File2.txt File3.txt File1.txt
         do
           echo $DASH >>prog1_output
           echo "Running $i Program 1 Server $server File $FILE" 
           echo "Running $i Program 1 Server $server File $FILE" >>prog1_output 
           ./udpclient $server 9950 $BASE/$FILE >>prog1_output 2>&1
         done
      done
      echo $DASH >>prog1_output
      echo "Running $i Program 1 Server $server STRING"
      echo "Running $i Program 1 Server $server STRING" >>prog1_output
      ./udpclient $server 9950 "$STR" >>prog1_output 2>&1
      echo $DASH >>prog1_output
   
      echo "Done Testing $i program 1" >>prog1_output
      echo "Done Testing $i program 1" 
      echo "Check file mygrade/prog1_output for more information"
      cd /afs/nd.edu/coursefa.14/cse/cse30264.01/dropbox
   else
      echo "NO PROG1 DIRECTORY FOR $i"
   fi
