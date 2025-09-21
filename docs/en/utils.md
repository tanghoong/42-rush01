# Utils.c Documentation

## Overview

The `utils.c` file contains fundamental utility functions that provide basic I/O operations and character classification for the 4x4 skyscraper puzzle solver. These functions serve as the foundation layer, replacing standard library functions with 42 school compliant implementations using only `write`, `malloc`, and `free`.

## File Purpose

This module provides:
- **Character classification** - Testing character types (space, digit)
- **Basic I/O operations** - Character and string output
- **Number formatting** - Integer to string conversion and output
- **42 compliance** - Custom implementations of forbidden standard library functions
- **Foundation layer** - Low-level utilities used throughout the project

## Design Philosophy

### Standard Library Replacement
- **No printf/puts**: Custom string output using `write()`
- **No isspace/isdigit**: Custom character classification
- **No atoi dependency**: Supporting number parsing elsewhere
- **Pure implementation**: Only uses allowed functions

### Minimalist Approach
- **Essential functions only**: Only what's needed for the project
- **Simple implementations**: Clear, readable algorithms
- **No feature bloat**: Focused on core requirements
- **Performance adequate**: Optimized for correctness over speed

---

## Function Documentation

### 1. `ft_is_space`

```c
int ft_is_space(char c)
```

**Purpose**: Determines if a character is considered whitespace.

**Parameters**:
- `char c` - Character to test

**Return Value**:
- `1` - Character is whitespace
- `0` - Character is not whitespace

**Algorithm**:
```c
return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
```

**Whitespace Characters Detected**:
- `' '` (0x20) - Space character
- `'\t'` (0x09) - Horizontal tab
- `'\n'` (0x0A) - Line feed (Unix newline)
- `'\r'` (0x0D) - Carriage return (Mac/Windows newline component)

**Use Cases**:
- **Input parsing**: Skipping whitespace between numbers
- **Token separation**: Identifying word boundaries
- **String cleaning**: Trimming unwanted spaces

**Examples**:
```c
ft_is_space(' ')  → 1
ft_is_space('\t') → 1
ft_is_space('\n') → 1
ft_is_space('a')  → 0
ft_is_space('5')  → 0
```

**Standard Library Equivalent**: `isspace()` from `<ctype.h>`

---

### 2. `ft_is_digit`

```c
int ft_is_digit(char c)
```

**Purpose**: Determines if a character represents a decimal digit.

**Parameters**:
- `char c` - Character to test

**Return Value**:
- `1` - Character is a digit (0-9)
- `0` - Character is not a digit

**Algorithm**:
```c
return (c >= '0' && c <= '9');
```

**Logic Explanation**:
- Uses ASCII character ordering
- '0' = 48, '1' = 49, ..., '9' = 57
- Any character in this range is a digit

**Use Cases**:
- **Number parsing**: Validating numeric input
- **Input validation**: Ensuring characters are digits before conversion
- **Lexical analysis**: Tokenizing numeric values

**Examples**:
```c
ft_is_digit('0') → 1
ft_is_digit('5') → 1
ft_is_digit('9') → 1
ft_is_digit('a') → 0
ft_is_digit(' ') → 0
ft_is_digit('+') → 0
```

**Standard Library Equivalent**: `isdigit()` from `<ctype.h>`

---

### 3. `ft_putchar`

```c
void ft_putchar(char c)
```

**Purpose**: Outputs a single character to standard output.

**Parameters**:
- `char c` - Character to output

**Return Value**:
- `void` - No return value

**Algorithm**:
```c
write(1, &c, 1);
```

**Implementation Details**:
- **File descriptor 1**: Standard output (stdout)
- **Buffer address**: `&c` (address of character variable)
- **Byte count**: `1` (single character)
- **System call**: Direct `write()` system call

**Use Cases**:
- **Character output**: Building block for all text output
- **String construction**: Used by `ft_putstr` for string output
- **Number formatting**: Used by `ft_putnbr` for digit output
- **Grid formatting**: Used by output functions for spacing

**Examples**:
```c
ft_putchar('A');    // Outputs: A
ft_putchar('\n');   // Outputs: newline
ft_putchar(' ');    // Outputs: space
```

**Error Handling**:
- **No error checking**: Assumes `write()` succeeds
- **System call failure**: Would be silent (consistent with 42 style)
- **Invalid descriptor**: System handles error

**Performance**: O(1) - single system call per character

---

### 4. `ft_putstr`

```c
void ft_putstr(char *str)
```

**Purpose**: Outputs a null-terminated string to standard output.

**Parameters**:
- `char *str` - Pointer to null-terminated string

