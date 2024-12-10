#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Compilation and basic setup
make clean && make

test_nm() {
    local file=$1
    local test_name=$2
    echo "Testing $test_name..."
    
    # Run both system nm and our nm
    nm $file > system_output.txt 2>/dev/null
    ./ft_nm $file > our_output.txt 2>/dev/null
    
    # Compare outputs
    if diff system_output.txt our_output.txt >/dev/null; then
        echo -e "${GREEN}✓ Test passed: $test_name${NC}"
        return 0
    else
        echo -e "${RED}✗ Test failed: $test_name${NC}"
        echo "Differences found:"
        diff system_output.txt our_output.txt
        return 1
    }
}

# Create test directory
mkdir -p test_files

# Compile test files
gcc -o test_files/basic_test -c test_files/basic_test.c
gcc -o test_files/basic_test_32 -m32 -c test_files/basic_test.c 2>/dev/null

# Test cases
echo "Starting NM tests..."

# Basic tests
test_nm "test_files/basic_test" "Basic 64-bit object file"
test_nm "test_files/basic_test_32" "Basic 32-bit object file"
test_nm "ft_nm" "Self test"
test_nm "/bin/ls" "System binary - ls"
test_nm "/usr/bin/python3" "System binary - python3"

# Error cases
echo "Testing error cases..."
./ft_nm nonexistent_file 2>error_output.txt
if grep -q "No such file" error_output.txt; then
    echo -e "${GREEN}✓ Error case passed: Nonexistent file${NC}"
else
    echo -e "${RED}✗ Error case failed: Nonexistent file${NC}"
fi

# Create corrupted file for testing
dd if=/dev/urandom of=test_files/corrupted bs=1024 count=1 2>/dev/null
test_nm "test_files/corrupted" "Corrupted file"

# Cleanup
rm -f system_output.txt our_output.txt error_output.txt
rm -rf test_files

echo "All tests completed."
