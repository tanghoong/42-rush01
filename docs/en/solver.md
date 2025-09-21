# Solver.c Documentation

## Overview

The `solver.c` file contains the core solving engine for the 4x4 skyscraper puzzle. This module implements a constraint satisfaction algorithm using backtracking with efficient constraint checking through bitmasks. It represents the heart of the puzzle solver, where mathematical logic meets algorithmic efficiency to find valid solutions that satisfy all visibility clues.

## File Purpose

This module handles:
- **Constraint satisfaction** - Ensuring no duplicate numbers in rows/columns
- **Backtracking algorithm** - Systematic exploration of solution space
- **Efficient constraint checking** - Using bitmasks for fast validation
- **State management** - Placing and removing values with proper cleanup
- **Solution validation** - Integrating with visibility checking for complete validation
- **Optimization** - Pruning invalid branches early to improve performance

## Design Philosophy

### Constraint Satisfaction Problem (CSP)
A skyscraper puzzle is a classic CSP with:
- **Variables**: 16 grid cells (each needs a value 1-4)
- **Domain**: Each variable can take values {1, 2, 3, 4}
- **Constraints**: 
  - Row uniqueness (each row has 1,2,3,4 exactly once)
  - Column uniqueness (each column has 1,2,3,4 exactly once)
  - Visibility constraints (clues around the grid must be satisfied)

### Backtracking Strategy
- **Systematic exploration**: Try all possibilities in organized manner
- **Early pruning**: Reject partial solutions that can't lead to valid complete solutions
- **State restoration**: Undo changes when backtracking to explore alternatives
- **Depth-first search**: Explore one branch completely before trying alternatives

---

## Algorithm Overview

### Backtracking Process
```
1. If all 16 positions filled → validate complete solution
2. Find next empty position
3. For each possible value (1-4):
   a. Check if value violates constraints
   b. If valid: place value and recurse to next position
   c. If recursion succeeds → solution found
   d. If recursion fails → remove value and try next
4. If no values work → backtrack to previous position
```

### Constraint Checking Strategy
- **Bitmasks for efficiency**: O(1) constraint checking instead of O(n) array scanning
- **Immediate validation**: Check constraints before placing, not after
- **Complete validation**: Final visibility check only when grid is complete

---

## Function Documentation

### 1. `ft_is_valid_placement`

```c
int ft_is_valid_placement(t_grid *grid, int row, int col, int val)
```

**Purpose**: Determines if a value can be legally placed at a specific grid position without violating row/column uniqueness constraints.

**Parameters**:
- `t_grid *grid` - Current grid state with constraint tracking
- `int row` - Target row (0-3)
- `int col` - Target column (0-3)  
- `int val` - Value to place (1-4)

**Return Value**:
- `1` - Placement is valid (no constraint violations)
- `0` - Placement violates constraints (duplicate in row or column)

**Algorithm**:
```c
bit = 1 << (val - 1);                    // Convert value to bitmask
if (grid->row_used[row] & bit)           // Check row constraint
    return (0);                          // Value already used in row
if (grid->col_used[col] & bit)           // Check column constraint  
    return (0);                          // Value already used in column
return (1);                              // Valid placement
```

**Bitmask Logic**:
- **Value 1**: `bit = 1 << 0 = 0001` (bit 0)
- **Value 2**: `bit = 1 << 1 = 0010` (bit 1)  
- **Value 3**: `bit = 1 << 2 = 0100` (bit 2)
- **Value 4**: `bit = 1 << 3 = 1000` (bit 3)

**Constraint Checking**:
```c
// Example: row_used[0] = 0101 (values 1 and 3 used)
// Checking value 2: bit = 0010
// 0101 & 0010 = 0000 (false) → value 2 is available
// Checking value 1: bit = 0001  
// 0101 & 0001 = 0001 (true) → value 1 already used
```

**Performance**: O(1) - constant time using bitwise operations instead of O(n) array scanning.

---

### 2. `ft_place_value`

```c
void ft_place_value(t_grid *grid, int row, int col, int val)
```

