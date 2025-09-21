# Check.c Documentation

## Overview

The `check.c` file contains the visibility validation functions that verify whether a completed or partial grid solution satisfies the skyscraper puzzle clues. These functions implement the core logic for determining if buildings are visible from different directions according to the puzzle rules.

## File Purpose

This module is responsible for:
- **Row visibility validation** - checking left and right clues
- **Column visibility validation** - checking top and bottom clues  
- **Complete grid validation** - verifying all clues are satisfied
- **Solution verification** - confirming a solved puzzle is correct

## Skyscraper Visibility Rules

### Basic Concept
In a skyscraper puzzle, numbers 1-4 represent building heights. The visibility clues around the grid indicate how many buildings can be "seen" from that direction.

### Visibility Logic
- A taller building **blocks** shorter buildings behind it
- You can only see buildings that are **taller** than all buildings in front of them
- Buildings of the same height or shorter are **hidden**

### Example
```
Row: [1, 3, 4, 2]
From left → right: See 1, then 3 (blocks 1), then 4 (blocks 1,3) = 3 visible
From right ← left: See 2, then 4 (blocks 2) = 2 visible
```

---

## Function Documentation

### 1. `ft_check_row_visibility`

```c
static int ft_check_row_visibility(t_grid *grid, int row, t_input *input)
```

**Purpose**: Validates visibility clues for a single row (left and right directions).

**Parameters**:
- `t_grid *grid` - The current grid state
- `int row` - Row index (0-3) to check
- `t_input *input` - Contains the clues array

**Algorithm**:
1. **Extract clues**:
   - Left clue: `input->clues[8 + row]` (clues 8-11)
   - Right clue: `input->clues[12 + row]` (clues 12-15)

2. **Count visible buildings**:
   - From left: Use `ft_count_visible_left(grid->cells[row])`
   - From right: Use `ft_count_visible_right(grid->cells[row])`

3. **Validate**:
   - Return `0` if either direction doesn't match its clue
   - Return `1` if both directions match their clues

**Clue Mapping**:
```
Clues array indices for rows:
Row 0: left=clue[8],  right=clue[12]
Row 1: left=clue[9],  right=clue[13]  
Row 2: left=clue[10], right=clue[14]
Row 3: left=clue[11], right=clue[15]
```

**Example**:
```c
// Grid row: [4, 3, 2, 1]
// Left clue = 4, Right clue = 1
// Left visibility: 4 buildings visible (4, then nothing higher)
// Right visibility: 1 building visible (only 4 is higher than 1,2,3)
// Result: Both match, return 1
```

---

### 2. `ft_check_col_visibility`

```c
static int ft_check_col_visibility(t_grid *grid, int col, t_input *input)
```

**Purpose**: Validates visibility clues for a single column (top and bottom directions).

**Parameters**:
- `t_grid *grid` - The current grid state  
- `int col` - Column index (0-3) to check
- `t_input *input` - Contains the clues array

**Algorithm**:
1. **Extract clues**:
   - Top clue: `input->clues[col]` (clues 0-3)
   - Bottom clue: `input->clues[4 + col]` (clues 4-7)

2. **Count visible buildings**:
   - From top: Use `ft_count_visible_top(grid, col)`
   - From bottom: Use `ft_count_visible_bottom(grid, col)`

3. **Validate**:
   - Return `0` if either direction doesn't match its clue
   - Return `1` if both directions match their clues

**Clue Mapping**:
```
Clues array indices for columns:
Col 0: top=clue[0], bottom=clue[4]
Col 1: top=clue[1], bottom=clue[5]
Col 2: top=clue[2], bottom=clue[6]  
Col 3: top=clue[3], bottom=clue[7]
```

**Example**:
```c
// Grid column: [1, 2, 3, 4] (top to bottom)
// Top clue = 4, Bottom clue = 1
// Top visibility: 4 buildings visible (each is taller than previous)
// Bottom visibility: 1 building visible (only 4 is visible)
// Result: Both match, return 1
```

---

### 3. `ft_check_visibility`

```c
int ft_check_visibility(t_grid *grid, t_input *input)
```

**Purpose**: Validates the entire grid against all 16 visibility clues.

**Parameters**:
- `t_grid *grid` - The complete grid to validate
- `t_input *input` - Contains all 16 clues

**Algorithm**:
1. **Iterate through all positions** (0-3):
   - Check row `i` using `ft_check_row_visibility`
   - Check column `i` using `ft_check_col_visibility`

2. **Early termination**:
   - Return `0` immediately if any row or column fails
   - Continue only if all checks pass

