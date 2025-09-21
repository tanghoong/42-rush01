# Vis.c Documentation

## Overview

The `vis.c` file implements the visibility counting algorithms that form the mathematical foundation of the skyscraper puzzle. This module contains the core logic for determining how many "skyscrapers" are visible from each direction around the grid perimeter. These functions translate the puzzle's visual metaphor into precise mathematical calculations that validate whether a proposed solution satisfies all visibility clues.

## File Purpose

This module handles:
- **Visibility counting** - Mathematical calculation of visible skyscrapers from each direction
- **Line-of-sight simulation** - Modeling how taller buildings hide shorter ones
- **Directional traversal** - Scanning rows and columns from different starting points
- **Height comparison logic** - Determining when a building becomes visible
- **Constraint validation support** - Providing data for complete solution checking
- **Algorithm optimization** - Efficient single-pass visibility counting

## Skyscraper Puzzle Theory

### Visual Metaphor
Imagine a 4×4 grid where each cell contains a "skyscraper" of height 1, 2, 3, or 4. Standing outside the grid and looking across a row or column, you can only see skyscrapers that are taller than all the skyscrapers in front of them. The puzzle provides "clues" indicating how many skyscrapers are visible from each direction.

### Mathematical Model
- **Grid values**: Heights {1, 2, 3, 4}
- **Visibility rule**: A skyscraper at position i is visible if `height[i] > max(height[0..i-1])`
- **Clue validation**: Count of visible skyscrapers must match the given clue
- **Complete constraint**: All 16 clues (4 sides × 4 directions) must be satisfied

### Line-of-Sight Algorithm
```
visible_count = 0
max_height = 0
for each position in direction:
    if height[position] > max_height:
        max_height = height[position]
        visible_count++
return visible_count
```

---

## Algorithm Overview

### Visibility Counting Strategy
1. **Initialize tracking variables** - Start with no buildings seen (`visible = 0`, `max_height = 0`)
2. **Traverse in viewing direction** - Scan row/column from the perspective viewpoint
3. **Height comparison** - Check if current building is taller than previous tallest
4. **Update visibility** - If taller, it's visible and becomes new height threshold
5. **Continue scanning** - Repeat until entire row/column is processed
6. **Return count** - Total number of visible buildings from this direction

### Directional Scanning
- **Left→Right**: Scan row from column 0 to 3
- **Right→Left**: Scan row from column 3 to 0  
- **Top→Bottom**: Scan column from row 0 to 3
- **Bottom→Top**: Scan column from row 3 to 0

### Optimization Principles
- **Single pass**: O(n) time complexity per direction
- **Minimal state**: Only track maximum height and count
- **Early visibility**: Determine visibility immediately upon encountering taller building
- **No backtracking**: Linear scan is sufficient for visibility counting

---

## Function Documentation

### 1. `ft_count_visible_left`

```c
int ft_count_visible_left(int *row)
```

**Purpose**: Counts how many skyscrapers are visible when looking from the left side of a row (left to right scan).

**Parameters**:
- `int *row` - Array of 4 integers representing heights in a single row

**Return Value**:
- `int` - Number of visible skyscrapers (range: 1-4)

**Algorithm**:
```c
max_height = 0;                          // No buildings seen yet
visible = 0;                             // Count of visible buildings
i = 0;                                   // Start from leftmost position
while (i < SIZE)                         // Scan left to right
{
    if (row[i] > max_height)             // Current building is taller
    {
        max_height = row[i];             // Update height threshold
        visible++;                       // Increment visible count
    }
    i++;                                 // Move to next position
}
return (visible);
```

**Visual Example**:
```
Row: [2, 1, 4, 3]
Looking from left ←

Position 0: height=2, max=0 → 2>0 ✓ visible, max=2, count=1
Position 1: height=1, max=2 → 1≤2 ✗ hidden behind building at pos 0
Position 2: height=4, max=2 → 4>2 ✓ visible, max=4, count=2  
Position 3: height=3, max=4 → 3≤4 ✗ hidden behind building at pos 2

Result: 2 visible skyscrapers
```

**Visibility Logic**:
- **Building at pos 0**: Always visible (first building encountered)
- **Building at pos 1**: Hidden behind taller building at pos 0 (height 2)
- **Building at pos 2**: Visible because it's taller than previous maximum (4 > 2)
- **Building at pos 3**: Hidden behind building at pos 2 (height 4)

