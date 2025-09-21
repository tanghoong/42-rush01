# Parser.c Documentation

## Overview

The `parser.c` file contains the input processing and validation logic for the 4x4 skyscraper puzzle solver. This module is responsible for converting raw command-line input strings into structured data, validating format and content, and preparing the clues for the solving algorithm. It implements robust parsing with comprehensive error detection according to 42 school standards.

## File Purpose

This module handles:
- **String tokenization** - Breaking input into individual numbers
- **Number extraction** - Converting string digits to integers  
- **Input validation** - Ensuring correct format and count
- **Range validation** - Verifying clue values are within valid range (1-4)
- **Data transformation** - Converting raw input to structured clues array
- **Error detection** - Comprehensive validation with early failure detection

## Design Philosophy

### Defensive Programming
- **Multi-layered validation** - Count, extraction, range, and format checking
- **Early failure detection** - Return immediately on any validation error
- **Robust parsing** - Handle whitespace, malformed input gracefully
- **No assumptions** - Validate every aspect of input data

### Modular Architecture
- **Single responsibility** - Each function handles one parsing aspect
- **Clear interfaces** - Well-defined input/output contracts
- **Reusable components** - Helper functions for common operations
- **Error propagation** - Consistent boolean return pattern

---

## Function Documentation

### 1. `ft_count_numbers`

```c
static int ft_count_numbers(char *str)
```

**Purpose**: Counts the total number of numeric tokens in the input string.

**Scope**: `static` - Internal helper function for input validation

**Parameters**:
- `char *str` - Input string to analyze

**Return Value**:
- `int` - Count of numeric tokens found (0 or positive)

**Algorithm**:
1. **Iterate through string** character by character
2. **Detect number start** when encountering first digit
3. **Skip entire number** by consuming all consecutive digits
4. **Increment counter** for each complete number found
5. **Continue scanning** until end of string

**Step-by-Step Logic**:
```c
count = 0;
i = 0;
while (str[i])                    // Scan entire string
{
    if (ft_is_digit(str[i]))      // Found start of number
    {
        count++;                  // Count this number
        while (str[i] && ft_is_digit(str[i]))  // Skip entire number
            i++;
    }
    else
        i++;                      // Skip non-digit character
}
```

**Examples**:
```c
ft_count_numbers("1 2 3 4")           → 4
ft_count_numbers("12 34 567")         → 3  
ft_count_numbers("1  2   3    4")     → 4 (handles multiple spaces)
ft_count_numbers("1a2b3c")           → 3 (ignores letters)
ft_count_numbers("")                  → 0
ft_count_numbers("abc def")           → 0 (no numbers)
```

**Use Case**: Pre-validation to quickly check if input has exactly 16 numbers before detailed parsing.

---

### 2. `ft_parse_number`

```c
static int ft_parse_number(char *str, int *i, int *number)
```

**Purpose**: Extracts a single integer from the string starting at position `*i`.

**Scope**: `static` - Internal helper for number extraction

**Parameters**:
- `char *str` - Source string containing the number
- `int *i` - Pointer to current position (modified to point after number)
- `int *number` - Pointer to store extracted integer value

**Return Value**:
- `1` - Successfully parsed a number
- `0` - No number found at current position

**Algorithm**:
1. **Initialize parsing state** (`j = 0`, `*number = 0`)
2. **Process each digit** while consecutive digits found
3. **Build number incrementally** using decimal place value
4. **Update position** to point after the number
5. **Return success** if at least one digit was processed

**Mathematical Logic**:
```c
// For multi-digit numbers like "123":
// First digit '1': number = 1
// Second digit '2': number = 1 * 10 + 2 = 12  
// Third digit '3': number = 12 * 10 + 3 = 123
if (j == 0)
    *number = str[*i] - '0';           // First digit: direct conversion
else  
    *number = *number * 10 + (str[*i] - '0');  // Subsequent: decimal shift + add
```

**Position Management**:
- **Input**: `*i` points to start of potential number
- **Processing**: `*i` advances through each digit
- **Output**: `*i` points to first non-digit after number

**Examples**:
```c
// str = "123 456", i = 0
ft_parse_number(str, &i, &num);  // num = 123, i = 3
// str = "abc", i = 0  
ft_parse_number(str, &i, &num);  // returns 0, i unchanged
```

**Error Handling**: Returns 0 if no digits found, but doesn't advance position.

---

### 3. `ft_extract_numbers`

```c
static int ft_extract_numbers(char *str, int *numbers)
```

**Purpose**: Extracts all numeric values from input string into an integer array.

**Scope**: `static` - Internal helper for bulk number extraction

**Parameters**:
- `char *str` - Input string containing space-separated numbers
- `int *numbers` - Array to store extracted integers (must have space for 16)

**Return Value**:
- `int` - Number of integers successfully extracted