**Purpose**: Places a value in the grid and updates constraint tracking structures.

**Parameters**:
- `t_grid *grid` - Grid to modify
- `int row` - Target row (0-3)
- `int col` - Target column (0-3)
- `int val` - Value to place (1-4)

**Return Value**: `void` - No return (state modification function)

**Algorithm**:
```c
bit = 1 << (val - 1);                    // Convert value to bitmask
grid->cells[row][col] = val;             // Place value in grid
grid->row_used[row] |= bit;              // Mark value as used in row
grid->col_used[col] |= bit;              // Mark value as used in column
```

**State Updates**:
1. **Grid modification**: Set cell to the specified value
2. **Row constraint update**: Set bit indicating value is used in this row
3. **Column constraint update**: Set bit indicating value is used in this column

**Example**:
```c
// Before: grid->cells[1][2] = 0, row_used[1] = 0001, col_used[2] = 0010
ft_place_value(grid, 1, 2, 3);
// After:  grid->cells[1][2] = 3, row_used[1] = 0101, col_used[2] = 0110
```

**Bitmask Update Logic**:
- **OR operation (`|=`)**: Sets the bit corresponding to the value
- **Preserves existing bits**: Other values remain marked as used
- **Atomic operation**: All three updates maintain consistent state

---

### 3. `ft_remove_value`

```c
void ft_remove_value(t_grid *grid, int row, int col, int val)
```

**Purpose**: Removes a value from the grid and updates constraint tracking (backtracking cleanup).

**Parameters**:
- `t_grid *grid` - Grid to modify
- `int row` - Target row (0-3)
- `int col` - Target column (0-3)
- `int val` - Value to remove (1-4)

**Return Value**: `void` - No return (state restoration function)

**Algorithm**:
```c
bit = 1 << (val - 1);                    // Convert value to bitmask
grid->cells[row][col] = 0;               // Clear cell (0 = empty)
grid->row_used[row] &= ~bit;             // Unmark value in row
grid->col_used[col] &= ~bit;             // Unmark value in column
```

**State Restoration**:
1. **Grid cleanup**: Reset cell to empty state (0)
2. **Row constraint cleanup**: Clear bit indicating value is no longer used in row
3. **Column constraint cleanup**: Clear bit indicating value is no longer used in column

**Bitmask Clearing Logic**:
- **NOT operation (`~`)**: Inverts bitmask (0001 becomes 1110)
- **AND operation (`&=`)**: Clears only the target bit
- **Preserves other bits**: Other values remain marked as used

**Example**:
```c
// Before: grid->cells[1][2] = 3, row_used[1] = 0101, col_used[2] = 0110
ft_remove_value(grid, 1, 2, 3);
// After:  grid->cells[1][2] = 0, row_used[1] = 0001, col_used[2] = 0010
```

**Critical for Backtracking**: Ensures clean state restoration when exploring alternative branches.

---

### 4. `ft_backtrack`

```c
static int ft_backtrack(t_grid *grid, t_input *input, int pos)
```

**Purpose**: Core recursive backtracking algorithm that systematically explores all possible solutions.

**Scope**: `static` - Internal engine function, not exposed outside module

**Parameters**:
- `t_grid *grid` - Current grid state (modified during search)
- `t_input *input` - Puzzle clues for final validation
- `int pos` - Current position in linear traversal (0-15)

**Return Value**:
- `1` - Solution found (success)
- `0` - No solution possible from current state

**Position Mapping**:
```c
row = pos / SIZE;    // Integer division: pos 0-3 → row 0, pos 4-7 → row 1, etc.
col = pos % SIZE;    // Modulo operation: pos 0,4,8,12 → col 0, pos 1,5,9,13 → col 1, etc.
```

**Linear Position Layout**:
```
pos:  0  1  2  3      row 0
      4  5  6  7      row 1  
      8  9 10 11      row 2
     12 13 14 15      row 3
```

**Algorithm Flow**:

