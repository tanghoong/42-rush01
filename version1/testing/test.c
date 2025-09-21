#include "rush.h"

// Simple test to verify the parsing and basic functionality
int main()
{
    t_input input;
    t_grid grid;
    
    // Test case: "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"
    // This should create a solvable 4x4 skyscraper puzzle
    
    char test_str[] = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2";
    
    if (ft_parse_input(test_str, &input))
    {
        write(1, "Parse successful\n", 17);
        
        // Initialize grid
        int i = 0, j = 0;
        while (i < SIZE)
        {
            j = 0;
            while (j < SIZE)
            {
                grid.cells[i][j] = 0;
                j++;
            }
            grid.row_used[i] = 0;
            grid.col_used[i] = 0;
            i++;
        }
        
        if (ft_solve_skyscraper(&input, &grid))
        {
            write(1, "Solution found:\n", 16);
            ft_print_grid(&grid);
        }
        else
        {
            write(1, "No solution found\n", 18);
        }
    }
    else
    {
        write(1, "Parse failed\n", 13);
    }
    
    return 0;
}