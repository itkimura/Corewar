ac=$#
if [ $ac == 0 ]
then
	echo "Please give me champion name"
else
	for arg in "$@"; do
		if [ "$arg" = "make" ]
		then
			make
		elif [ "$arg" = "makere" ]
		then
			make re
		else
			./resources/asm $arg
			str+=`echo $arg | sed 's/.s$/.cor /'`
		fi
	done
	echo "echo $str"
	./corewar $str
	# ./corewar -dump 31 $str > our
	# ./resources/corewar -d 31 $str > intra
	# diff our intra
fi