#### **Base Case - Complete Grid**
```c
if (pos == 16)
    return (ft_check_visibility(grid, input));
```
- All 16 positions filled → validate complete solution against visibility clues
- Delegates to `check.c` module for comprehensive visibility validation
- Returns 1 only if all clues are satisfied

#### **Skip Filled Cells**
```c
if (grid->cells[row][col] != 0)
    return (ft_backtrack(grid, input, pos + 1));
```
- Some positions might be pre-filled (future optimization)
- Skip to next position without trying values
- Maintains algorithm generality

#### **Try All Possible Values**
```c
val = 1;
while (val <= SIZE)                      // Try values 1, 2, 3, 4
{
    if (ft_is_valid_placement(grid, row, col, val))
    {
        ft_place_value(grid, row, col, val);         // Make move
        if (ft_backtrack(grid, input, pos + 1))      // Recurse
            return (1);                              // Solution found!
        ft_remove_value(grid, row, col, val);        // Backtrack
    }
    val++;
}
return (0);                              // No valid value found
```

**Recursion Tree Example**:
```
pos=0, try val=1
├─ pos=1, try val=1 (invalid - same row)
├─ pos=1, try val=2
│  ├─ pos=2, try val=1 (invalid - same row)  
│  ├─ pos=2, try val=3
│  │  └─ ... continue recursion
│  └─ pos=2, try val=4
└─ pos=1, try val=3
   └─ ... explore this branch
```

**Performance Characteristics**:
- **Best case**: O(1) - lucky first guesses work
- **Average case**: Depends on constraint tightness and heuristics
- **Worst case**: O(4^16) - try every possibility
- **Practical performance**: Much better due to constraint propagation

---

### 5. `ft_solve_skyscraper`

```c
int ft_solve_skyscraper(t_input *input, t_grid *grid)
```

**Purpose**: Public interface function that initiates the solving process.

**Scope**: Public function (exported in header) - Main solver interface

**Parameters**:
- `t_input *input` - Parsed puzzle clues
- `t_grid *grid` - Empty grid to fill with solution

**Return Value**:
- `1` - Puzzle solved successfully
- `0` - No solution exists (unsolvable puzzle)

**Algorithm**:
```c
return (ft_backtrack(grid, input, 0));
```

**Interface Role**:
- **Abstraction layer**: Hides backtracking implementation details
- **Clean API**: Simple success/failure interface for callers
- **Starting point**: Begins search from position 0 (top-left corner)
- **State management**: Assumes grid is properly initialized

**Usage Pattern**:
```c
// In main.c
t_grid grid;
t_input input;
ft_init_grid(&grid);                     // Clean slate
if (ft_solve_skyscraper(&input, &grid))  // Attempt solve
{
    ft_print_grid(&grid);                // Success: print solution
}
else
{
    write(1, "Error\n", 6);              // Failure: no solution
}
```

---

## Constraint Satisfaction Theory

### Problem Classification
The 4x4 skyscraper puzzle is a **Constraint Satisfaction Problem (CSP)** with:

#### **Variables**: X = {x₀₀, x₀₁, ..., x₃₃}
- 16 grid positions that need values

#### **Domain**: D = {1, 2, 3, 4}  
- Each position can have any of 4 height values

#### **Constraints**: C = {Row, Column, Visibility}
1. **Row constraints**: Each row contains {1,2,3,4} exactly once
2. **Column constraints**: Each column contains {1,2,3,4} exactly once  
3. **Visibility constraints**: Clues around edges must be satisfied

### Search Space Analysis

#### **Total Combinations**
- **Without constraints**: 4^16 = 4,294,967,296 possibilities
- **With row/column constraints**: 4! × 4! = 576 Latin squares
- **With visibility constraints**: Much smaller (often 1 unique solution)

#### **Constraint Propagation Benefits**
- **Early pruning**: Eliminate branches that violate row/column uniqueness
- **Reduced search**: Only explore valid partial solutions
- **Performance gain**: Orders of magnitude faster than brute force

---

## Algorithm Complexity Analysis

### Time Complexity