**Performance**: O(n) where n=4, single pass through row

---

### 2. `ft_count_visible_right`

```c
int ft_count_visible_right(int *row)
```

**Purpose**: Counts how many skyscrapers are visible when looking from the right side of a row (right to left scan).

**Parameters**:
- `int *row` - Array of 4 integers representing heights in a single row

**Return Value**:
- `int` - Number of visible skyscrapers (range: 1-4)

**Algorithm**:
```c
max_height = 0;                          // No buildings seen yet
visible = 0;                             // Count of visible buildings
i = SIZE - 1;                            // Start from rightmost position (3)
while (i >= 0)                           // Scan right to left
{
    if (row[i] > max_height)             // Current building is taller
    {
        max_height = row[i];             // Update height threshold
        visible++;                       // Increment visible count
    }
    i--;                                 // Move to previous position
}
return (visible);
```

**Visual Example**:
```
Row: [2, 1, 4, 3]
Looking from right →

Position 3: height=3, max=0 → 3>0 ✓ visible, max=3, count=1
Position 2: height=4, max=3 → 4>3 ✓ visible, max=4, count=2
Position 1: height=1, max=4 → 1≤4 ✗ hidden behind building at pos 2
Position 0: height=2, max=4 → 2≤4 ✗ hidden behind building at pos 2

Result: 2 visible skyscrapers
```

**Key Difference from Left View**:
- **Same row, different perspective**: Different buildings become visible
- **Scanning direction**: Processes positions in reverse order (3→2→1→0)
- **Independent calculation**: Right view count can differ from left view count
- **Same algorithm**: Identical visibility logic, just different traversal direction

**Symmetry Observation**: For row [2,1,4,3], both left and right views show 2 visible buildings, but this is coincidental.

---

### 3. `ft_count_visible_top`

```c
int ft_count_visible_top(t_grid *grid, int col)
```

**Purpose**: Counts how many skyscrapers are visible when looking from the top of a column (top to bottom scan).

**Parameters**:
- `t_grid *grid` - Complete grid structure containing all cell values
- `int col` - Column index to analyze (0-3)

**Return Value**:
- `int` - Number of visible skyscrapers (range: 1-4)

**Algorithm**:
```c
max_height = 0;                          // No buildings seen yet
visible = 0;                             // Count of visible buildings
i = 0;                                   // Start from top position (row 0)
while (i < SIZE)                         // Scan top to bottom
{
    if (grid->cells[i][col] > max_height)// Current building is taller
    {
        max_height = grid->cells[i][col]; // Update height threshold
        visible++;                        // Increment visible count
    }
    i++;                                  // Move to next row
}
return (visible);
```

**Column Access Pattern**:
```c
grid->cells[0][col]    // Top of column (row 0)
grid->cells[1][col]    // Second from top (row 1)
grid->cells[2][col]    // Second from bottom (row 2)  
grid->cells[3][col]    // Bottom of column (row 3)
```

**Visual Example**:
```
Column 1: [3, 2, 4, 1] (extracted from grid->cells[i][1])
Looking from top ↓

Row 0: height=3, max=0 → 3>0 ✓ visible, max=3, count=1
Row 1: height=2, max=3 → 2≤3 ✗ hidden behind building at row 0
Row 2: height=4, max=3 → 4>3 ✓ visible, max=4, count=2
Row 3: height=1, max=4 → 1≤4 ✗ hidden behind building at row 2

Result: 2 visible skyscrapers
```

**Data Structure Access**:
- **Grid navigation**: Accesses `grid->cells[i][col]` to read column values
- **Column-wise traversal**: Fixes column index, iterates through row indices
- **Memory pattern**: Accesses different memory locations (not sequential like row functions)
- **Cache considerations**: Column access has different cache behavior than row access

---

### 4. `ft_count_visible_bottom`

```c
int ft_count_visible_bottom(t_grid *grid, int col)
```

**Purpose**: Counts how many skyscrapers are visible when looking from the bottom of a column (bottom to top scan).

**Parameters**:
- `t_grid *grid` - Complete grid structure containing all cell values
- `int col` - Column index to analyze (0-3)

**Return Value**:
- `int` - Number of visible skyscrapers (range: 1-4)

