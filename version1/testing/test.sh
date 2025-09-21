#!/bin/bash

# Shell test script for 42-rush01 skyscraper puzzle
# This script mimics the logic of test.c

echo "Starting Rush-01 Skyscraper Puzzle Test"

# Test case parameters (same as in test.c)
TEST_CASE="4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"

echo "Test Case: $TEST_CASE"

# Change to the gpt directory where the C files are located
cd gpt || { echo "Error: Cannot change to gpt directory"; exit 1; }

# Check if executable exists, if not compile it
if [ ! -f "rush-01" ]; then
    echo "Compiling the program..."
    
    # Use make to compile if Makefile exists
    if [ -f "Makefile" ]; then
        make
    else
        # Fallback compilation
        gcc -Wall -Wextra -Werror -o rush-01 main.c parser.c solver.c check.c output.c utils.c vis.c
    fi
    
    if [ $? -ne 0 ]; then
        echo "Compilation failed!"
        exit 1
    fi
    
    echo "Compilation successful!"
fi

# Run the program with the test case
echo "Running test case..."

if [ -f "rush-01" ]; then
    # Run the program and capture output
    RESULT=$(./rush-01 $TEST_CASE)
    EXIT_CODE=$?
    
    echo "Program output:"
    echo "$RESULT"
    
    # Analyze the result
    if [ $EXIT_CODE -eq 0 ]; then
        echo "✓ Test PASSED: Program executed successfully"
        
        # Check if output contains a valid solution (4x4 grid)
        GRID_LINES=$(echo "$RESULT" | grep -E "^[[:space:]]*[1-4][[:space:]]+[1-4][[:space:]]+[1-4][[:space:]]+[1-4][[:space:]]*$" | wc -l)
        
        if [ "$GRID_LINES" -eq 4 ]; then
            echo "✓ Valid 4x4 solution grid detected"
            
            # Display the solution nicely
            echo ""
            echo "Solution Grid:"
            echo "┌─────────┐"
            echo "$RESULT" | grep -E "^[[:space:]]*[1-4][[:space:]]+[1-4][[:space:]]+[1-4][[:space:]]+[1-4][[:space:]]*$" | while read line; do
                formatted_line=$(echo "$line" | sed 's/[[:space:]]\+/ /g' | xargs)
                echo "│ $formatted_line │"
            done
            echo "└─────────┘"
        else
            echo "⚠ Warning: Expected 4x4 grid not found in output"
        fi
        
    else
        echo "✗ Test FAILED: Program returned exit code $EXIT_CODE"
    fi
    
else
    echo "✗ Error: Executable not found"
    exit 1
fi

echo ""
echo "Test completed."

# Additional test cases (optional)
echo ""
echo "Running additional test cases..."

ADDITIONAL_TESTS=(
    "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"  # Easy case
    "2 1 3 2 3 2 1 4 2 4 1 3 4 1 2 3"   # Another test case
)

for i in "${!ADDITIONAL_TESTS[@]}"; do
    TEST="${ADDITIONAL_TESTS[$i]}"
    echo ""
    echo "Additional Test $((i+1)): $TEST"
    
    RESULT=$(./rush-01 $TEST 2>&1)
    EXIT_CODE=$?
    
    if [ $EXIT_CODE -eq 0 ]; then
        echo "✓ Additional test $((i+1)) PASSED"
    else
        echo "✗ Additional test $((i+1)) FAILED (exit code: $EXIT_CODE)"
    fi
done

echo ""
echo "All tests completed!"

# Return to original directory
cd ..