#### **Best Case**: O(1)
- Solution found immediately with first guesses
- Rare but possible for simple puzzles

#### **Average Case**: O(n^k) where n=4, k≪16
- Depends on constraint tightness and puzzle difficulty
- Visibility constraints significantly prune search space
- Typical performance much better than worst case

#### **Worst Case**: O(4^16)
- Must explore entire search tree
- Only for extremely constrained or unsolvable puzzles
- Mitigated by constraint propagation and early termination

### Space Complexity

#### **Recursion Stack**: O(d) where d≤16
- Maximum recursion depth is 16 (number of positions)
- Each stack frame uses constant space
- Total stack space ≈ 16 × 32 bytes = 512 bytes

#### **Grid Storage**: O(1)
- Fixed 4×4 grid with bitmasks
- Total space ≈ 80 bytes (constant)

#### **Overall**: O(1) space - very memory efficient

### Performance Optimizations

#### **Bitmask Operations**
- **Constraint checking**: O(1) instead of O(n) array scanning
- **State updates**: O(1) bitwise operations
- **Memory efficiency**: Compact constraint representation

#### **Early Termination**
- **Invalid placements**: Return immediately without recursion
- **Complete validation**: Only when all positions filled
- **Pruning**: Eliminate invalid branches early

#### **Linear Position Traversal**
- **Cache-friendly**: Sequential memory access pattern
- **Simple arithmetic**: Fast row/column calculation
- **Predictable**: No complex position selection heuristics

---

## Integration with Project Modules

### Module Dependencies
```
solver.c depends on:
├── rush.h (t_grid, t_input, SIZE definitions)
├── check.c (ft_check_visibility for complete validation)
└── No direct I/O dependencies
```

### Data Flow
```
main.c → ft_solve_skyscraper() → ft_backtrack() → ft_check_visibility()
         ↑                        ↓
      Success/Fail            Constraint validation
```

### Interface Contracts

#### **Input Contract**:
- `grid` must be properly initialized (all cells = 0, bitmasks = 0)
- `input` must contain 16 validated clues (range 1-4)

#### **Output Contract**:
- Returns 1: `grid` contains valid complete solution
- Returns 0: `grid` state undefined (caller should not use)

#### **Side Effects**:
- Modifies grid during search (but restores on failure)
- No global state modifications
- No I/O operations

---

## Debugging and Analysis Tools

### State Inspection
```c
// Add debugging function for development:
void debug_print_state(t_grid *grid, int pos)
{
    printf("Position %d (row %d, col %d):\n", pos, pos/SIZE, pos%SIZE);
    printf("Row %d used: %04b\n", pos/SIZE, grid->row_used[pos/SIZE]);
    printf("Col %d used: %04b\n", pos%SIZE, grid->col_used[pos%SIZE]);
    // Print partial grid state...
}
```

### Performance Profiling
```c
// Add counters for analysis:
static int placement_attempts = 0;
static int backtrack_calls = 0;
static int constraint_checks = 0;

// Track algorithm efficiency and optimization opportunities
```

### Solution Verification
```c
// Independent verification function:
int verify_solution(t_grid *grid)
{
    // Check all rows have 1,2,3,4
    // Check all columns have 1,2,3,4  
    // Verify against original clues
    return (all_constraints_satisfied);
}
```

---

## Testing and Validation

### Unit Testing Strategy

#### **Constraint Functions**
```c
// Test constraint checking
t_grid test_grid = {0};
test_grid.row_used[0] = 0x05;  // Values 1,3 used in row 0
assert(ft_is_valid_placement(&test_grid, 0, 0, 2) == 1);  // Value 2 OK
assert(ft_is_valid_placement(&test_grid, 0, 0, 1) == 0);  // Value 1 blocked

// Test placement/removal  
ft_place_value(&test_grid, 0, 0, 2);
assert(test_grid.cells[0][0] == 2);
assert(test_grid.row_used[0] == 0x07);  // Now 1,2,3 used
ft_remove_value(&test_grid, 0, 0, 2);  
assert(test_grid.cells[0][0] == 0);
assert(test_grid.row_used[0] == 0x05);  // Back to 1,3 used
```

