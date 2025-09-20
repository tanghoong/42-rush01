#include "rush.h"

int	ft_count_visible_left(int *row)
{
	int	max_height;
	int	visible;
	int	i;

	max_height = 0;
	visible = 0;
	i = 0;
	while (i < SIZE)
	{
		if (row[i] > max_height)
		{
			max_height = row[i];
			visible++;
		}
		i++;
	}
	return (visible);
}

int	ft_count_visible_right(int *row)
{
	int	max_height;
	int	visible;
	int	i;

	max_height = 0;
	visible = 0;
	i = SIZE - 1;
	while (i >= 0)
	{
		if (row[i] > max_height)
		{
			max_height = row[i];
			visible++;
		}
		i--;
	}
	return (visible);
}

int	ft_count_visible_top(t_grid *grid, int col)
{
	int	max_height;
	int	visible;
	int	i;

	max_height = 0;
	visible = 0;
	i = 0;
	while (i < SIZE)
	{
		if (grid->cells[i][col] > max_height)
		{
			max_height = grid->cells[i][col];
			visible++;
		}
		i++;
	}
	return (visible);
}

int	ft_count_visible_bottom(t_grid *grid, int col)
{
	int	max_height;
	int	visible;
	int	i;

	max_height = 0;
	visible = 0;
	i = SIZE - 1;
	while (i >= 0)
	{
		if (grid->cells[i][col] > max_height)
		{
			max_height = grid->cells[i][col];
			visible++;
		}
		i--;
	}
	return (visible);
}
