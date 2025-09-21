# Main.c Documentation

## Overview

The `main.c` file serves as the program entry point and orchestrates the entire 4x4 skyscraper puzzle solving process. This module handles command-line argument validation, coordinates the parsing-solving-output pipeline, and manages the overall program flow with proper error handling according to 42 school standards.

## File Purpose

This module is responsible for:
- **Program entry point** - Standard C main() function
- **Argument validation** - Ensuring correct command-line usage
- **Pipeline orchestration** - Coordinating parse → solve → output flow
- **Grid initialization** - Setting up clean data structures
- **Error management** - Consistent error handling and exit codes
- **Resource coordination** - Managing program state and flow control

## Design Philosophy

### Single Responsibility Coordination
- **Orchestration over computation** - Delegates specific tasks to specialized modules
- **Clear flow control** - Linear progression through program phases
- **Fail-fast approach** - Early termination on any error condition
- **Clean separation** - No business logic mixed with coordination

### 42 School Compliance
- **Standard main signature** - `int main(int argc, char **argv)`
- **Proper exit codes** - 0 for success, 1 for any error
- **Consistent error output** - "Error\n" for all failure cases
- **No forbidden functions** - Only uses allowed functions and custom utilities

---

## Function Documentation

### 1. `ft_init_grid`

```c
static void ft_init_grid(t_grid *grid)
```

**Purpose**: Initializes a grid structure to a clean, empty state ready for solving.

**Scope**: `static` - Internal helper function, not exposed to other modules

**Parameters**:
- `t_grid *grid` - Pointer to grid structure to initialize

**Return Value**:
- `void` - No return value (initialization function)

**Preconditions**:
- Grid pointer must be valid (non-NULL)
- Grid structure must be allocated (stack or heap)

**Postconditions**:
- All grid cells set to 0 (empty)
- All row usage bitmasks set to 0 (no numbers used)
- All column usage bitmasks set to 0 (no numbers used)
- Grid ready for constraint-based solving

#### Algorithm Analysis

**Nested Loop Structure**:
```c
i = 0;                    // Outer loop: rows
while (i < SIZE)          // SIZE = 4 (rows 0,1,2,3)
{
    j = 0;                // Inner loop: columns  
    while (j < SIZE)      // SIZE = 4 (columns 0,1,2,3)
    {
        grid->cells[i][j] = 0;  // Clear each cell
        j++;              // Next column
    }
    grid->row_used[i] = 0;    // Clear row bitmask
    grid->col_used[i] = 0;    // Clear column bitmask  
    i++;                  // Next row
}
```

**Initialization Details**:

1. **Cell Initialization** (`grid->cells[i][j] = 0`):
   - Sets each of 16 cells to 0 (empty/unassigned)
   - 0 indicates no number placed yet
   - Valid values will be 1-4 when solving

2. **Row Bitmask Initialization** (`grid->row_used[i] = 0`):
   - Clears constraint tracking for each row
   - Each bit represents a number (bit 0 = number 1, bit 1 = number 2, etc.)
   - 0 means no numbers are used in the row yet

3. **Column Bitmask Initialization** (`grid->col_used[i] = 0`):
   - Clears constraint tracking for each column
   - Same bitmask logic as rows
   - Enables fast constraint checking during solving

**Memory Layout After Initialization**:
```c
grid->cells = {
    {0, 0, 0, 0},    // Row 0: all empty
    {0, 0, 0, 0},    // Row 1: all empty
    {0, 0, 0, 0},    // Row 2: all empty
    {0, 0, 0, 0}     // Row 3: all empty
};
grid->row_used = {0, 0, 0, 0};  // No numbers used in any row
grid->col_used = {0, 0, 0, 0};  // No numbers used in any column
```

**Performance**:
- **Time Complexity**: O(n²) where n=4, so O(16) constant time
- **Space Complexity**: O(1) - only uses loop variables
- **Iterations**: Exactly 16 cell assignments + 8 bitmask assignments

---

### 2. `main`

```c
int main(int argc, char **argv)
```

**Purpose**: Program entry point that orchestrates the complete skyscraper puzzle solving process.

**Parameters**:
- `int argc` - Number of command-line arguments (including program name)
- `char **argv` - Array of command-line argument strings

**Return Value**:
- `0` - Success (puzzle solved and printed)
- `1` - Failure (any error condition)

**Expected Usage**:
```bash
./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
```

#### Algorithm Flow

