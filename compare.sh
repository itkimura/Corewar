#!/bin/bash

#
# File path configuration (Please change if you want!)
#
VM_PATH="./"
INTRA_VM_PATH="./resources/"
COR_FILES_PATH="./resources/cor_files/working/"
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
# Print help message
#
if [ $ac -eq 0 -o "$1" = "--help" ]; then
	echo -e "Description:\n"
	echo -e "  The scrip tests your corwar  with random player and compare with the corwar from Resources\n"
	echo -e "Basic usage:\n"
	echo -e "  ${BOLD}bash compare.sh N option:[the number of random players]${NC}\n"
	echo -e "The following option is available:\n"
	echo -e "  ${BOLD}bash compare.sh${NC}\t\tprint this help message"
	echo -e "  ${BOLD}bash compare.sh --help${NC}\tprint this help message"
	echo -e "  ${BOLD}bash compare.sh N${NC}\t\ttest corewar with ${BOLD}1${NC} player and compare with corwar from Resources every ${BOLD}N${NC} cycles"
	echo -e "  ${BOLD}bash compare.sh N N2${NC}\t\ttest corewar with ${BOLD}N2${NC} players and compare with corwar from Resources every ${BOLD}N${NC} cycles\n\n"
	exit
fi

#
# Set up N numbers
#
cycle=$1
playernb="1"
if [ $ac -gt 1 ];then
	playernb=$2
fi

#
# loop cycles
#
loop_tests() {
	while [ $playernb -gt 0 ]
	do
		random=$(($RANDOM%TOTAL_COR_FILES))
		champions+=" ${COR_FILES[$random]}"
		((playernb--))
	done
	loop=$cycle
	
	echo "Files: $champions"
	while [ $loop -lt 1000 ]
	do
		./corewar -dump $loop $champions > test1
		./resources/corewar -d $loop $champions > test2
		#echo "Run $our"
		#echo "Run $intra"
		diff=`diff test1 test2`
		#echo "diff = $diff"
		if [ "$diff" == "" ]
		then
			echo -e -n "${GREEN}.${NC}"
		else
			echo -e -n "${RED}.${NC}"
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
				break ;
			fi
		fi
		((loop+=$cycle))
	done
	rm -f test1 test2
	echo ""
}

loop_tests