3. **Complete validation**:
   - Return `1` only if all 4 rows AND all 4 columns pass

**Usage Context**:
This function is called:
- When the backtracking algorithm fills all 16 cells
- To verify a complete solution before output
- As the final validation step in the solver

**Logic Flow**:
```
For i = 0 to 3:
  ├─ Check row i visibility (left + right clues)
  │  └─ If failed: return 0
  └─ Check col i visibility (top + bottom clues)
     └─ If failed: return 0
Return 1 (all passed)
```

---

## Integration with Solver

### Call Hierarchy
```
ft_solve_skyscraper()
└── ft_backtrack()
    └── ft_check_visibility() ← Called when pos == 16 (grid full)
        ├── ft_check_row_visibility() ← For each row
        └── ft_check_col_visibility() ← For each column
```

### Dependency Functions
The check functions rely on visibility counting from `vis.c`:
- `ft_count_visible_left(int *row)` - Count from left side of row
- `ft_count_visible_right(int *row)` - Count from right side of row  
- `ft_count_visible_top(t_grid *grid, int col)` - Count from top of column
- `ft_count_visible_bottom(t_grid *grid, int col)` - Count from bottom of column

---

## Clue Array Structure

The 16 clues in `input->clues[]` are organized as:
```
Index  | Direction | Position
-------|-----------|----------
0-3    | Top       | Columns 0,1,2,3
4-7    | Bottom    | Columns 0,1,2,3  
8-11   | Left      | Rows 0,1,2,3
12-15  | Right     | Rows 0,1,2,3
```

**Visual Representation**:
```
       0   1   2   3     ← Top clues (indices 0-3)
       ↓   ↓   ↓   ↓
    8→ [·] [·] [·] [·] ←12
    9→ [·] [·] [·] [·] ←13  
   10→ [·] [·] [·] [·] ←14
   11→ [·] [·] [·] [·] ←15
       ↑   ↑   ↑   ↑
       4   5   6   7     ← Bottom clues (indices 4-7)
```

---

## Error Handling

### Return Values
- **Return 0**: Visibility constraint violated
- **Return 1**: All visibility constraints satisfied

### Validation Points
1. **Row validation**: Both left and right clues must match
2. **Column validation**: Both top and bottom clues must match  
3. **Complete validation**: All 4 rows AND all 4 columns must pass

### Failure Cases
- Calculated visibility ≠ expected clue value
- Any single direction mismatch fails the entire check
- Used for backtracking: invalid placements are rejected

---

## Performance Considerations

### Time Complexity
- **Per row check**: O(4) - scan 4 cells twice (left + right)
- **Per column check**: O(4) - scan 4 cells twice (top + bottom)  
- **Complete check**: O(16) - 4 rows × O(4) + 4 columns × O(4)

### Space Complexity
- **O(1)** - Only uses local variables for indices and clue values
- No additional data structures or recursion

### Optimization
- **Early termination**: Returns immediately on first constraint violation
- **Static functions**: Row/column checks are internal helpers
- **Direct array access**: No complex pointer arithmetic

---

## Testing Examples

### Valid Case
```c
Grid: [4,3,2,1]  Clues: left=4, right=1
      [3,4,1,2]         left=2, right=2  
      [2,1,4,3]         left=2, right=2
      [1,2,3,4]         left=4, right=1

Result: All visibility checks pass → return 1
```

### Invalid Case  
```c
Grid: [1,2,3,4]  Clues: left=4, right=1
      [2,3,4,1]         left=3, right=2
      [3,4,1,2]         left=2, right=2  
      [4,1,2,3]         left=1, right=2

Row 0: left_visible=4, left_clue=4 ✓, right_visible=1, right_clue=1 ✓
Row 1: left_visible=3, left_clue=3 ✓, right_visible=2, right_clue=2 ✓
But column checks might fail...
Result: If any check fails → return 0
```

---

## 42 Norm Compliance

### Function Standards
✅ **Function length**: All functions ≤ 25 lines  
✅ **Function naming**: All use `ft_` prefix  
✅ **Static functions**: Helper functions properly scoped  
✅ **Variable naming**: Clear, descriptive names  
✅ **Return consistency**: Always 0 (fail) or 1 (success)  

### Code Quality
✅ **Single responsibility**: Each function has one clear purpose  
✅ **Clear logic flow**: Easy to follow validation steps  
✅ **No side effects**: Pure validation functions  
✅ **Consistent style**: Matches project conventions  

This documentation provides complete understanding of the visibility validation logic that ensures skyscraper puzzle solutions are mathematically correct and satisfy all given clues.