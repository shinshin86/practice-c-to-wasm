#!/bin/bash

# make test directory
mkdir target_directory
echo "This is a test file." > target_directory/file1.txt
echo "Another test file." > target_directory/file2.txt

# compile
clang rlezip.c -o rlezip

# zip
./rlezip

# check for created zip file
if [ ! -f output.zip ]; then
    echo "Error: ZIP file not created!"
    exit 1
fi


# cleanup
rm -r target_directory
rm output.zip
rm rlezip
