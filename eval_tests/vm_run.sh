ac=$#
GREEN='\033[0;32m'
RESET='\033[0m'
if [ $ac == 0 ]
then
	echo "Please give me champion name"
else
	for arg in "$@"; do
		if [ "$arg" = "make" ]
		then
			echo -e "${GREEN}Run make${RESET}"
			make
		elif [ "$arg" = "makere" ]
		then
			echo -e "${GREEN}Run makere${RESET}"
			make re
		else
		if [[ $arg == *".s"* ]]
			then
				echo -e "${GREEN}Run assembler for test.s${RESET}"
				./resources/asm $arg
			fi
			str+=`echo " $arg" | sed 's/.s$/.cor/'`
		fi
	done
	echo -e "${GREEN}Run ./corewar$str${RESET}"
	./corewar$str
	#our=`./corewar -dump 31 $str`
	#intra=`./resources/corewar -d 31 $str`
	#diff our intra
fi