**Return Value**:
- `void` - No return value

**Algorithm**:
1. **Null check**: Return immediately if `str` is NULL
2. **Character iteration**: Loop through string until null terminator
3. **Character output**: Use `ft_putchar()` for each character
4. **Pointer advancement**: Move to next character

**Step-by-Step Execution**:
```c
if (!str)           // Safety check for null pointer
    return;
i = 0;
while (str[i])      // Loop until '\0'
{
    ft_putchar(str[i]); // Output current character
    i++;            // Move to next character
}
```

**Safety Features**:
- **Null pointer protection**: Prevents segmentation fault
- **Standard behavior**: Matches expected string output behavior
- **No buffer overflow**: Relies on proper null termination

**Use Cases**:
- **Error messages**: Outputting "Error\n" for failures
- **Debug output**: Printing status messages (if needed)
- **String literals**: Outputting constant strings

**Examples**:
```c
ft_putstr("Hello");     // Outputs: Hello
ft_putstr("Error\n");   // Outputs: Error\n
ft_putstr("");          // Outputs: (nothing)
ft_putstr(NULL);        // Outputs: (nothing, safe)
```

**Performance**: O(n) where n is string length

---

### 5. `ft_putnbr`

```c
void ft_putnbr(int n)
```

**Purpose**: Outputs an integer to standard output in decimal format.

**Parameters**:
- `int n` - Integer to output

**Return Value**:
- `void` - No return value

**Algorithm** (Recursive):
1. **Base case**: If n < 10, output single digit
2. **Recursive case**: If n ≥ 10, output higher digits first, then current digit
3. **Digit extraction**: Use modulo and division for digit separation
4. **Character conversion**: Convert digit to ASCII character

**Step-by-Step for Multi-digit Numbers**:
```c
if (n >= 10)
{
    ft_putnbr(n / 10);      // Recursively output higher digits
    ft_putnbr(n % 10);      // Output current (rightmost) digit
}
else
{
    ft_putchar('0' + n);    // Convert digit to ASCII and output
}
```

**Mathematical Logic**:
- **Division by 10**: Removes rightmost digit (123 / 10 = 12)
- **Modulo 10**: Extracts rightmost digit (123 % 10 = 3)
- **ASCII conversion**: '0' + digit gives ASCII character ('0' + 3 = '3')

**Execution Example for n = 1234**:
```
Call ft_putnbr(1234):
├─ n >= 10, so call ft_putnbr(123) and ft_putnbr(4)
   ├─ ft_putnbr(123):
   │  ├─ n >= 10, so call ft_putnbr(12) and ft_putnbr(3)
   │     ├─ ft_putnbr(12):
   │     │  ├─ n >= 10, so call ft_putnbr(1) and ft_putnbr(2)
   │     │     ├─ ft_putnbr(1): outputs '1'
   │     │     └─ ft_putnbr(2): outputs '2'
   │     └─ ft_putnbr(3): outputs '3'
   └─ ft_putnbr(4): outputs '4'
Result: "1234"
```

**Use Cases**:
- **Grid output**: Printing cell values (1-4)
- **Debug information**: Displaying numeric values
- **Result formatting**: Converting solutions to readable format

**Examples**:
```c
ft_putnbr(0);     // Outputs: 0
ft_putnbr(7);     // Outputs: 7
ft_putnbr(42);    // Outputs: 42
ft_putnbr(1234);  // Outputs: 1234
```

**Limitations**:
- **No negative numbers**: Doesn't handle negative integers
- **No error checking**: Assumes valid input
- **Recursion depth**: Stack usage proportional to number of digits

**Performance**: O(log n) where n is the number value (recursive calls)

---

## Integration with Project

### Dependency Graph
```
main.c → ft_putstr (error messages)
output.c → ft_putnbr, ft_putchar (grid formatting)
parser.c → ft_is_space, ft_is_digit (input parsing)
All modules → Basic I/O functions
```

### Usage Patterns

#### Input Processing
```c
// In parser.c
while (str[i] && ft_is_space(str[i]))  // Skip whitespace
    i++;
if (ft_is_digit(str[i]))              // Validate numeric input
    // Process digit
```

#### Output Generation
```c
// In output.c
ft_putnbr(grid->cells[i][j]);         // Print cell value
if (j < SIZE - 1)
    ft_putchar(' ');                  // Add spacing
ft_putchar('\n');                     // End line
```

#### Error Handling
```c
// In main.c
if (error_condition)
{
    ft_putstr("Error\n");            // Standard error output
    return (1);
}
```

---

## Performance Analysis