**Algorithm**:
1. **Initialize scanning** (`i = 0`, `num_idx = 0`)
2. **Skip whitespace** before each potential number
3. **Parse number** if digit found at current position
4. **Store result** and advance to next array position
5. **Continue until** end of string or 16 numbers found
6. **Return count** of numbers extracted

**Whitespace Handling**:
```c
while (str[i] && ft_is_space(str[i]))    // Skip all whitespace
    i++;
```
- Handles multiple spaces, tabs, newlines between numbers
- Robust against irregular formatting in input

**Number Processing**:
```c
if (str[i] && ft_is_digit(str[i]))       // Valid number start
{
    if (ft_parse_number(str, &i, &numbers[num_idx]))  // Extract number
        num_idx++;                        // Advance array index
}
```

**Non-digit Character Handling**:
```c
else if (str[i])                         // Non-digit, non-space character
    i++;                                 // Skip it and continue
```

**Safety Limits**:
- **Maximum extraction**: Stops at 16 numbers (puzzle requirement)
- **Bounds protection**: `num_idx < 16` prevents array overflow
- **Graceful termination**: Returns count even if input continues

**Examples**:
```c
int nums[16];
ft_extract_numbers("1 2 3 4", nums);           → 4, nums = {1,2,3,4,...}
ft_extract_numbers("1  2   3    4", nums);     → 4 (handles spacing)
ft_extract_numbers("1,2,3,4", nums);           → 4 (ignores commas)
ft_extract_numbers("1 two 3 four", nums);      → 2, nums = {1,3,...}
```

---

### 4. `ft_validate_clues`

```c
static int ft_validate_clues(int *clues)
```

**Purpose**: Validates that all clue values are within the valid range for 4x4 skyscraper puzzles.

**Scope**: `static` - Internal validation helper

**Parameters**:
- `int *clues` - Array of 16 clue values to validate

**Return Value**:
- `1` - All clues are valid (in range 1-4)
- `0` - At least one clue is invalid

**Validation Logic**:
```c
i = 0;
while (i < 16)                           // Check all 16 clues
{
    if (clues[i] < 1 || clues[i] > SIZE) // SIZE = 4
        return (0);                      // Fail immediately on invalid clue
    i++;
}
return (1);                              // All clues valid
```

**Range Requirements**:
- **Minimum value**: 1 (at least one building visible)
- **Maximum value**: 4 (all buildings visible in increasing height order)
- **Invalid values**: 0, negative numbers, values > 4

**Skyscraper Logic Context**:
- **Clue = 1**: Only tallest building (4) visible from that direction
- **Clue = 2**: Two buildings visible (e.g., heights 3,4 or 2,4)
- **Clue = 3**: Three buildings visible (e.g., heights 2,3,4)
- **Clue = 4**: All four buildings visible (heights 1,2,3,4)

**Examples**:
```c
int valid_clues[] = {4,3,2,1,1,2,2,2,4,3,2,1,1,2,2,2};
ft_validate_clues(valid_clues);         → 1 (all in range 1-4)

int invalid_clues[] = {4,3,2,0,...};   // Contains 0
ft_validate_clues(invalid_clues);       → 0 (invalid)

int invalid_clues2[] = {4,3,2,5,...};  // Contains 5  
ft_validate_clues(invalid_clues2);      → 0 (invalid)
```

---

### 5. `ft_parse_input`

```c
int ft_parse_input(char *str, t_input *input)
```

**Purpose**: Main parsing function that orchestrates the complete input validation and conversion process.

**Scope**: Public function (exported in header) - Main module interface

**Parameters**:
- `char *str` - Raw input string from command line
- `t_input *input` - Output structure to populate with parsed clues

**Return Value**:
- `1` - Successful parsing and validation
- `0` - Any parsing or validation failure

**Multi-Stage Validation Process**:

#### **Stage 1: Null Pointer Check**
```c
if (!str)
    return (0);
```
- Prevents segmentation fault on NULL input
- Early termination for invalid pointer

#### **Stage 2: Count Validation**
```c
if (ft_count_numbers(str) != 16)
    return (0);
```
- Ensures exactly 16 numbers in input
- Quick pre-check before expensive parsing

#### **Stage 3: Extraction Validation**
```c
if (ft_extract_numbers(str, numbers) != 16)
    return (0);
```
- Double-checks that 16 numbers were actually extractable
- Handles edge cases where counting and extraction differ

#### **Stage 4: Range Validation**
```c
if (!ft_validate_clues(numbers))
    return (0);
```
- Verifies all clues are in valid range (1-4)
- Ensures puzzle constraints can be satisfied

#### **Stage 5: Data Transfer**
```c
i = 0;
while (i < 16)
{
    input->clues[i] = numbers[i];
    i++;
}
return (1);
```
- Copies validated numbers to output structure
- Only reached if all validation passes

