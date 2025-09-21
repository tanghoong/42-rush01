#include "rush.h"

int	main(int argc, char **argv)
{
	int	*clues;
	int	*grid;

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	clues = malloc(16 * sizeof(int));
	if (!clues)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	grid = malloc(16 * sizeof(int));
	if (!grid)
	{
		free(clues);
		write(1, "Error\n", 6);
		return (1);
	}
	if (!ft_parse_input(argv[1], clues))
	{
		free(clues);
		free(grid);
		write(1, "Error\n", 6);
		return (1);
	}
	ft_init_grid(grid);
	if (!ft_solve_skyscraper(clues, grid))
	{
		free(clues);
		free(grid);
		write(1, "Error\n", 6);
		return (1);
	}
	ft_print_grid(grid);
	free(clues);
	free(grid);
	return (0);
}