### Time Complexity
- **ft_is_space**: O(1) - constant time comparison
- **ft_is_digit**: O(1) - constant time comparison  
- **ft_putchar**: O(1) - single system call
- **ft_putstr**: O(n) - linear in string length
- **ft_putnbr**: O(log n) - logarithmic in number value

### Space Complexity
- **ft_is_space**: O(1) - no additional space
- **ft_is_digit**: O(1) - no additional space
- **ft_putchar**: O(1) - single character on stack
- **ft_putstr**: O(1) - single index variable
- **ft_putnbr**: O(log n) - recursion stack depth

### System Call Efficiency
- **Direct write() calls**: No buffering overhead
- **Character-by-character**: Simple but not optimized for large output
- **Adequate for project**: 4x4 grid output is minimal

---

## Error Handling and Edge Cases

### Input Validation
- **ft_putstr null check**: Prevents segfault on NULL pointer
- **Character range**: ft_is_digit handles full ASCII range
- **Whitespace coverage**: ft_is_space covers common whitespace types

### Edge Cases Handled
```c
ft_putstr(NULL);     // Safe: returns without action
ft_putstr("");       // Safe: outputs nothing (correct behavior)
ft_putnbr(0);        // Correct: outputs '0'
ft_is_space('\0');   // Correct: returns 0
ft_is_digit('\xFF'); // Correct: returns 0 (non-ASCII)
```

### Limitations and Assumptions
- **ft_putnbr**: Assumes non-negative integers only
- **No buffer overflow protection**: Assumes proper null termination
- **No internationalization**: ASCII-only character handling
- **No error reporting**: Silent failure on system call errors

---

## 42 Norm Compliance

### Function Standards
✅ **Function count**: 5 functions (exactly at limit)  
✅ **Function length**: All functions ≤ 25 lines  
✅ **Function naming**: All use `ft_` prefix  
✅ **Parameter naming**: Clear, descriptive names  
✅ **Return consistency**: Consistent return value patterns

### Code Quality
✅ **Single responsibility**: Each function has one clear purpose  
✅ **No side effects**: Functions are predictable  
✅ **Clear logic**: Easy to understand algorithms  
✅ **Minimal dependencies**: Only uses allowed functions

### Style Compliance
✅ **Indentation**: Proper tab indentation  
✅ **Spacing**: Correct spacing around operators  
✅ **Braces**: K&R brace style  
✅ **Variable declarations**: Proper declaration placement  
✅ **Line length**: All lines under 80 characters

---

## Testing Strategies

### Unit Testing Approach
```c
// Character classification tests
assert(ft_is_space(' ') == 1);
assert(ft_is_space('a') == 0);
assert(ft_is_digit('5') == 1);
assert(ft_is_digit('x') == 0);

// Output testing (manual verification)
ft_putchar('A');      // Should see: A
ft_putstr("Hello");   // Should see: Hello  
ft_putnbr(42);        // Should see: 42
```

### Integration Testing
- **Parser integration**: Test with whitespace-separated input
- **Output integration**: Verify grid formatting
- **Error message integration**: Confirm error output format

### Boundary Testing
- **ASCII limits**: Test character functions with boundary values
- **Number limits**: Test ft_putnbr with 0, single digits, large numbers
- **String limits**: Test empty strings, very long strings

---

## Usage Examples and Best Practices

### Recommended Usage Patterns
```c
// Safe string output
if (error_message)
    ft_putstr(error_message);

// Number formatting in loops
for (i = 0; i < SIZE; i++)
{
    ft_putnbr(grid[i]);
    if (i < SIZE - 1)
        ft_putchar(' ');
}

// Input parsing
while (ft_is_space(*input))
    input++;
if (ft_is_digit(*input))
    // Process number
```

### Anti-patterns to Avoid
```c
// Don't assume non-null without checking
ft_putstr(potentially_null_string);  // BAD

// Don't use for negative numbers
ft_putnbr(-42);  // UNDEFINED BEHAVIOR

// Don't rely on error reporting
if (ft_putchar('x') == ERROR)  // NO ERROR RETURN
```

---

## Future Enhancements and Extensibility

### Potential Improvements
- **ft_putnbr_safe**: Version with negative number support
- **ft_putstr_safe**: Version with length limits
- **Error return codes**: Functions that report success/failure
- **Buffered output**: More efficient for large output

### Current Design Strengths
- **Simplicity**: Easy to understand and maintain
- **Reliability**: Minimal failure modes
- **Performance**: Adequate for project requirements
- **Compliance**: Meets all 42 requirements

This documentation provides complete understanding of the utility functions that form the foundation of the skyscraper puzzle solver's I/O and character processing capabilities.