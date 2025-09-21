#include "rush.h"

static void	ft_init_grid(t_grid *grid)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			grid->cells[i][j] = 0;
			j++;
		}
		grid->row_used[i] = 0;
		grid->col_used[i] = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_input	input;
	t_grid	grid;

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	if (!ft_parse_input(argv[1], &input))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	ft_init_grid(&grid);
	if (!ft_solve_skyscraper(&input, &grid))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	ft_print_grid(&grid);
	return (0);
}