**Validation Redundancy**:
- **Count vs Extract**: Both must return 16 for consistency
- **Multi-stage checking**: Each stage can catch different error types
- **Defense in depth**: Multiple validation layers prevent bad data

**Examples**:
```c
t_input input;

// Valid input
ft_parse_input("4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2", &input);  → 1

// Invalid: wrong count
ft_parse_input("1 2 3 4", &input);                           → 0

// Invalid: out of range  
ft_parse_input("5 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2", &input);  → 0

// Invalid: non-numeric
ft_parse_input("a b c d e f g h i j k l m n o p", &input);    → 0
```

---

## Input Format Specification

### Expected Input Structure
The parser expects exactly 16 space-separated integers representing clues in this order:

```
Position: 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
Meaning:  T0 T1 T2 T3 B0 B1 B2 B3 L0 L1 L2 L3 R0 R1 R2 R3
```

Where:
- **T0-T3**: Top clues (columns 0-3)
- **B0-B3**: Bottom clues (columns 0-3)  
- **L0-L3**: Left clues (rows 0-3)
- **R0-R3**: Right clues (rows 0-3)

### Visual Grid Representation
```
       T0  T1  T2  T3     ← positions 0-3
       ↓   ↓   ↓   ↓
    L0 →  [·] [·] [·] [·] ← R0  (positions 8,12)
    L1 →  [·] [·] [·] [·] ← R1  (positions 9,13)  
    L2 →  [·] [·] [·] [·] ← R2  (positions 10,14)
    L3 →  [·] [·] [·] [·] ← R3  (positions 11,15)
       ↑   ↑   ↑   ↑
       B0  B1  B2  B3     ← positions 4-7
```

### Valid Input Examples
```bash
# Standard spacing
"4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"

# Irregular spacing (still valid)
"4  3   2    1 1 2 2 2 4 3 2 1 1 2 2 2"

# Mixed whitespace (still valid)  
"4	3 2
1 1 2 2 2 4 3 2 1 1 2 2 2"
```

### Invalid Input Examples
```bash
# Wrong count
"1 2 3 4 5"

# Out of range values
"0 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
"4 3 2 5 1 2 2 2 4 3 2 1 1 2 2 2"

# Non-numeric content
"a b c d e f g h i j k l m n o p"
"1 2 three 4 5 6 7 8 9 10 11 12 13 14 15 16"

# Empty or null
""
(null pointer)
```

---

## Error Detection and Validation

### Validation Layers

#### **Layer 1: Pointer Safety**
- Null pointer detection prevents crashes
- Early return for invalid input pointer

#### **Layer 2: Count Validation**  
- Quick check for expected number of tokens
- Prevents processing of obviously malformed input

#### **Layer 3: Extraction Validation**
- Verifies that counted numbers are actually parseable
- Catches inconsistencies between counting and extraction

#### **Layer 4: Range Validation**
- Ensures all values meet puzzle constraints
- Validates business logic requirements

#### **Layer 5: Data Integrity**
- Final transfer only after all validation passes
- Guarantees clean data in output structure

### Error Categories

#### **Format Errors**
- Wrong number of arguments
- Non-numeric content where numbers expected
- Malformed number strings

#### **Range Errors**
- Values less than 1
- Values greater than 4  
- Zero or negative values

#### **Structural Errors**
- Null input pointer
- Inconsistent counting vs extraction
- Unexpected character sequences

### Validation Robustness

#### **Whitespace Tolerance**
```c
// All equivalent inputs:
"1 2 3 4"        // Single spaces
"1  2   3    4"  // Multiple spaces  
"1\t2\n3\r4"     // Mixed whitespace
```

#### **Error Recovery**
- No partial parsing - all or nothing approach
- Clean failure states with boolean returns
- No memory leaks or dangling state

---

## Integration with Project

### Module Dependencies
```
parser.c depends on:
├── rush.h (type definitions: t_input, SIZE)
├── utils.c (ft_is_digit, ft_is_space)  
└── system (no direct system calls)
```

### Interface Contract
```c
int ft_parse_input(char *str, t_input *input);
```

**Preconditions**:
- `str` can be NULL (handled safely)
- `input` must point to valid t_input structure

**Postconditions**:
- Returns 1: `input->clues` contains 16 valid values (1-4)
- Returns 0: `input` structure unchanged, no side effects

**Usage Pattern**:
```c
// In main.c
t_input input;
if (!ft_parse_input(argv[1], &input))
{
    // Handle error - no cleanup needed
    write(1, "Error\n", 6);  
    return (1);
}
// Use input.clues[0-15] safely
```

### Data Flow
```
Command line → argv[1] → ft_parse_input() → input.clues[16] → Solver
```

---

## Performance Analysis

### Time Complexity

