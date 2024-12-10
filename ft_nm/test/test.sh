#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Test files array
FILES=(
   "error_header"
   "header"
   "header_and_prog" 
   "header_and_prog_copy"
   "header_copy"
   "header_offset_error"
   "not_so_easy_test"
   "test_facile"
   "unterminated_string"
   "wrong_arch"
)

# Function to test single file
test_file() {
   local file=$1
   
   # Run both nm and ft_nm, capture output and return code
   nm_out=$(nm "$file" 2>/dev/null)
   nm_ret=$?
   ft_nm_out=$(../ft_nm "$file" 2>/dev/null)
   ft_nm_ret=$?
   
   # Compare return codes
   if [ $nm_ret -ne $ft_nm_ret ]; then
       printf "${RED}FAIL${NC} $file (return codes differ: nm=$nm_ret, ft_nm=$ft_nm_ret)\n"
       return
   fi
   
   # Compare outputs
   if [ "$nm_out" = "$ft_nm_out" ]; then
       printf "${GREEN}OK${NC} $file\n"
   else
       printf "${RED}FAIL${NC} $file (outputs differ)\n"
       # Create diff file
       diff <(echo "$nm_out") <(echo "$ft_nm_out") > "diff_${file}.txt"
   fi
}

# Main test loop
echo "Testing ft_nm against nm..."
for file in "${FILES[@]}"; do
   test_file "$file"
done
