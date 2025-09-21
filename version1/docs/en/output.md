# Output.c Documentation

## Overview

The `output.c` file contains the grid display functionality for the 4x4 skyscraper puzzle solver. This module is responsible for formatting and printing the solved puzzle grid to the standard output in the correct format required by 42 school standards.

## File Purpose

This module handles:
- **Grid formatting** - Converting numeric grid to readable output
- **Standard output** - Using only allowed functions (`write`)
- **Spacing control** - Proper formatting with spaces between numbers
- **Line management** - Correct newline placement for grid rows
- **42 compliance** - Following strict output requirements

## Design Philosophy

### Separation of Concerns
- **Single responsibility**: Only handles output formatting
- **No computation**: Pure display function with no logic
- **Clean interface**: Simple function signature
- **Minimal dependencies**: Only uses basic utility functions

### 42 School Requirements
- **Allowed functions only**: Uses `write` through utility wrappers
- **No printf/scanf**: Custom number printing implementation
- **Exact format**: Matches expected output specification
- **Error handling**: Clean output for valid solutions only

---

## Function Documentation

### `ft_print_grid`

```c
void ft_print_grid(t_grid *grid)
```

**Purpose**: Prints a completed 4x4 skyscraper puzzle solution to standard output.

**Parameters**:
- `t_grid *grid` - Pointer to the solved grid structure containing the 4x4 solution

**Return Value**:
- `void` - No return value (pure output function)

