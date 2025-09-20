#include "rush.h"

/* Entry:
 *  argv[1] must be a single quoted string of 4N integers in [1..N].
 *  On any error or no-solution, print "Error\n".
 *  On success, print the grid and newline per row.
 */
int	main(int argc, char **argv)
{
	t_input in;
	int   **grid;

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!parse_input(argv[1], &in))
		return (1); /* parse_input already printed Error */

    if (!precheck_contradictions(&in))
    {
        write(1, "Error\n", 6);
        free_input(&in);
        return (1);
    }

	if (!solve_first_solution(&in, &grid))
	{
		write(1, "Error\n", 6);
		free_input(&in);
		return (1);
	}
	print_grid(grid, in.N);

	/* cleanup */
	for (int r = 0; r < in.N; ++r) free(grid[r]);
	free(grid);
	free_input(&in);
	return (0);
}
