#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

# Test counters
TOTAL=0
PASSED=0

# Benchmark results
declare -A TIMING_RESULTS

# Function to compare outputs
compare_ls() {
    local opts=$1
    local dir=$2
    local test_name=$3
    
    TOTAL=$((TOTAL + 1))
    
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

# Function to measure execution time
benchmark() {
    local cmd=$1
    local name=$2
    local iterations=$3
    
    total_time=0
    for ((i=1; i<=$iterations; i++)); do
        start_time=$(date +%s.%N)
        eval $cmd >/dev/null 2>&1
        end_time=$(date +%s.%N)
        execution_time=$(echo "$end_time - $start_time" | bc)
        total_time=$(echo "$total_time + $execution_time" | bc)
    done
    
    average_time=$(echo "scale=6; $total_time / $iterations" | bc)
    TIMING_RESULTS[$name]=$average_time
}

# Create complex test environment
setup_advanced_test_env() {
    echo -e "${BLUE}Setting up advanced test environment...${NC}"
    rm -rf test_dir
    mkdir -p test_dir
    
    # Create deep directory structure
    mkdir -p test_dir/level1/level2/level3/level4/level5
    
    # Create many files with different timestamps
    for i in {1..100}; do
        echo "content$i" > "test_dir/file$i"
        sleep 0.01  # Small delay for different timestamps
    done
    
    # Create files with special characters
    touch "test_dir/file with spaces"
    touch "test_dir/file'with'quotes"
    touch "test_dir/file#with#special@chars"
    
    # Create different types of files
    mkfifo test_dir/testpipe 2>/dev/null
    ln -s "file1" "test_dir/symlink1"
    ln "test_dir/file1" "test_dir/hardlink1"
    
    # Create hidden files and directories
    touch test_dir/.hidden1
    touch test_dir/.hidden2
    mkdir test_dir/.hidden_dir
    touch test_dir/.hidden_dir/.hidden_file
    
    # Create files with different permissions
    touch test_dir/no_permissions
    chmod 000 test_dir/no_permissions
    touch test_dir/executable
    chmod 755 test_dir/executable
    
    # Create large directory structure for performance testing
    mkdir -p test_dir/big_dir
    for i in {1..1000}; do
        echo "content" > "test_dir/big_dir/file$i"
        if [ $((i % 100)) -eq 0 ]; then
            mkdir -p "test_dir/big_dir/dir$i"
            for j in {1..10}; do
                echo "subcontent" > "test_dir/big_dir/dir$i/subfile$j"
            done
        fi
    done
}

# Run advanced tests
run_advanced_tests() {
    echo -e "${BLUE}Running advanced tests...${NC}"
    
    # Basic edge cases
    compare_ls "" "test_dir/file with spaces" "File with spaces"
    compare_ls "" "test_dir/file'with'quotes" "File with quotes"
    compare_ls "" "test_dir/file#with#special@chars" "File with special chars"
    
    # Permission tests
    compare_ls "-l" "test_dir/no_permissions" "File with no permissions"
    compare_ls "-l" "test_dir/executable" "Executable file"
    
    # Deep recursion
    compare_ls "-R" "test_dir/level1" "Deep directory recursion"
    
    # Multiple arguments with different types
    compare_ls "-l" "test_dir/symlink1 test_dir/hardlink1" "Different link types"
    
    # Hidden files in subdirectories
    compare_ls "-Ra" "test_dir/.hidden_dir" "Hidden files in subdirectories"
}

# Run performance tests
run_performance_tests() {
    echo -e "${BLUE}Running performance tests...${NC}"
    
    # Test cases with iterations
    benchmark "LC_ALL=C ./ft_ls test_dir/big_dir" "Simple ls" 5
    benchmark "LC_ALL=C ./ft_ls -l test_dir/big_dir" "Long format" 5
    benchmark "LC_ALL=C ./ft_ls -laR test_dir/big_dir" "Recursive" 3
    
    # Compare with system ls
    benchmark "LC_ALL=C ls test_dir/big_dir" "System ls" 5
    benchmark "LC_ALL=C ls -l test_dir/big_dir" "System ls long" 5
    benchmark "LC_ALL=C ls -laR test_dir/big_dir" "System ls recursive" 3
    
    # Print results
    echo -e "\n${BLUE}Performance Results (average time in seconds):${NC}"
    printf "%-20s %-10s %-10s %-10s\n" "Operation" "ft_ls" "ls" "Difference"
    printf "%-20s %-10f %-10f %-10f\n" \
        "Simple listing" ${TIMING_RESULTS["Simple ls"]} ${TIMING_RESULTS["System ls"]} \
        $(echo "${TIMING_RESULTS["Simple ls"]} - ${TIMING_RESULTS["System ls"]}" | bc)
    printf "%-20s %-10f %-10f %-10f\n" \
        "Long format" ${TIMING_RESULTS["Long format"]} ${TIMING_RESULTS["System ls long"]} \
        $(echo "${TIMING_RESULTS["Long format"]} - ${TIMING_RESULTS["System ls long"]}" | bc)
    printf "%-20s %-10f %-10f %-10f\n" \
        "Recursive" ${TIMING_RESULTS["Recursive"]} ${TIMING_RESULTS["System ls recursive"]} \
        $(echo "${TIMING_RESULTS["Recursive"]} - ${TIMING_RESULTS["System ls recursive"]}" | bc)
}

# Main execution
echo -e "${BLUE}Starting comprehensive ft_ls testing...${NC}"

setup_advanced_test_env
run_advanced_tests
run_performance_tests

echo -e "\n${BLUE}Test Results: $PASSED/$TOTAL passed${NC}"
if [ $PASSED -eq $TOTAL ]; then
    echo -e "${GREEN}All tests passed!${NC}"
else
    echo -e "${RED}Some tests failed.${NC}"
fi

echo -e "\n${BLUE}Cleaning up...${NC}"
rm -rf test_dir
