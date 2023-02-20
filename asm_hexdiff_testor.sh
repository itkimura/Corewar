#!/bin/bash

DIFF_FILE="asm_diff.txt"

# Remove diff file if it already exists
if [ -f "$DIFF_FILE" ]; then
    rm "$DIFF_FILE"
fi
#
# Run hexdump on all files in og_valid_asm and our_valid_asm directories
echo "Running hexdump on og_valid_asm and our_valid_asm files"
no_diff=1
for file in og_valid_asm/* our_valid_asm/*; do
	echo "Processing file: $file"
		og_hexdump=$(hexdump -vC "og_valid_asm/$(basename "$file")")
        our_hexdump=$(hexdump -vC "our_valid_asm/$(basename "$file")")

    # Compare hexdumps and print differences if any
    if [ "$og_hexdump" != "$our_hexdump" ]; then
        echo -e "\033[0;31mDifferences found for file: $file\033[0m" >> asm_diff.txt
        diff -u <(echo "$og_hexdump") <(echo "$our_hexdump") >> asm_diff.txt
        no_diff=0
    else
        echo -e "\033[0;32mNo differences found for file: $file\033[0m" >> asm_diff.txt
    fi
done

if [ $no_diff -eq 1 ]; then
    echo -e "\033[0;32mNo differences found between the hexdumps\033[0m" >> asm_diff.txt 
else
    echo -e "\033[0;31mDifferences found between the hexdumps\033[0m" >> asm_diff.txt 
fi
echo "Tests completed. Differences between OG ASM and OUR ASM can be found in $DIFF_FILE."
