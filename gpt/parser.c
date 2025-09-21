#include "rush.h"

static int	ft_count_numbers(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_digit(str[i]))
		{
			count++;
			while (str[i] && ft_is_digit(str[i]))
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_parse_number(char *str, int *i, int *number)
{
	int	j;

	j = 0;
	*number = 0;
	while (str[*i] && ft_is_digit(str[*i]))
	{
		if (j == 0)
			*number = str[*i] - '0';
		else
			*number = *number * 10 + (str[*i] - '0');
		j++;
		(*i)++;
	}
	return (j > 0);
}

static int	ft_extract_numbers(char *str, int *numbers)
{
	int	i;
	int	num_idx;

	i = 0;
	num_idx = 0;
	while (str[i] && num_idx < 16)
	{
		while (str[i] && ft_is_space(str[i]))
			i++;
		if (str[i] && ft_is_digit(str[i]))
		{
			if (ft_parse_number(str, &i, &numbers[num_idx]))
				num_idx++;
		}
		else if (str[i])
			i++;
	}
	return (num_idx);
}

static int	ft_validate_clues(int *clues)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (clues[i] < 1 || clues[i] > SIZE)
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse_input(char *str, t_input *input)
{
	int	numbers[16];
	int	i;

	if (!str)
		return (0);
	if (ft_count_numbers(str) != 16)
		return (0);
	if (ft_extract_numbers(str, numbers) != 16)
		return (0);
	if (!ft_validate_clues(numbers))
		return (0);
	i = 0;
	while (i < 16)
	{
		input->clues[i] = numbers[i];
		i++;
	}
	return (1);
}