#### **Per Function**:
- **ft_count_numbers**: O(n) - single string scan
- **ft_parse_number**: O(k) - k digits per number  
- **ft_extract_numbers**: O(n) - single string scan with parsing
- **ft_validate_clues**: O(1) - always checks exactly 16 values
- **ft_parse_input**: O(n) - dominated by string scanning

Where n = input string length, k = average digits per number

#### **Overall**: O(n) - linear in input string length

### Space Complexity
- **Local arrays**: `numbers[16]` = 64 bytes temporary storage
- **Loop variables**: O(1) additional space
- **No dynamic allocation**: All memory on stack
- **Overall**: O(1) - constant space usage

### Optimization Characteristics
- **Early termination**: Returns immediately on validation failure
- **Single-pass algorithms**: Most operations scan string only once
- **No redundant work**: Each validation layer adds unique value
- **Minimal copying**: Direct extraction to final storage

---

## Testing and Validation

### Unit Testing Strategy

#### **Function-Level Testing**
```c
// ft_count_numbers testing
assert(ft_count_numbers("1 2 3 4") == 4);
assert(ft_count_numbers("12 34") == 2);
assert(ft_count_numbers("") == 0);
assert(ft_count_numbers("abc") == 0);

// ft_validate_clues testing  
int valid[] = {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};
assert(ft_validate_clues(valid) == 1);
int invalid[] = {0,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};
assert(ft_validate_clues(invalid) == 0);
```

#### **Integration Testing**
```c
t_input input;

// Valid complete input
assert(ft_parse_input("4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2", &input) == 1);
assert(input.clues[0] == 4);
assert(input.clues[15] == 2);

// Invalid input
assert(ft_parse_input("1 2 3", &input) == 0);
assert(ft_parse_input(NULL, &input) == 0);
```

### Edge Case Testing

#### **Boundary Conditions**
- Empty string input
- Exactly 16 numbers (valid)
- 15 or 17 numbers (invalid)
- All minimum values (1,1,1,...)
- All maximum values (4,4,4,...)

#### **Malformed Input**
- Mixed numeric and non-numeric
- Numbers outside valid range
- Unusual whitespace patterns
- Very long input strings

### Error Condition Testing
```bash
# Test harness for validation
test_cases=(
    ""                                   # Empty
    "1 2 3"                             # Too few  
    "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17"  # Too many
    "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15"      # Out of range (0)
    "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16"     # Out of range (5)
    "a b c d e f g h i j k l m n o p"            # Non-numeric
)

for test in "${test_cases[@]}"; do
    if ./rush-01 "$test" 2>/dev/null; then
        echo "FAIL: Should have rejected '$test'"
    else
        echo "PASS: Correctly rejected '$test'"
    fi
done
```

---

## 42 Norm Compliance

### Function Standards
✅ **Function count**: 5 functions (exactly at limit)  
✅ **Function length**: All functions ≤ 25 lines after refactoring  
✅ **Function naming**: All use `ft_` prefix  
✅ **Static functions**: Internal helpers properly scoped  
✅ **Parameter clarity**: Clear, descriptive parameter names

### Code Quality
✅ **Single responsibility**: Each function has one clear parsing task  
✅ **Error handling**: Consistent boolean return pattern  
✅ **Input validation**: Comprehensive defensive programming  
✅ **No side effects**: Functions don't modify global state  
✅ **Clear logic flow**: Easy to follow validation sequence

### Style Compliance
✅ **Indentation**: Proper tab indentation throughout  
✅ **Braces**: K&R brace style  
✅ **Spacing**: Correct spacing around operators and keywords  
✅ **Variable declarations**: Proper declaration placement  
✅ **Line length**: All lines under 80 characters  
✅ **Comments**: Code is self-documenting without excessive comments

---

## Best Practices Demonstrated

### Defensive Programming
- **Null pointer checks**: Prevent segfaults
- **Bounds checking**: Prevent buffer overflows  
- **Range validation**: Ensure data meets business rules
- **Multi-layer validation**: Defense in depth approach

### Robust Parsing
- **Whitespace tolerance**: Handle various input formats
- **Error recovery**: Clean failure without side effects
- **Input sanitization**: Validate before processing
- **Early termination**: Fail fast on invalid input

### Clean Architecture
- **Separation of concerns**: Each function handles one aspect
- **Clear interfaces**: Well-defined input/output contracts
- **Composable functions**: Helper functions build up complexity
- **Testable design**: Easy to unit test individual components

### Memory Safety
- **Stack allocation**: No dynamic memory management
- **Bounds protection**: Array access within limits
- **No buffer overruns**: Safe string processing
- **Automatic cleanup**: Stack variables cleaned up automatically

This documentation provides complete understanding of the input processing pipeline that transforms raw command-line arguments into validated, structured data ready for the skyscraper puzzle solving algorithm.