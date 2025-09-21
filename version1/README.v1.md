# 42 Rush-01: 4x4 Skyscraper Puzzle Solver

## Overview

This project is a 4x4 skyscraper puzzle solver implemented according to 42 school standards. A skyscraper puzzle is a logic puzzle where you must place numbers 1-4 in a 4x4 grid such that each row and column contains all numbers exactly once, and the visibility clues around the edges are satisfied.

## How Skyscraper Puzzles Work

### Rules
1. Fill a 4x4 grid with numbers 1-4
2. Each row must contain numbers 1, 2, 3, 4 exactly once
3. Each column must contain numbers 1, 2, 3, 4 exactly once
4. Numbers represent building heights
5. Clues around the edges indicate how many buildings are visible from that direction

### Visibility Rules
- A taller building blocks the view of shorter buildings behind it
- From any direction, you can only see buildings that are taller than all buildings in front of them

### Input Format
The program expects 16 numbers as input representing clues in this order:
```
    col0 col1 col2 col3
      ↓    ↓    ↓    ↓
    [ 4    3    2    1  ]  ← top clues
    [ 1    2    2    2  ]  ← bottom clues
    [ 4    3    2    1  ] ← → left clues
    [ 1    2    2    2  ] ← → right clues
```

## Project Structure

### Files Overview

| File | Purpose |
|------|---------|
| `rush.h` | Header file with all structures and function prototypes |
| `main.c` | Entry point and main program logic |
| `parser.c` | Input parsing and validation |
| `utils.c` | Utility functions for output and basic operations |
| `vis.c` | Visibility calculation functions |
| `solver.c` | Core solving algorithm with backtracking |
| `Makefile` | Build configuration |
| `test.c` | Simple test program |

---

## File Details

### 1. `rush.h` - Header File

**Purpose**: Contains all type definitions, constants, and function prototypes.

**Key Components**:
- `#define SIZE 4` - Fixed grid size for optimization
- Function declarations for allowed functions: `write`, `malloc`, `free`
- Structure definitions
- All function prototypes

**Structures**:
```c
typedef struct s_input {
    int clues[16];  // All 16 clues in order: top, bottom, left, right
} t_input;

typedef struct s_grid {
    int cells[4][4];    // The 4x4 grid
    int row_used[4];    // Bitmask of used numbers per row
    int col_used[4];    // Bitmask of used numbers per column
} t_grid;
```

---

### 2. `main.c` - Entry Point

**Purpose**: Program entry point with argument validation and main flow control.

**Functions**:
- `static void ft_init_grid(t_grid *grid)`
  - Initializes all grid cells to 0
  - Resets all bitmasks to 0
  
- `int main(int argc, char **argv)`
  - Validates argument count
  - Calls parser, solver, and output functions
  - Handles error cases with "Error\n" output

**Flow**:
1. Check argc == 2
2. Parse input string
3. Initialize empty grid
4. Solve the puzzle
5. Print solution or error

---

### 3. `parser.c` - Input Processing

**Purpose**: Parse and validate the input string containing 16 clue numbers.

**Functions**:
- `static int ft_count_numbers(char *str)`
  - Counts numeric tokens in input string
  - Returns total count of numbers found

- `static int ft_extract_numbers(char *str, int *numbers)`
  - Extracts exactly 16 numbers from input string
  - Handles multi-digit numbers correctly
  - Returns number of extracted values

- `static int ft_validate_clues(int *clues)`
  - Ensures all clues are in range [1, 4]
  - Returns 1 if valid, 0 otherwise

- `int ft_parse_input(char *str, t_input *input)`
  - Main parsing function
  - Validates input has exactly 16 numbers
  - Stores parsed clues in input structure

**Input Format**: "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"

---

### 4. `utils.c` - Utility Functions

**Purpose**: Basic I/O and helper functions using only allowed functions.

**Functions**:
- `int ft_is_space(char c)`
  - Checks if character is whitespace
  - Supports space, tab, newline, carriage return

- `int ft_is_digit(char c)`
  - Checks if character is a digit (0-9)

- `void ft_putchar(char c)`
  - Outputs single character using write()

- `void ft_putstr(char *str)`
  - Outputs string character by character

- `void ft_putnbr(int n)`
  - Outputs integer recursively
  - Handles multi-digit numbers

- `void ft_print_grid(t_grid *grid)`
  - Prints the solved 4x4 grid
  - Format: "1 2 3 4\n2 3 4 1\n..."

---

### 5. `vis.c` - Visibility Calculations

**Purpose**: Calculate visible buildings from each direction.

