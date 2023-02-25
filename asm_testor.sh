#!/bin/bash

# Function to print usage help
function usage {
    echo "Usage: $0 [-valid | -error]"
    echo "  -valid   : Execute only the tests related to valid_asm_test.txt"
    echo "  -error   : Execute only the tests related to error_asm_test.txt"
	echo "  -clean   : Remove created directories and text files"
    exit 1
}

if [[ $# -eq 0 ]]; then
    usage
fi
# Parse command line arguments
while [[ $# -gt 0 ]]
do
    key="$1"

    case $key in
        -valid)
            TEST_TYPE="valid"
            shift
            ;;
        -error)
            TEST_TYPE="error"
            shift
            ;;
		 -clean)
            CLEANUP=true
            shift
            ;;
        *)
            usage
            shift
            ;;
    esac
done

# Remove directories if they already exist
if [ "$TEST_TYPE" == "valid" ]; then
	if [ -d "our_valid_asm" ]; then
    	rm -rf "our_asm"
	fi
	if [ -d "og_valid_asm" ]; then
    	rm -rf "og_asm"
	fi
fi
if [ "$TEST_TYPE" == "error" ]; then
	if [ -d "our_error_asm" ]; then
    	rm -rf "our_error_asm"
	fi
	if [ -d "og_error_asm" ]; then
    	rm -rf "og_error_asm"
	fi
fi

# Clean up created directories and text files
if [ "$CLEANUP" == true ]; then
    if [ -d "our_valid_asm" ]; then
        rm -rf "our_valid_asm"
    fi
    if [ -d "og_valid_asm" ]; then
        rm -rf "og_valid_asm"
    fi
    if [ -d "our_error_asm" ]; then
        rm -rf "our_error_asm"
    fi
    if [ -d "og_error_asm" ]; then
        rm -rf "og_error_asm"
    fi
    if [ -f "valid_asm_test.txt" ]; then
        rm "valid_asm_test.txt"
    fi
    if [ -f "error_asm_test.txt" ]; then
        rm "error_asm_test.txt"
    fi
    echo -e "\033[35mAll files deleted\033[0m"
    exit 0
fi

# Create directories for output files
if [ "$TEST_TYPE" == "valid" ]; then
    our_asm_dir="$(dirname "$0")/our_valid_asm"
    mkdir -p "$our_asm_dir"
    og_asm_dir="$(dirname "$0")/og_valid_asm"
    mkdir -p "$og_asm_dir"
elif [ "$TEST_TYPE" == "error" ]; then
    our_asm_dir="$(dirname "$0")/our_error_asm"
    mkdir -p "$our_asm_dir"
    og_asm_dir="$(dirname "$0")/og_error_asm"
    mkdir -p "$og_asm_dir"
fi

# Remove output files if they exist
if [ -f valid_asm_test.txt ]; then
    rm valid_asm_test.txt
fi

if [ -f error_asm_test.txt ]; then
    rm error_asm_test.txt
fi

# Run asm and example_asm on all files in s_files directory with -valid option
if [ "$TEST_TYPE" == "valid" ]; then
    echo -e "\033[35mTesting with asm and example_asm with valid\033[0m"
    for file in eval_tests/s_files/*.s; do
        echo -e "***\033[32mOUR ASM***\n"\033[0m >> valid_asm_test.txt
		./asm "$file" 2>&1 | tee -a valid_asm_test.txt > /dev/null
		echo -e "\n" >> valid_asm_test.txt
        mv "${file%.s}.cor" our_valid_asm/
        echo -e "***\033[31mOG ASM***\n"\033[0m >> valid_asm_test.txt
		./eval_tests/asm "$file" 2>&1 | tee -a valid_asm_test.txt > /dev/null
		echo -e "\n" >> valid_asm_test.txt
        mv "${file%.s}.cor" og_valid_asm/
    done
    echo -e "\033[35mTests completed. Results can be found in valid_asm_test.txt\033[0m"

# Run asm and example_asm on all files in asm_error_files directory with -error option
#
elif [ "$TEST_TYPE" == "error" ]; then
 	echo -e "\033[35mTesting with asm and example_asm error\033[0m"
    for file in eval_tests/asm_error_files/*.s; do
        echo -e "***\033[32mOUR ASM***\n\033[0m" >> error_asm_test.txt
		./asm "$file" 2>&1 | tee -a error_asm_test.txt > /dev/null
		echo -e "\n" >> error_asm_test.txt
        mv "${file%.s}.cor" our_error_asm/
        echo -e "***\033[31mOG ASM***\n\033[0m" >> error_asm_test.txt
		./eval_tests/asm "$file" 2>&1 | tee -a error_asm_test.txt > /dev/null
		echo -e "\n" >> error_asm_test.txt
        mv "${file%.s}.cor" og_error_asm/
    done
	echo -e "\033[35mTests completed. Results can be found in error_asm_test.txt\033[0m"
fi
