#!/bin/bash

# Compile first
echo "Compiling..."
make
if [ $? -ne 0 ]; then
    echo "Compilation Failed!"
    exit 1
fi

echo "Compilation Success! Running Tests..."
echo "------------------------------------------------"

# List of all test IDs found in your YAML file
tests=(
"01a" "01b" "01c" "01d"
"02a" "02b" "02c" "02d"
"03a" "03b" "03c" "03d"
"04a" "04b" "04c" "04d"
"05a" "05b" "05c" "05d"
"06a" "06b" "06c" "06d"
"07a" "07b" "07c" "07d"
"08a" "08b"
"09a" "09b"
"10a" "10b"
"11a"
"12a"
)

pass_count=0
fail_count=0

for t in "${tests[@]}"; do
    input_file="testcases/${t}-input.txt"
    output_file="testcases/${t}-output.txt"

    # Run the test
    # We use ./lab7 < input | diff output -
    ./lab7 < "$input_file" | diff -w "$output_file" - > /dev/null

    # Check exit code of diff (0 = match, 1 = difference)
    if [ $? -eq 0 ]; then
        echo "Test $t: PASSED"
        ((pass_count++))
    else
        echo "Test $t: FAILED"
        ((fail_count++))
        # Optional: Uncomment the line below to see the error immediately
        # ./lab7 < "$input_file" | diff -w "$output_file" - 
    fi
done

echo "------------------------------------------------"
echo "Summary: $pass_count Passed, $fail_count Failed"
if [ $fail_count -eq 0 ]; then
    echo "ALL TESTS PASSED! CONGRATULATIONS!"
else
    echo "Some tests failed. Check the output above."
fi