**Functions**:
- `int ft_count_visible_left(int *row)`
  - Counts buildings visible from left side of row
  - Iterates left to right, tracking maximum height

- `int ft_count_visible_right(int *row)`
  - Counts buildings visible from right side of row
  - Iterates right to left, tracking maximum height

- `int ft_count_visible_top(t_grid *grid, int col)`
  - Counts buildings visible from top of column
  - Iterates top to bottom, tracking maximum height

- `int ft_count_visible_bottom(t_grid *grid, int col)`
  - Counts buildings visible from bottom of column
  - Iterates bottom to top, tracking maximum height

**Algorithm**: For each direction, maintain running maximum height and count buildings that exceed the current maximum.

---

### 6. `solver.c` - Core Solving Logic

**Purpose**: Implements backtracking algorithm to solve the puzzle.

**Functions**:
- `int ft_is_valid_placement(t_grid *grid, int row, int col, int val)`
  - Checks if value can be placed at position
  - Uses bitmasks to verify row/column constraints

- `void ft_place_value(t_grid *grid, int row, int col, int val)`
  - Places value in grid
  - Updates row and column bitmasks

- `void ft_remove_value(t_grid *grid, int row, int col, int val)`
  - Removes value from grid (backtrack)
  - Updates row and column bitmasks

- `static int ft_check_row_visibility(t_grid *grid, int row, t_input *input)`
  - Validates row against left/right clues
  - Uses visibility counting functions

- `static int ft_check_col_visibility(t_grid *grid, int col, t_input *input)`
  - Validates column against top/bottom clues
  - Uses visibility counting functions

- `int ft_check_visibility(t_grid *grid, t_input *input)`
  - Validates entire grid against all clues
  - Called when grid is complete

- `static int ft_backtrack(t_grid *grid, t_input *input, int pos)`
  - Recursive backtracking solver
  - Tries values 1-4 at each position
  - Position 0-15 represents cells row-wise

- `int ft_solve_skyscraper(t_input *input, t_grid *grid)`
  - Main solving function
  - Starts backtracking from position 0

**Algorithm**: Recursive backtracking with constraint checking at each step.

---

## How to Use

### Compilation
```bash
make
# or
gcc -Wall -Wextra -Werror *.c -o rush-01
```

### Running the Program
```bash
./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
```

### Input Format
- Single argument string with 16 space-separated numbers
- Numbers must be in range [1, 4]
- Order: top_clues bottom_clues left_clues right_clues
- Each group has 4 numbers for columns/rows 0-3

### Output
**Success**: 4x4 grid with solution
```
4 3 2 1
2 1 4 3
3 4 1 2
1 2 3 4
```

**Error**: "Error\n" for invalid input or unsolvable puzzle

---

## Testing

### Test Cases

#### Test Case 1: Simple Case
```bash
./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
```
Expected: Valid solution (grid will be displayed)

#### Test Case 2: All 1s (Impossible)
```bash
./rush-01 "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"
```
Expected: "Error\n"

#### Test Case 3: All 4s (Impossible)
```bash
./rush-01 "4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4"
```
Expected: "Error\n"

#### Test Case 4: Invalid Input (wrong count)
```bash
./rush-01 "1 2 3 4 5"
```
Expected: "Error\n"

#### Test Case 5: Invalid Values
```bash
./rush-01 "0 1 2 3 4 5 6 7 8 9 1 2 3 4 5 6"
```
Expected: "Error\n"

### Manual Testing with test.c
Compile and run the test file:
```bash
gcc -Wall -Wextra -Werror test.c parser.c utils.c vis.c solver.c -o test
./test
```

### Validation Methods
1. **Parse validation**: Check input format and ranges
2. **Constraint validation**: Verify sudoku-like constraints during solving
3. **Visibility validation**: Check all clues are satisfied in final solution
4. **Memory validation**: Ensure no leaks (minimal malloc usage)

### Error Cases Handled
- Wrong number of arguments
- Invalid input format
- Numbers out of range [1, 4]
- Unsolvable puzzles
- Contradictory clues

---

## Algorithm Complexity

**Time Complexity**: O(4^16) worst case, but with pruning typically much faster
**Space Complexity**: O(1) - fixed size structures, minimal recursion depth

## 42 School Compliance

✅ **Function restrictions**: Only uses `write`, `malloc`, `free`  
✅ **Norm compliance**: All functions under 25 lines  
✅ **Naming convention**: All functions prefixed with `ft_`  
✅ **Header structure**: Clean prototypes and structures  
✅ **Error handling**: Consistent "Error\n" output  
✅ **Memory management**: No leaks, minimal allocation  
✅ **Makefile**: Standard 42 Makefile format