**Preconditions**:
- Grid must be completely filled (no zeros)
- Grid must contain valid numbers (1-4)
- Grid must be a valid solution (caller's responsibility)

**Postconditions**:
- Grid is printed to stdout
- Output follows exact format specification
- Cursor is positioned at start of next line after output

---

## Algorithm Analysis

### Step-by-Step Logic

#### 1. **Outer Loop - Row Iteration**
```c
i = 0;
while (i < SIZE)  // SIZE = 4
```
- **Purpose**: Iterate through each row of the 4x4 grid
- **Range**: i = 0, 1, 2, 3 (representing rows top to bottom)
- **Control**: Uses while loop for 42 norm compliance

#### 2. **Inner Loop - Column Iteration**  
```c
j = 0;
while (j < SIZE)  // SIZE = 4
```
- **Purpose**: Process each cell within the current row
- **Range**: j = 0, 1, 2, 3 (representing columns left to right)
- **Nested structure**: Executed 4 times per row iteration

#### 3. **Number Output**
```c
ft_putnbr(grid->cells[i][j]);
```
- **Function call**: Uses utility function for number printing
- **Data access**: `grid->cells[i][j]` retrieves cell value
- **Valid range**: Numbers 1-4 (puzzle constraints)
- **Implementation**: Recursive digit-by-digit output using `write()`

#### 4. **Spacing Logic**
```c
if (j < SIZE - 1)
    ft_putchar(' ');
```
- **Condition**: Add space after numbers, except last in row
- **Logic**: `j < 3` means positions 0,1,2 get spaces, position 3 doesn't
- **Result**: "1 2 3 4" format (space-separated, no trailing space)

#### 5. **Line Termination**
```c
ft_putchar('\n');
i++;
```
- **Newline**: End each row with newline character
- **Row advance**: Move to next row for outer loop
- **Output result**: Each row on separate line

### Visual Flow Diagram
```
Start
  ↓
i = 0 (Row 0) ──────┐
  ↓                │
j = 0,1,2,3        │ Repeat for
Print: "1 2 3 4\n"  │ i = 1,2,3
  ↓                │
i = 1 (Row 1) ──────┘
  ↓
...continue...
  ↓
End (4 rows printed)
```

---

## Output Format Specification

### Expected Output Format
```
1 2 3 4
4 1 2 3
3 4 1 2
2 3 4 1
```

### Format Requirements
- **Numbers**: Single digits 1-4 only
- **Separators**: Single space between numbers in same row
- **No trailing spaces**: Last number in row followed immediately by newline
- **Line endings**: Unix-style newlines (`\n`)
- **No extra lines**: Exactly 4 lines of output, no blank lines

### Character-by-Character Analysis
```
Position: 0123456789...
Output:   "1 2 3 4\n4 1 2 3\n3 4 1 2\n2 3 4 1\n"
          └─────┘ └─────┘ └─────┘ └─────┘
           Row 0   Row 1   Row 2   Row 3
```

---

## Integration with Project

### Call Hierarchy
```
main()
├── ft_solve_skyscraper() → Success
├── ft_print_grid() ← Called here
└── return 0
```

### Usage Context
- **When called**: Only after successful puzzle solution
- **Caller**: `main()` function after solver returns success
- **Precondition**: Grid contains valid, complete solution
- **Alternative**: On error/failure, "Error\n" is printed instead

### Dependency Functions
The function relies on utility functions from `utils.c`:
- `ft_putnbr(int n)` - Converts integer to character output
- `ft_putchar(char c)` - Outputs single character using `write()`

---

## Memory and Performance

### Memory Usage
- **Stack space**: O(1) - only local variables `i`, `j`
- **No allocation**: No malloc/free operations
- **Grid access**: Read-only access to existing grid structure
- **No copying**: Direct access to original data

### Time Complexity
- **O(n²)**: Where n=4, so O(16) constant time
- **Linear in output**: Proportional to characters printed
- **No optimization needed**: Already optimal for fixed 4x4 size

### Space Complexity
- **O(1)**: Constant space for loop variables
- **No recursion**: Iterative implementation only
- **No buffers**: Direct character-by-character output

---

## Error Handling and Edge Cases

### Input Validation
- **Assumes valid grid**: No null pointer checks (caller responsibility)
- **Assumes complete solution**: No zero-checking (solver guarantees)
- **Assumes correct values**: No range validation (solver constraints)

### Robust Design Choices
- **Simple loops**: while loops less prone to off-by-one errors
- **Clear conditions**: `j < SIZE - 1` is explicit and readable
- **No complex logic**: Minimal branching reduces bug potential

### Error Scenarios (Handled by Caller)
- **Invalid grid**: main() prints "Error\n" instead of calling this function
- **Unsolvable puzzle**: Solver fails, this function never called
- **Invalid input**: Parser fails, this function never called

---

## 42 Norm Compliance

### Function Standards
✅ **Function length**: 18 lines (well under 25-line limit)  
✅ **Function naming**: Uses `ft_` prefix convention  
✅ **Parameter naming**: Clear, descriptive parameter name  
✅ **Variable naming**: Simple, clear `i`, `j` for loop indices  
✅ **Single function**: Only one function in file (under 5-function limit)

### Code Style
✅ **Indentation**: Proper tab indentation  
✅ **Spacing**: Correct spacing around operators and keywords  
✅ **Braces**: K&R brace style  
✅ **Line length**: All lines under 80 characters  
✅ **No forbidden functions**: Only uses allowed `write` through wrappers

### Allowed Functions Usage
- **write()**: Used indirectly through `ft_putchar` and `ft_putnbr`
- **No printf**: Custom number printing implementation
- **No library functions**: Pure custom implementation
- **42 compliant**: Follows all school restrictions

---

## Testing and Validation

### Manual Testing
```c
// Example test grid
t_grid test_grid = {
    .cells = {
        {1, 2, 3, 4},
        {4, 1, 2, 3}, 
        {3, 4, 1, 2},
        {2, 3, 4, 1}
    }
};

ft_print_grid(&test_grid);
// Expected output:
// 1 2 3 4
// 4 1 2 3  
// 3 4 1 2
// 2 3 4 1
```

### Edge Case Testing
```c
// Minimum values (all 1s - invalid puzzle but tests output)
// Maximum values (all 4s - invalid puzzle but tests output)
// Mixed values (valid solutions)
```

### Output Verification
- **Character count**: Each row should be exactly 7 characters ("1 2 3 4")
- **Line count**: Exactly 4 lines of output
- **No extra whitespace**: No trailing spaces or extra newlines
- **Correct numbers**: All values in range 1-4

---

## Usage Examples

### Standard Usage
```c
if (ft_solve_skyscraper(&input, &grid))
{
    ft_print_grid(&grid);  // Print solution
    return (0);
}
else
{
    write(1, "Error\n", 6);  // Print error instead
    return (1);
}
```

### Integration Pattern
```c
// Complete main() flow
parse_input() → solve_puzzle() → ft_print_grid() → success
     ↓               ↓                             
   error          error       → write("Error\n") → failure
```

---

## Future Considerations

### Extensibility
- **Grid size**: Could be generalized for NxN grids
- **Output format**: Could support different formatting options
- **Error output**: Could be moved to this module for consistency

### Optimization
- **Current implementation**: Already optimal for 4x4 fixed size
- **No premature optimization**: Simple, clear code preferred
- **Performance adequate**: Output is not a bottleneck

### Maintenance
- **Single responsibility**: Easy to modify output format if needed
- **Clear separation**: Independent of solving logic
- **Testable**: Easy to unit test with known grid inputs

This documentation provides complete understanding of the output formatting logic and its role in delivering properly formatted skyscraper puzzle solutions according to 42 school requirements.