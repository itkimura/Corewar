#!/bin/bash

#
# File path configuration (Please change if you want!)
#
VM_PATH="./corewar"
INTRA_VM_PATH="./eval_tests/resources/corewar"
COR_FILES_PATH="./eval_tests/cor_files/working/"
COR_ERROR_FILES_PATH="./eval_tests/cor_files/error/"
COR_FILES=(`ls ${COR_FILES_PATH}*`)
TOTAL_COR_FILES=$(ls $COR_FILES_PATH | wc -l)

#
# Color scheme
#
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
BOLD='\033[0;1m'
NC='\033[0m'
ac=$#


#
# error files
#
echo -e "${BOLD}Test error files${NC}"
COR_ERROR_FILES=`ls $COR_ERROR_FILES_PATH`
for FILE in $COR_ERROR_FILES;
do
	echo -e "[$YELLOW$FILE$NC]"
	leaks -q --atExit -- $VM_PATH --lld-size-2 $COR_ERROR_FILES_PATH$FILE > output
	echo -e -n "LEAKS:\t"
	res=`cat output | tail -n 2 | awk '{print $3}'`
	if [ "$res" == "0" ]
		then
			echo -e "${GREEN}OK${NC} "
		else
			echo -e "${RED}KO${NC} "
	fi
	echo -n -e "YOUR:\t"
	cat output | head -n 1
	echo -n -e "TEST:\t"
	$INTRA_VM_PATH $COR_ERROR_FILES_PATH$FILE
done

#
# Test operation (-v 4 compare)
#
echo -e "\n${BOLD}Test -v flags${NC}"
COR_FILES=`ls $COR_FILES_PATH`
NBS=`echo -e "1\n2\n4\n8\n16"`
for FILE in $COR_FILES;
do
	FILE_NAME=`basename $FILE`
	if [ "$FILE_NAME" != "Car.cor" ] && [ "$FILE_NAME" != "bee_gees.cor" ];
	then
		echo -e "[$YELLOW$FILE$NC]"
		for NB in $NBS
		do
			echo -n "$NB:"
			leaks -q --atExit -- $VM_PATH --lld-size-2 $COR_FILES_PATH$FILE -v $NB > output
			leaks=`cat output | tail -n 2 | awk '{print $3}'`
			line=`cat output | wc -l`
			cat output | head -n $((line - 4)) > our
			$INTRA_VM_PATH $COR_FILES_PATH$FILE -v $NB > intra
			diff=`diff our intra`
			if [ "$diff" == "" ] && [ "$leaks" == "0" ]
			then
				echo -e -n "${GREEN}OK${NC} "
			elif [ "$leaks" != "0" ];
			then
				echo -e -n "${RED}LEAKS${NC} "
			else
				echo -e -n "${RED}KO${NC} "
				echo "Do you want to print diff? [y/n]"
				read -r b
				if [ "$b" == "y" ]
				then
					echo -e "${RED}ERROR:${NC} ./corewar -d $loop $champions"
					echo "diff = $diff"
				fi
				echo "Do you want to quit? [y/n]"
				read -r b
				if [ "$b" == "y" ]
				then
					exit
				fi
			fi
		done
		echo ""
	fi
done
rm -f our
rm -f output
rm -f intra

