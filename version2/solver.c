#include "rush.h"

int	ft_is_valid_placement(int *grid, int row, int col, int val)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		if (ft_get_cell_value(grid, row, i) == val)
			return (0);
		i++;
	}
	j = 0;
	while (j < SIZE)
	{
		if (ft_get_cell_value(grid, j, col) == val)
			return (0);
		j++;
	}
	return (1);
}

int	ft_backtrack(int *grid, int *clues, int pos)
{
	int	row;
	int	col;
	int	val;

	if (pos == 16)
		return (ft_check_visibility(grid, clues));
	row = pos / SIZE;
	col = pos % SIZE;
	if (ft_get_cell_value(grid, row, col) != 0)
		return (ft_backtrack(grid, clues, pos + 1));
	val = 1;
	while (val <= SIZE)
	{
		if (ft_is_valid_placement(grid, row, col, val))
		{
			ft_set_cell_value(grid, row, col, val);
			if (ft_backtrack(grid, clues, pos + 1))
				return (1);
			ft_set_cell_value(grid, row, col, 0);
		}
		val++;
	}
	return (0);
}

int	ft_solve_skyscraper(int *clues, int *grid)
{
	return (ft_backtrack(grid, clues, 0));
}