**Algorithm**:
```c
max_height = 0;                          // No buildings seen yet
visible = 0;                             // Count of visible buildings
i = SIZE - 1;                            // Start from bottom position (row 3)
while (i >= 0)                           // Scan bottom to top
{
    if (grid->cells[i][col] > max_height)// Current building is taller
    {
        max_height = grid->cells[i][col]; // Update height threshold
        visible++;                        // Increment visible count
    }
    i--;                                  // Move to previous row
}
return (visible);
```

**Reverse Column Access Pattern**:
```c
grid->cells[3][col]    // Bottom of column (row 3) - start here
grid->cells[2][col]    // Second from bottom (row 2)
grid->cells[1][col]    // Second from top (row 1)
grid->cells[0][col]    // Top of column (row 0) - end here
```

**Visual Example**:
```
Column 1: [3, 2, 4, 1] (extracted from grid->cells[i][1])
Looking from bottom ↑

Row 3: height=1, max=0 → 1>0 ✓ visible, max=1, count=1
Row 2: height=4, max=1 → 4>1 ✓ visible, max=4, count=2
Row 1: height=2, max=4 → 2≤4 ✗ hidden behind building at row 2
Row 0: height=3, max=4 → 3≤4 ✗ hidden behind building at row 2

Result: 2 visible skyscrapers
```

**Scanning Direction Impact**:
- **Different visibility**: Same column data yields different visible counts from top vs. bottom
- **Bottom-up perspective**: Building at row 3 (height 1) is visible first
- **Height threshold evolution**: `max_height` progresses differently (1→4 vs. 3→4)
- **Independent result**: Bottom view count independent of top view count

---

## Mathematical Analysis

### Visibility Function Properties

#### **Monotonicity**
The visibility counting algorithm exhibits monotonic behavior:
- **Height threshold**: `max_height` never decreases during scan
- **Visibility count**: `visible` never decreases during scan
- **Deterministic**: Same input always produces same output

#### **Boundary Conditions**

##### **Minimum Visibility: 1**
```c
// Any non-empty row/column has at least 1 visible building
// The tallest building in the direction is always visible
```

##### **Maximum Visibility: 4**
```c
// Perfect ascending sequence: [1, 2, 3, 4]
// Every building is taller than all previous ones
```

### Complexity Analysis

#### **Time Complexity**: O(n) where n = SIZE = 4
- **Single pass**: Each function scans exactly 4 positions once
- **Constant operations**: Height comparison and counter increment are O(1)
- **Linear scaling**: Would scale linearly for larger grid sizes

#### **Space Complexity**: O(1)
- **Fixed variables**: `max_height`, `visible`, `i` use constant space
- **No additional storage**: Algorithm doesn't store intermediate results
- **In-place computation**: Works directly with input data

### Pattern Recognition

#### **Optimal Visibility Patterns**

##### **Maximum visibility (4 visible)**:
```
[1, 2, 3, 4] → All buildings visible (ascending order)
```

##### **Minimum visibility (1 visible)**:
```
[4, 3, 2, 1] → Only first building visible (descending order)
```

##### **Common patterns**:
```
[4, 1, 2, 3] → 2 visible (4 at start, then all hidden)
[1, 4, 2, 3] → 2 visible (1, then 4, then all hidden)
[2, 3, 1, 4] → 3 visible (2, then 3, then 4 breaks through)
```

---

## Integration with Puzzle Solving

### Usage in Validation Process

#### **Complete Grid Validation**
```c
// In check.c: ft_check_visibility()
for (int row = 0; row < SIZE; row++)
{
    if (input->clues[LEFT][row] != 0)
        if (ft_count_visible_left(grid->cells[row]) != input->clues[LEFT][row])
            return (0);  // Left clue violated
            
    if (input->clues[RIGHT][row] != 0)
        if (ft_count_visible_right(grid->cells[row]) != input->clues[RIGHT][row])
            return (0);  // Right clue violated
}

for (int col = 0; col < SIZE; col++)
{
    if (input->clues[TOP][col] != 0)
        if (ft_count_visible_top(grid, col) != input->clues[TOP][col])
            return (0);  // Top clue violated
            
    if (input->clues[BOTTOM][col] != 0)
        if (ft_count_visible_bottom(grid, col) != input->clues[BOTTOM][col])
            return (0);  // Bottom clue violated
}
```

### Performance in Solving Context

#### **Validation Frequency**
- **Called once per complete solution**: Only when backtracking fills all 16 positions
- **16 visibility calculations**: 4 directions × 4 rows/columns = 16 function calls
- **Total operations**: 16 × 4 = 64 height comparisons per validation
- **Validation cost**: O(64) = O(1) for 4×4 grid