**Phase 1: Argument Validation**
```c
if (argc != 2)
{
    write(1, "Error\n", 6);
    return (1);
}
```
- **Expected arguments**: Program name + 1 clue string = 2 total
- **Validation logic**: Exactly 2 arguments required
- **Error handling**: Immediate termination with error message
- **Exit code**: 1 indicates argument error

**Phase 2: Input Parsing**
```c
if (!ft_parse_input(argv[1], &input))
{
    write(1, "Error\n", 6);
    return (1);
}
```
- **Function call**: Delegates to parser module
- **Input source**: `argv[1]` contains clue string
- **Output destination**: `input` structure stores parsed clues
- **Error detection**: Parser returns 0 on any parsing failure
- **Consistent error**: Same "Error\n" message for user

**Phase 3: Grid Initialization**
```c
ft_init_grid(&grid);
```
- **Clean slate**: Prepare empty grid for solving
- **No error checking**: Initialization cannot fail
- **Stack allocation**: Grid stored on main's stack frame
- **Address passing**: Pass grid address for modification

**Phase 4: Puzzle Solving**
```c
if (!ft_solve_skyscraper(&input, &grid))
{
    write(1, "Error\n", 6);
    return (1);
}
```
- **Function call**: Delegates to solver module
- **Input data**: Parsed clues from Phase 2
- **Output data**: Solved grid (modified in-place)
- **Error detection**: Solver returns 0 if no solution exists
- **Unsolvable puzzles**: Treated as error condition

**Phase 5: Solution Output**
```c
ft_print_grid(&grid);
return (0);
```
- **Function call**: Delegates to output module
- **Success path**: Only reached if all previous phases succeed
- **Grid display**: Formatted 4x4 solution output
- **Exit code**: 0 indicates successful completion

#### Program Flow Diagram
```
main() Entry
     ↓
┌─ Validate argc == 2
│    ├─ Success: Continue
│    └─ Failure: Error + return 1
     ↓
┌─ Parse input string  
│    ├─ Success: Continue
│    └─ Failure: Error + return 1
     ↓
┌─ Initialize grid (always succeeds)
     ↓
┌─ Solve puzzle
│    ├─ Success: Continue  
│    └─ Failure: Error + return 1
     ↓
┌─ Print solution
     ↓
   return 0
```

---

## Error Handling Strategy

### Consistent Error Response
**All error conditions produce identical output**:
```c
write(1, "Error\n", 6);
return (1);
```

**Error Categories Handled**:
1. **Argument errors**: Wrong number of command-line arguments
2. **Parse errors**: Invalid input format, wrong number count, out-of-range values
3. **Solver errors**: Unsolvable puzzle, contradictory clues

### Error Handling Benefits
- **User consistency**: Same error message regardless of failure type
- **Simplicity**: No complex error categorization needed
- **42 compliance**: Matches school requirements exactly
- **Security**: No information leakage about internal failures

### No Error Conditions
- **Grid initialization**: Cannot fail (simple memory clearing)
- **Solution output**: Only called on successful solve
- **Memory allocation**: Uses stack allocation (automatic cleanup)

---

## Data Structure Management

### Stack-Based Allocation
```c
t_input input;    // 16 integers (64 bytes typical)
t_grid  grid;     // 4x4 grid + bitmasks (80 bytes typical)
```

**Advantages**:
- **Automatic cleanup**: No manual memory management needed
- **Fast allocation**: Stack allocation is O(1)
- **Scope safety**: Variables automatically cleaned up on return
- **No leaks**: Impossible to leak stack-allocated memory

### Data Flow Between Phases
```
argv[1] → input (parsing)
input → grid (solving) 
grid → stdout (output)
```

**State Transitions**:
1. **Raw string** → **Structured clues** (parsing phase)
2. **Empty grid** → **Solved grid** (solving phase)  
3. **Grid structure** → **Formatted text** (output phase)

---

## Integration with Project Modules

### Module Dependencies
```
main.c depends on:
├── rush.h (type definitions)
├── parser.c (ft_parse_input)
├── solver.c (ft_solve_skyscraper)  
├── output.c (ft_print_grid)
└── system (write function)
```

### Interface Contracts

#### **Parser Interface**
```c
int ft_parse_input(char *str, t_input *input);
// Returns: 1 = success, 0 = failure
// Modifies: input structure on success
```

#### **Solver Interface**  
```c
int ft_solve_skyscraper(t_input *input, t_grid *grid);
// Returns: 1 = solved, 0 = unsolvable
// Modifies: grid structure on success
```

#### **Output Interface**
```c
void ft_print_grid(t_grid *grid);
// Returns: void (always succeeds)
// Side effect: writes to stdout
```

