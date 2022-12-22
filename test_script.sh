#!/bin/bash

VM_PATH="./"

INTRA_VM_PATH="./resources/"

COR_FILES_PATH="./resources/cor_files/working/"
COR_FILES=(`ls ${COR_FILES_PATH}*`)
TOTAL_COR_FILES=$(ls $COR_FILES_PATH | wc -l)

random_loop_champion() {
	max_loop=$1
	total_champions=$2
	echo "Testing $total_champions champion(s)"
	while [ $max_loop -gt 0 ]
	do
		intra=$3
		our=$4
		files="Champ files:"
		counter=0
		while [ $counter -lt $total_champions ]
		do
			random=$(($RANDOM%TOTAL_COR_FILES))
			intra+=" ${COR_FILES[$random]}"
			our+=" ${COR_FILES[$random]}"
			files+=" $(basename ${COR_FILES[$random]})"
			((counter++))
		done
		$intra > intra_vm_output
		$our > vm_ouput
		diff=$(diff intra_vm_output vm_ouput)
		if [ -z "$diff" ]
		then
			echo "OK - $files"
		else
			echo "KO - $files"
			echo $diff
		fi
		((max_loop--))
	done
	echo -e "\n"
}

compare_if_place_correctly() {
	random=$(($RANDOM%TOTAL_COR_FILES))
	filename="$(basename ${COR_FILES[$random]}) "
	files="Testing files: "
	intra_vm="${INTRA_VM_PATH}corewar -d 1"
	vm=""${VM_PATH}corewar""
	random_loop_champion 10 1 "${intra_vm}" "${vm}"
	random_loop_champion 10 2 "${intra_vm}" "${vm}"
	random_loop_champion 10 3 "${intra_vm}" "${vm}"
	random_loop_champion 10 4 "${intra_vm}" "${vm}"
}


compare_if_place_correctly