#### **Critical Path Analysis**
```
Backtracking → Complete grid → ft_check_visibility() → vis.c functions → Success/Failure
```

The visibility counting functions represent the final validation step that determines whether a complete grid assignment satisfies all puzzle constraints.

---

## Directional Mapping and Clue Integration

### Clue Position Mapping

#### **Input Clue Layout**:
```
    T0  T1  T2  T3     ← Top clues
L0  [1] [2] [3] [4] R0  ← Left/Right clues for row 0
L1  [1] [2] [3] [4] R1  ← Left/Right clues for row 1  
L2  [1] [2] [3] [4] R2  ← Left/Right clues for row 2
L3  [1] [2] [3] [4] R3  ← Left/Right clues for row 3
    B0  B1  B2  B3     ← Bottom clues
```

#### **Function to Clue Mapping**:
```c
// Row-based clues
input->clues[0] → ft_count_visible_top(grid, 0)     // T0
input->clues[4] → ft_count_visible_left(grid->cells[0])  // L0  
input->clues[8] → ft_count_visible_bottom(grid, 0)  // B0
input->clues[12] → ft_count_visible_right(grid->cells[0]) // R0
```

### Validation Logic Flow

#### **Clue Validation Process**:
1. **Parse clue**: Extract expected visibility count from input
2. **Calculate actual**: Use appropriate vis.c function to count visibility  
3. **Compare values**: Check if calculated matches expected
4. **Return result**: Success (match) or failure (mismatch)

#### **Selective Validation**:
```c
if (input->clues[position] != 0)  // 0 = no clue provided
{
    int calculated = ft_count_visible_xxx(...);
    if (calculated != input->clues[position])
        return (0);  // Constraint violation
}
```

---

## Algorithm Variations and Extensions

### Optimization Opportunities

#### **Early Termination**
```c
// If we've seen height 4, all remaining buildings are hidden
if (max_height == 4)
    break;  // No more buildings can be visible
```

#### **Clue-Based Pruning**
```c
// If clue is 1, only first building matters
if (expected_clue == 1 && visible > 1)
    return (0);  // Already too many visible
```

#### **Height 4 Special Case**
```c
// Height 4 building always creates visibility break
if (current_height == 4)
{
    visible++;
    break;  // Nothing beyond height 4 is visible
}
```

### Generalization to N×N Grids

#### **Scalable Implementation**:
```c
int ft_count_visible_left_generic(int *row, int size)
{
    int max_height = 0;
    int visible = 0;
    
    for (int i = 0; i < size; i++)
    {
        if (row[i] > max_height)
        {
            max_height = row[i];
            visible++;
        }
    }
    return (visible);
}
```

#### **Performance Scaling**:
- **Time complexity**: O(n) for n×n grid
- **Space complexity**: Remains O(1)
- **Total validation**: O(n²) for complete grid check

---

## Testing and Verification

### Unit Testing Strategy

#### **Known Visibility Patterns**:
```c
// Test maximum visibility
int ascending[4] = {1, 2, 3, 4};
assert(ft_count_visible_left(ascending) == 4);
assert(ft_count_visible_right(ascending) == 1);  // Only 4 visible from right

// Test minimum visibility  
int descending[4] = {4, 3, 2, 1};
assert(ft_count_visible_left(descending) == 1);  // Only 4 visible from left
assert(ft_count_visible_right(descending) == 4);

// Test mixed patterns
int mixed[4] = {2, 1, 4, 3};
assert(ft_count_visible_left(mixed) == 2);   // 2, then 4
assert(ft_count_visible_right(mixed) == 2);  // 3, then 4
```

#### **Column Testing**:
```c
// Create test grid
t_grid test_grid;
// Set column values: test_grid.cells[i][0] = heights[i]
int column_heights[4] = {3, 1, 4, 2};
for (int i = 0; i < 4; i++)
    test_grid.cells[i][0] = column_heights[i];

assert(ft_count_visible_top(&test_grid, 0) == 2);     // 3, then 4
assert(ft_count_visible_bottom(&test_grid, 0) == 2);  // 2, then 4
```

### Edge Case Validation

#### **All Same Height** (Invalid in real puzzle):
```c
int same[4] = {2, 2, 2, 2};
// Result: 1 visible (first building only)
// Note: This violates skyscraper uniqueness constraint
```

