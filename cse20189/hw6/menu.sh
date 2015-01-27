#!/bin/bash
#John F. Lake, Jr. 
#Presents the user with 8 menu options, and takes the user's input. 

trap bashtrap SIGINT


bashtrap(){
	echo "Can't exit."
}

present_menu(){
	echo "Menu item:	Item number:	Command to Execute:"
	echo "disk_free		1	  df -k \"filespec\""
	echo "disk_usage		2	  du -s -k \"filespec\""
	echo "list_files		3	  ls -F"
	echo "process_status		4	  top"
	echo "examine_volume		5	  vos examine user.afsid"
	echo "shell			6	  /bin/bash"
	echo "date			7	  date + \"%a %b %Y %r\""
	echo "exit			8	  exit"
}
clear
while [ "1" -eq "1" ]
do
	present_menu 
	read r
	clear
	case "$r" in 
		1)
			echo "Give a filespec:"
			read file
			df -k "$file"
			sleep 2;
			clear;;
		2)
		        echo "Give a filespec:"
                        read file
                        df -k "$file"
			sleep 2;
			clear;;
		3)
			ls -F
			sleep 2;
			clear;;
		4)
			top
			sleep 2; 
			clear;;
		5)
			echo "Enter your afsid."
			read ID
			/usr/sbin/vos examine -id user.$ID;;
		6)
			/bin/bash
			sleep 2;
			clear;;
		7)	
			date +"%a %b %Y %r"
			sleep 2; 
			clear;;
		8)
			exit;;
						
	esac
done
