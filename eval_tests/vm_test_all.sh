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
	echo -n -e "YOUR:\t"
	$VM_PATH --lld-size-2 $COR_ERROR_FILES_PATH$FILE
	echo -n -e "TEST:\t"
	$INTRA_VM_PATH $COR_ERROR_FILES_PATH$FILE
done


#
# Test operation (-v 4 compare)
#
echo -e "\n${BOLD}Test operations${NC}"
CHAMPION_NB="1"
PLAY_TIME="10"
NB=$CHAMPION_NB
while [ $PLAY_TIME -gt 0 ]
do
	while [ $NB -gt 0 ]
	do
		RANDOM_FILE=$(($RANDOM%TOTAL_COR_FILES))
		CHAMPIONS+=" ${COR_FILES[$RANDOM_FILE]}"
		((NB--))
	done
	echo -n -e "[$(basename $CHAMPIONS)]\t"
	$VM_PATH --lld-size-2 $CHAMPIONS -l 4 > our
	$INTRA_VM_PATH $CHAMPIONS -v 4 > intra
	diff=`diff our intra`
	if [ "$diff" == "" ]
	then
		echo -e "${GREEN}OK${NC}"
	else
		echo -e "${RED}KO${NC}"
	fi
	NB=$CHAMPION_NB
	CHAMPIONS=""
	((PLAY_TIME--))
done
rm -f our
rm -f intra

