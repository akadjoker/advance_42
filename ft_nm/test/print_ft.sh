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

clear

test_file() {
   local file=$1
   
   echo "--------------------------------------------"
   printf "${GREEN} $file ${NC} \n"
   nm_out=$(../ft_nm "$file" )
   printf "$nm_out\n"
 

}

# Main test loop
echo "Testing against ft_nm..."
for file in "${FILES[@]}"; do
   test_file "$file"
done



