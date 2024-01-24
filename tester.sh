#!/bin/bash

SHELL_PROGRAM="./minishell"

# Run a test and check the result
run_test()
{
    test_name=$1
    expected_output=$2
    command_to_run=$3

    echo -n "Running test $test_name... "

    actual_output=$($SHELL_PROGRAM $command_to_run)

    if [ "$actual_output" = "$expected_output" ]; then
        echo "$(tput setaf 2)OK$(tput sgr0)"  # Green color for OK
    else
        echo "$(tput setaf 1)FAILED$(tput sgr0)"  # Red color for FAILED
        echo "  Expected: $expected_output"
        echo "  Actual  : $actual_output"
    fi
}

# Tests
run_test "cd" "minishell> " "cd ../../../../../.."
run_test "Echo" "minishell> " "echo"
run_test "Test 3" "minishell> " "pwd: ~"
run_test "Test 4" "minishell> " "pwd: ~/Desktop"

# echo "Testing complete."