#### **Algorithm Testing**
```c
// Test with known solvable puzzle
t_input known_input = {{4,3,2,1,1,2,2,2,4,3,2,1,1,2,2,2}};
t_grid test_grid;
ft_init_grid(&test_grid);
assert(ft_solve_skyscraper(&known_input, &test_grid) == 1);

// Test with impossible puzzle  
t_input impossible = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
ft_init_grid(&test_grid);
assert(ft_solve_skyscraper(&impossible, &test_grid) == 0);
```

### Performance Testing
```bash
# Benchmark with various puzzle difficulties
time ./rush-01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"  # Easy
time ./rush-01 "2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2"  # Hard  
time ./rush-01 "1 1 1 1 4 4 4 4 1 1 1 1 4 4 4 4"  # Impossible
```

### Correctness Verification
```c
// Verify solution satisfies all constraints
int verify_complete_solution(t_grid *grid, t_input *input)
{
    // Check row uniqueness
    for (int row = 0; row < SIZE; row++)
        if (!check_row_unique(grid->cells[row])) return 0;
    
    // Check column uniqueness  
    for (int col = 0; col < SIZE; col++)
        if (!check_column_unique(grid, col)) return 0;
        
    // Check visibility constraints
    return ft_check_visibility(grid, input);
}
```

---

## 42 Norm Compliance

### Function Standards
✅ **Function count**: 5 functions (exactly at limit after refactoring)  
✅ **Function length**: All functions ≤ 25 lines  
✅ **Function naming**: All use `ft_` prefix convention  
✅ **Static scope**: Internal functions properly scoped  
✅ **Parameter clarity**: Clear, descriptive parameter names

### Algorithm Quality
✅ **Single responsibility**: Each function has one clear algorithmic task  
✅ **Clean interfaces**: Well-defined input/output contracts  
✅ **State management**: Proper state modification and restoration  
✅ **Error handling**: Clean failure modes with boolean returns  
✅ **No side effects**: Functions don't modify unexpected state

### Code Style
✅ **Indentation**: Proper tab indentation throughout  
✅ **Braces**: K&R brace style consistently applied  
✅ **Variable naming**: Clear, mathematical variable names  
✅ **Logic clarity**: Algorithm flow is easy to follow  
✅ **No excessive comments**: Code is self-documenting

---

## Advanced Topics and Extensions

### Algorithm Improvements

#### **Heuristics for Variable Ordering**
- **Most Constrained Variable**: Choose position with fewest valid values
- **Degree Heuristic**: Choose position affecting most constraints
- **Current**: Simple left-to-right, top-to-bottom ordering

#### **Value Ordering Heuristics**  
- **Least Constraining Value**: Choose value that eliminates fewest options for other positions
- **Current**: Try values 1,2,3,4 in order

#### **Constraint Propagation**
- **Arc Consistency**: Eliminate values that can't lead to valid solutions
- **Forward Checking**: Check constraints on unassigned variables
- **Current**: Basic constraint checking at placement time

### Scalability Considerations

#### **Generalization to N×N**
```c
// Current: Optimized for 4×4
#define SIZE 4
// Extension: Parameterized size
int solve_nxn_skyscraper(int n, t_input *input, t_grid *grid);
```

#### **Multiple Solutions**
```c
// Current: Find first solution
// Extension: Find all solutions
int find_all_solutions(t_input *input, t_grid solutions[], int max_solutions);
```

### Performance Optimization

#### **Iterative Deepening**
- Try solutions with fewer backtracks first
- Gradually increase search depth
- Better for finding solutions quickly

#### **Parallel Search**  
- Distribute different value choices across threads
- Shared state requires synchronization
- Potential for significant speedup

This documentation provides complete understanding of the constraint satisfaction algorithm that forms the mathematical and computational core of the skyscraper puzzle solver, demonstrating how theoretical computer science concepts translate into practical, efficient code.