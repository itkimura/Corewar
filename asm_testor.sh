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
    exit 0
fi

# Create directories for output files
if [ "$TEST_TYPE" == "valid" ]; then
	mkdir -p our_valid_asm
	mkdir -p og_valid_asm 
elif [ "$TEST_TYPE" == "error" ]; then
	mkdir -p our_error_asm
	mkdir -p og_error_asm
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
	echo "Testing with asm and example_asm with valid"
	for file in resources/s_files/*; do
		echo "***OUR ASM***\n" >> valid_asm_test.txt
		./asm "$file" > "$(dirname "$0")/our_valid_asm/$(basename "${file%.*}").cor"
    	./asm $file >> valid_asm_test.txt
		echo "***OG ASM***\n" >> valid_asm_test.txt
		./resources/example_asm "$file" > "$(dirname "$0")/og_valid_asm/$(basename "${file%.*}").cor"
    	./resources/example_asm $file >> valid_asm_test.txt
	done
	echo "Tests completed. Results can be found in valid_asm_test.txt"

# Run asm and example_asm on all files in asm_error_files directory with -error option
elif [ "$TEST_TYPE" == "error" ]; then
 	echo "Testing with asm and example_asm error"
	for file in eval_tests/asm_error_files/*; do
		echo "***OUR ASM***\n" >> error_asm_test.txt   
		./asm "$file" > "$(dirname "$0")/our_error_asm/$(basename "${file%.*}").cor"
    	./asm $file >> error_asm_test.txt
		echo "***OG ASM***\n" >> error_asm_test.txt   
		./resources/example_asm "$file" > "$(dirname "$0")/og_error_asm/$(basename "${file%.*}").cor"
    	./resources/example_asm $file >> error_asm_test.txt
	done
	echo "Tests completed. Results can be found in error_asm_test.txt"
fi
