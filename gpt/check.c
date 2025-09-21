#include "rush.h"

static int	ft_check_row_visibility(t_grid *grid, int row, t_input *input)
{
	int	left_clue;
	int	right_clue;

	left_clue = input->clues[8 + row];
	right_clue = input->clues[12 + row];
	if (ft_count_visible_left(grid->cells[row]) != left_clue)
		return (0);
	if (ft_count_visible_right(grid->cells[row]) != right_clue)
		return (0);
	return (1);
}

static int	ft_check_col_visibility(t_grid *grid, int col, t_input *input)
{
	int	top_clue;
	int	bottom_clue;

	top_clue = input->clues[col];
	bottom_clue = input->clues[4 + col];
	if (ft_count_visible_top(grid, col) != top_clue)
		return (0);
	if (ft_count_visible_bottom(grid, col) != bottom_clue)
		return (0);
	return (1);
}

int	ft_check_visibility(t_grid *grid, t_input *input)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (!ft_check_row_visibility(grid, i, input))
			return (0);
		if (!ft_check_col_visibility(grid, i, input))
			return (0);
		i++;
	}
	return (1);
}
