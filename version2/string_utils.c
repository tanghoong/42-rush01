#include "rush.h"

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_count_numbers(char *str)
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
