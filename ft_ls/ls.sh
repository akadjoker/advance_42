#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

# Counter for tests
TOTAL=0
PASSED=0

# Function to compare ft_ls with system ls
compare_ls() {
    local opts=$1
    local dir=$2
    local test_name=$3
    
    TOTAL=$((TOTAL + 1))
    
    # Run both commands and store outputs
    # Using LC_ALL=C as specified in the subject
    your_ls_output=$(LC_ALL=C ./ft_ls $opts $dir 2>&1)
    system_ls_output=$(LC_ALL=C ls $opts $dir 2>&1)
    
    if [ "$your_ls_output" = "$system_ls_output" ]; then
        echo -e "${GREEN}✓ Test $TOTAL Passed:${NC} $test_name"
        PASSED=$((PASSED + 1))
    else
        echo -e "${RED}✗ Test $TOTAL Failed:${NC} $test_name"
        echo "Expected:"
        echo "$system_ls_output"
        echo "Got:"
        echo "$your_ls_output"
        echo "Difference:"
        diff <(echo "$system_ls_output") <(echo "$your_ls_output")
    fi
}

# Create test environment
setup_test_env() {
    rm -rf test_dir
    mkdir -p test_dir
    cd test_dir
    
    # Regular files with different timestamps
    echo "content1" > file1
    sleep 1
    echo "content2" > file2
    
    # Hidden files
    touch .hidden_file
    
    # Directories
    mkdir dir1
    mkdir dir1/subdir
    touch dir1/subdir/file3
    
    # Symbolic link
    ln -s file1 symlink1
    
    # Different permissions
    chmod 644 file1
    chmod 755 dir1
    
    cd ..
}

# Main test function
run_mandatory_tests() {
    echo "Testing mandatory features..."
    
    # Basic functionality
    compare_ls "" "test_dir" "Basic ls"
    compare_ls "-l" "test_dir" "Long format (-l)"
    compare_ls "-a" "test_dir" "Hidden files (-a)"
    compare_ls "-r" "test_dir" "Reverse order (-r)"
    compare_ls "-t" "test_dir" "Time sorting (-t)"
    compare_ls "-R" "test_dir" "Recursive (-R)"
    
    
    # Error cases
    compare_ls "" "nonexistent" "Nonexistent directory"
    compare_ls "-l" "test_dir/file1 test_dir/file2" "Multiple files"
    
    # Results
    echo "----------------------------------------"
    echo "Test Results: $PASSED/$TOTAL passed"
    if [ $PASSED -eq $TOTAL ]; then
        echo -e "${GREEN}All mandatory tests passed!${NC}"
    else
        echo -e "${RED}Some tests failed.${NC}"
    fi
}

# Run tests
echo "Setting up test environment..."
setup_test_env

echo "Running tests..."
run_mandatory_tests

echo "Cleaning up..."
rm -rf test_dir
