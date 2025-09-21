#include "rush.h"

void	ft_init_grid(int *grid)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		grid[i] = 0;
		i++;
	}
}

void	ft_init_arrays(int *row_used, int *col_used)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		row_used[i] = 0;
		col_used[i] = 0;
		i++;
	}
}

int	ft_get_cell_value(int *grid, int row, int col)
{
	return (grid[row * SIZE + col]);
}

void	ft_set_cell_value(int *grid, int row, int col, int val)
{
	grid[row * SIZE + col] = val;
}
