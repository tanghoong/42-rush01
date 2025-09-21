# Rush-01: Skyscraper Puzzle Solver (Version 2)

## Overview

This is a C implementation of a **Skyscraper Puzzle Solver** for 4×4 grids. The puzzle is a logic-based game where you must fill a 4×4 grid with numbers 1-4, ensuring that each number appears exactly once in each row and column, while also satisfying visibility constraints from the edges of the grid.

## How the Skyscraper Puzzle Works

In a Skyscraper puzzle:
- Fill a 4×4 grid with numbers 1-4
- Each row and column must contain all numbers 1-4 exactly once (like Sudoku)
- Numbers represent building heights (1 = shortest, 4 = tallest)
- Clues around the border indicate how many "buildings" are visible from that direction
- Taller buildings hide shorter ones behind them

Example:
```
   2 1 3 2    <- Top clues
2 [         ] 1
3 [         ] 2  <- Right clues  
1 [         ] 3
3 [         ] 2
   ^ Left clues
   2 2 1 3
   ^ Bottom clues
```

## Project Structure

```
version2/
├── rush.h          # Header file with function declarations and constants
├── main.c          # Main program entry point and memory management
├── parser.c        # Input parsing and validation
├── solver.c        # Core backtracking algorithm
├── vis.c           # Visibility calculation functions
├── check.c         # Grid validation functions  
├── output.c        # Grid printing functions
├── utils.c         # Basic utility functions (putchar, putstr, etc.)
├── string_utils.c  # String manipulation utilities
├── Makefile        # Build configuration
└── rush-01         # Compiled executable
```

## Features

### Core Functionality
- **Backtracking Algorithm**: Efficient recursive solution finding
- **Constraint Validation**: Real-time checking of Sudoku and visibility rules
- **Input Parsing**: Robust parsing of space-separated clue strings
- **Memory Management**: Safe allocation and deallocation of dynamic memory
- **Error Handling**: Comprehensive error checking and reporting

### Technical Highlights
- **Modular Design**: Clean separation of parsing, solving, and output logic
- **42 School Standards**: Follows strict coding norms (norminette compliant)
- **No Standard Library**: Custom implementations of basic functions
- **Optimized Solving**: Early termination on invalid placements

## Compilation

### Using Makefile
```bash
make
```

### Manual Compilation
```bash
gcc -Wall -Wextra -Werror -o rush-01 main.c parser.c utils.c vis.c solver.c output.c check.c string_utils.c
```

### Clean Build Files
```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Clean and rebuild
```

## Usage

```bash
./rush-01 "clue1 clue2 clue3 ... clue16"
```

The program expects exactly 16 space-separated integers as input, representing the visibility clues in this order:
1. **Positions 0-3**: Top row (left to right)
2. **Positions 4-7**: Bottom row (left to right)  
3. **Positions 8-11**: Left column (top to bottom)
4. **Positions 12-15**: Right column (top to bottom)

### Example Usage

```bash
# Example 1: Basic puzzle
./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"

# Example 2: Another valid puzzle  
./rush-01 "2 1 3 2 2 2 1 3 2 3 1 3 1 2 3 2"

# Error cases
./rush-01 "1 2 3"           # Too few clues
./rush-01 "1 2 3 4 5 4 3 2 1 2 3 4 5 4 3 2 1"  # Too many clues
./rush-01 "0 1 2 3 1 2 3 4 1 2 3 4 1 2 3 4"     # Invalid clue (0)
```

## Algorithm Overview

### 1. Input Parsing (`parser.c`)
- Validates input format and count
- Extracts 16 numeric clues
- Ensures clues are in valid range (1-4)

### 2. Grid Initialization (`utils.c`)
- Creates empty 4×4 grid
- Sets up tracking arrays for row/column constraints

### 3. Backtracking Solver (`solver.c`)
- Places numbers 1-4 systematically in each cell
- Validates Sudoku constraints (unique in row/column)
- Checks visibility constraints after each row/column completion
- Backtracks on invalid states

### 4. Visibility Checking (`vis.c`)
- Counts visible buildings from each direction
- Implements line-of-sight calculation
- Validates against provided clues

### 5. Output (`output.c`)
- Prints solved grid in required format
- Handles error messages

## Code Architecture

### Memory Management
- Dynamic allocation for grid and clues arrays
- Proper cleanup on both success and error paths
- Null pointer checking throughout

### Error Handling
- Input validation at multiple levels
- Graceful failure with "Error\n" output
- Memory leak prevention

### Performance Optimizations
- Early constraint checking during backtracking
- Efficient visibility calculation algorithms
- Minimal memory footprint

## Testing

The solver can handle various puzzle difficulties:
- **Easy**: Puzzles with many constraint hints
- **Medium**: Balanced constraint distribution  
- **Hard**: Minimal clues requiring extensive backtracking
- **Invalid**: Unsolvable configurations (returns "Error")

## Return Values

- **0**: Success - puzzle solved and printed
- **1**: Error - invalid input, unsolvable puzzle, or memory allocation failure

## Dependencies

- **Compiler**: GCC with C99 standard
- **System Calls**: Only `write()` and `malloc()`/`free()`
- **No External Libraries**: All utilities implemented from scratch

## 42 School Compliance

This implementation follows 42 School coding standards:
- ✅ Norminette compliant
- ✅ No forbidden functions
- ✅ Proper error handling
- ✅ Memory management
- ✅ 25-line function limit
- ✅ 80-column line limit

## Author Notes

This version (v2) represents an improved implementation with:
- Better code organization and modularity
- Enhanced error handling and input validation
- Optimized solving algorithm
- Cleaner separation of concerns
- More robust memory management

---

*This project is part of the 42 School Rush programming challenges, focusing on algorithmic thinking, constraint satisfaction, and clean C programming practices.*