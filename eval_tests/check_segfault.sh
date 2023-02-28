#!/bin/bash

#
# File path configuration (Please change if you want!)
#
# ASM_PATH="./"
ASM_PATH="./resources/" #example_asm
S_FILES_PATH="./eval_tests/asm_error_files/"
# S_FILES_PATH="./eval_tests/s_files/"

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
echo -e "" >> leaks.txt
S_FILES=`ls $S_FILES_PATH`
for FILE in $S_FILES;
do
	echo -e "for file: $S_FILES_PATH$FILE$NC" >> leaks.txt
	./asm $S_FILES_PATH$FILE -x >> leaks.txt
	echo -e "---------------\n" >> leaks.txt
done