#### **Height 4 Dominance**:
```c
int height4_first[4] = {4, 1, 2, 3};
assert(ft_count_visible_left(height4_first) == 1);   // Only 4 visible
int height4_last[4] = {1, 2, 3, 4};  
assert(ft_count_visible_left(height4_last) == 4);    // All visible
```

### Correctness Verification

#### **Symmetry Checks**:
```c
// Create symmetric test cases
void test_symmetry(int heights[4])
{
    // Test left-right consistency with reversed array
    int reversed[4];
    for (int i = 0; i < 4; i++)
        reversed[i] = heights[3-i];
        
    int left_count = ft_count_visible_left(heights);
    int right_reversed = ft_count_visible_right(reversed);
    assert(left_count == right_reversed);  // Should be equal
}
```

#### **Grid Consistency**:
```c
// Verify row/column extraction matches direct array access
void test_grid_consistency(t_grid *grid)
{
    for (int row = 0; row < SIZE; row++)
    {
        int left = ft_count_visible_left(grid->cells[row]);
        // Manually extract row and test
        int extracted_row[4];
        for (int col = 0; col < SIZE; col++)
            extracted_row[col] = grid->cells[row][col];
        int left_extracted = ft_count_visible_left(extracted_row);
        assert(left == left_extracted);
    }
}
```

---

## Performance Benchmarking

### Execution Time Analysis

#### **Individual Function Performance**:
```bash
# Benchmark visibility counting functions
time_test() {
    for i in {1..1000000}; do
        ft_count_visible_left(test_row);
    done
}

# Expected: ~1-2 milliseconds for 1M iterations
# Indicates excellent O(1) performance for 4×4 case
```

#### **Complete Validation Performance**:
```bash  
# Benchmark complete grid validation
validate_grid_test() {
    # 16 visibility calculations per validation
    # 4 directions × 4 rows/columns = 16 calls
    for i in {1..100000}; do
        ft_check_visibility(test_grid, test_input);
    done
}

# Expected: ~10-20 milliseconds for 100K validations
# Indicates efficient integration with solving algorithm
```

### Memory Usage Analysis

#### **Function Memory Footprint**:
```c
// Each visibility function uses:
int max_height;    // 4 bytes
int visible;       // 4 bytes  
int i;            // 4 bytes
// Total: 12 bytes per function call
// Stack overhead: ~32 bytes
// Total per call: ~44 bytes
```

#### **Cache Performance**:
- **Row functions**: Excellent cache locality (sequential access)
- **Column functions**: Moderate cache performance (strided access)
- **Overall impact**: Minimal for 4×4 grid, more significant for larger grids

---

## 42 Norm Compliance

### Function Standards
✅ **Function count**: 4 functions (under 5-function limit)  
✅ **Function length**: All functions ≤ 25 lines  
✅ **Function naming**: All use `ft_` prefix with descriptive names  
✅ **Parameter clarity**: Clear parameter names (`row`, `grid`, `col`)  
✅ **Return values**: Consistent integer return type

### Algorithm Quality
✅ **Single responsibility**: Each function handles one directional view  
✅ **Code reuse**: Consistent algorithm pattern across functions  
✅ **Clear logic**: Visibility algorithm is easy to follow  
✅ **No side effects**: Functions don't modify input data  
✅ **Deterministic**: Same input always produces same output

### Code Style
✅ **Indentation**: Proper tab indentation throughout  
✅ **Variable naming**: Clear, mathematical variable names  
✅ **Loop structure**: Consistent while loop pattern  
✅ **Braces**: K&R brace style consistently applied  
✅ **Logic flow**: Clear algorithmic progression

---

## Integration Summary

The `vis.c` module provides the mathematical foundation for validating skyscraper puzzle solutions. Its four functions translate the visual metaphor of "counting visible skyscrapers" into precise algorithms that determine constraint satisfaction. The module's efficient O(n) visibility counting enables the backtracking solver to validate complete solutions quickly, making it a critical component in the overall puzzle-solving architecture.

These visibility functions bridge the gap between human intuition (looking at skyscrapers from different angles) and computational validation (checking that proposed solutions satisfy all mathematical constraints). Their elegant simplicity and computational efficiency make them ideal building blocks for constraint satisfaction algorithms in recreational mathematics and puzzle-solving applications.