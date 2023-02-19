valid_dir="/vm_champs/champs"
error_dir="/error_files/"
output_dir= /Users/clem/Desktop/Hive/Corewawa 

while getopts "ve" opt; do
  case ${opt} in
    v )
	  valid_dir="vm_champs/champs"
      echo "Outputting results from the \"$valid_dir\" directory"
      ;;
    e )
      error_dir="error_files/"
      echo "Outputting results from the \"$error_dir\" directory"
      ;;
    \? )
      echo "Invalid option: -$OPTARG" 1>&2
      exit 1
      ;;
  esac
done

if [ "$output_dir" ]; then
  out_file="valid_result.txt"
else
  out_file="error_result.txt"
fi

# Check if the output file already exists and delete it if it does
if [ -e "$out_file" ]; then
  rm "$out_file"
fi

# Loop over all .s files in the specified directory
if [ "$output_dir" ]; then
  dir="$valid_dir"
else
  dir="$error_dir"
fi

cd "$dir"
for file in *.s; do
  if [ -f "$file" ]; then
    echo "Processing file: $file"
    # Run the file with the first executable and write the output to the output file
    echo "Output from ./asm for \"$file\":" >> "$out_file"
    ./asm "$file" >> "$out_file" 2>&1
    echo "" >> "$output_dir$out_file"
    # Run the file with the second executable and write the output to the output file
    echo "Output from ./vm_champs/asm for \"$file\":" >> "$out_file"
    ./vm_champs/asm "$file" >> "$out_file" 2>&1
    echo "" >> "$out_file"
  fi
done

	echo "All test done! Find the result in \"$out_file\""