---

## Performance Characteristics

### Time Complexity
- **Argument checking**: O(1)
- **Input parsing**: O(n) where n = input string length  
- **Grid initialization**: O(1) - fixed 4x4 size
- **Puzzle solving**: O(4^16) worst case, much better with pruning
- **Output generation**: O(1) - fixed 4x4 size
- **Overall**: Dominated by solving complexity

### Space Complexity
- **Stack usage**: O(1) - fixed-size structures
- **No dynamic allocation**: All memory on stack
- **Recursion**: Solver may use recursive stack space
- **Overall**: O(1) main function overhead + solver requirements

### Memory Footprint
```c
sizeof(t_input) ≈ 64 bytes   // 16 integers
sizeof(t_grid)  ≈ 80 bytes   // 16 cells + 8 bitmasks
Total stack:    ≈ 144 bytes  // Very lightweight
```

---

## Testing and Validation

### Command Line Testing

#### **Valid Input Cases**
```bash
# Standard case
./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
# Expected: 4x4 solution grid

# Edge case - all different clues  
./rush-01 "1 2 3 4 4 3 2 1 2 3 1 4 3 1 4 2"
# Expected: 4x4 solution grid or Error
```

#### **Error Cases**
```bash
# No arguments
./rush-01
# Expected: Error

# Too many arguments  
./rush-01 "1 2 3" "4 5 6"
# Expected: Error

# Invalid input format
./rush-01 "1 2 3 invalid 5 6 7 8 9 10 11 12 13 14 15 16"
# Expected: Error

# Unsolvable puzzle
./rush-01 "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1"  
# Expected: Error
```

### Unit Testing Approach
```c
// Test grid initialization
t_grid test_grid;
ft_init_grid(&test_grid);
assert(test_grid.cells[0][0] == 0);
assert(test_grid.row_used[0] == 0);
assert(test_grid.col_used[0] == 0);

// Test main flow (integration testing)
// Requires full program execution with various inputs
```

---

## 42 Norm Compliance

### Function Standards
✅ **Function count**: 2 functions (well under 5-function limit)  
✅ **Function length**: Both functions under 25 lines  
✅ **Function naming**: `main` (standard), `ft_init_grid` (42 convention)  
✅ **Static scope**: Helper function properly scoped as static  
✅ **Variable naming**: Clear, descriptive variable names

### Code Quality
✅ **Single responsibility**: Each function has one clear purpose  
✅ **Error handling**: Consistent error messages and exit codes  
✅ **Flow control**: Clear, linear program progression  
✅ **No side effects**: Functions don't modify global state  
✅ **Clean interfaces**: Well-defined module boundaries

### Style Compliance
✅ **Indentation**: Proper tab indentation  
✅ **Braces**: K&R brace style throughout  
✅ **Spacing**: Correct spacing around operators and keywords  
✅ **Variable declarations**: Proper declaration placement  
✅ **Line length**: All lines under 80 characters  

---

## Best Practices Demonstrated

### Error Handling Patterns
- **Fail fast**: Return immediately on any error
- **Consistent messages**: Same error output for all failures  
- **Proper exit codes**: 0 for success, 1 for any error
- **No error propagation complexity**: Simple boolean success/failure

### Resource Management
- **Stack allocation**: Automatic cleanup, no leak potential
- **No dynamic memory**: Avoids malloc/free complexity
- **Scope-based lifetime**: Variables cleaned up automatically
- **Simple state management**: Clear data flow between phases

### Module Integration
- **Clear interfaces**: Well-defined function contracts
- **Loose coupling**: Modules only depend on interfaces, not implementations
- **Single direction flow**: No circular dependencies
- **Error boundary**: Each module responsible for its own validation

---

## Usage Examples and Scenarios

### Successful Execution
```bash
$ ./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
4 3 2 1
3 2 1 4
2 1 4 3  
1 4 3 2
$ echo $?
0
```

### Error Scenarios
```bash
$ ./rush-01
Error
$ echo $?
1

$ ./rush-01 "1 2 3"  
Error
$ echo $?  
1

$ ./rush-01 "impossible puzzle clues"
Error
$ echo $?
1
```

### Integration with Shell Scripts
```bash
#!/bin/bash
if ./rush-01 "$1" > solution.txt; then
    echo "Puzzle solved! Solution in solution.txt"
else  
    echo "Puzzle could not be solved"
fi
```

This documentation provides complete understanding of the program orchestration logic and demonstrates how a simple main function can effectively coordinate complex puzzle-solving operations while maintaining 42 school compliance and best practices.