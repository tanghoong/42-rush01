#include "rush.h"

static int	ft_check_row_visibility(int *grid, int row, int *clues)
{
	int	left_clue;
	int	right_clue;
	int	row_array[SIZE];
	int	i;

	left_clue = clues[8 + row];
	right_clue = clues[12 + row];
	i = 0;
	while (i < SIZE)
	{
		row_array[i] = ft_get_cell_value(grid, row, i);
		i++;
	}
	if (ft_count_visible_left(row_array) != left_clue)
		return (0);
	if (ft_count_visible_right(row_array) != right_clue)
		return (0);
	return (1);
}

static int	ft_check_col_visibility(int *grid, int col, int *clues)
{
	int	top_clue;
	int	bottom_clue;

	top_clue = clues[col];
	bottom_clue = clues[4 + col];
	if (ft_count_visible_top(grid, col) != top_clue)
		return (0);
	if (ft_count_visible_bottom(grid, col) != bottom_clue)
		return (0);
	return (1);
}

int	ft_check_visibility(int *grid, int *clues)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (!ft_check_row_visibility(grid, i, clues))
			return (0);
		if (!ft_check_col_visibility(grid, i, clues))
			return (0);
		i++;
	}
	return (1);
}
