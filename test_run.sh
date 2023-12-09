#!/bin/bash

# Check if a file path is provided as an argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <commands_file>"
    exit 1
fi

# Assign the input file to a variable
commands_file="$1"

# Check if the file exists
if [ ! -f "$commands_file" ]; then
    echo -e "\e[31mError: File not found - $commands_file\e[0m" >&2
    exit 1
fi

# Read and execute commands from the file
while IFS= read -r command; do
    echo "Executing: $command"
    eval "$command"
    exit_code=$?
    
    if [ $exit_code -ne 0 ]; then
        echo -e "\e[31mError: Command failed with exit code $exit_code\e[0m" >&2
        exit $exit_code
    else
        echo -e "\e[32mSuccess: Command executed successfully\e[0m"
    fi
done < "$commands_file"

echo -e "\e[32mAll commands executed successfully\e[0m"
exit 0
