#include "rush.h"

int	ft_is_valid_placement(t_grid *grid, int row, int col, int val)
{
	int	bit;

	bit = 1 << (val - 1);
	if (grid->row_used[row] & bit)
		return (0);
	if (grid->col_used[col] & bit)
		return (0);
	return (1);
}

void	ft_place_value(t_grid *grid, int row, int col, int val)
{
	int	bit;

	bit = 1 << (val - 1);
	grid->cells[row][col] = val;
	grid->row_used[row] |= bit;
	grid->col_used[col] |= bit;
}

void	ft_remove_value(t_grid *grid, int row, int col, int val)
{
	int	bit;

	bit = 1 << (val - 1);
	grid->cells[row][col] = 0;
	grid->row_used[row] &= ~bit;
	grid->col_used[col] &= ~bit;
}

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

static int	ft_backtrack(t_grid *grid, t_input *input, int pos)
{
	int	row;
	int	col;
	int	val;

	if (pos == 16)
		return (ft_check_visibility(grid, input));
	row = pos / SIZE;
	col = pos % SIZE;
	if (grid->cells[row][col] != 0)
		return (ft_backtrack(grid, input, pos + 1));
	val = 1;
	while (val <= SIZE)
	{
		if (ft_is_valid_placement(grid, row, col, val))
		{
			ft_place_value(grid, row, col, val);
			if (ft_backtrack(grid, input, pos + 1))
				return (1);
			ft_remove_value(grid, row, col, val);
		}
		val++;
	}
	return (0);
}

int	ft_solve_skyscraper(t_input *input, t_grid *grid)
{
	return (ft_backtrack(grid, input, 0));
}
