#include "rush.h"

int	ft_allocate_memory(int **clues, int **grid)
{
	*clues = malloc(16 * sizeof(int));
	if (!*clues)
		return (0);
	*grid = malloc(16 * sizeof(int));
	if (!*grid)
	{
		free(*clues);
		return (0);
	}
	return (1);
}

void	ft_cleanup_and_error(int *clues, int *grid)
{
	if (clues)
		free(clues);
	if (grid)
		free(grid);
	write(1, "Error\n", 6);
}

void	ft_cleanup_success(int *clues, int *grid)
{
	free(clues);
	free(grid);
}

int	ft_process_skyscraper(char *input)
{
	int	*clues;
	int	*grid;

	if (!ft_allocate_memory(&clues, &grid))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!ft_parse_input(input, clues))
	{
		ft_cleanup_and_error(clues, grid);
		return (1);
	}
	ft_init_grid(grid);
	if (!ft_solve_skyscraper(clues, grid))
	{
		ft_cleanup_and_error(clues, grid);
		return (1);
	}
	ft_print_grid(grid);
	ft_cleanup_success(clues, grid);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	return (ft_process_skyscraper(argv[1]));
}
