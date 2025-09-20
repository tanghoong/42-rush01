#include "rush.h"

/* -------- tiny libc (only what's needed) -------- */

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f');
}

int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/* Strict atoi: returns ok=0 if empty, overflow, or contains non-digits. */
int	ft_atoi_strict(const char *s, int *ok)
{
	long v = 0;
	int  i = 0;

	*ok = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (!ft_is_digit(s[i]))
			return (0);
		v = v * 10 + (s[i] - '0');
		if (v > 1000000) /* unreasonable upper bound guard */
			return (0);
		i++;
	}
	*ok = 1;
	return ((int)v);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(const char *s)
{
	if (!s) return ;
	while (*s)
		write(1, s++, 1);
}

/* prints positive int (we only print 1..9 here) */
void	ft_putnbr(int n)
{
	char c;

	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = '0' + n;
		write(1, &c, 1);
	}
}

/* Split by spaces, collapse multiple spaces, returns array of tokens.
 * count: number of tokens. Returns NULL on alloc failure.
 * NOTE: tokens are newly allocated strings; free with free_split().
 */
char	**ft_split_spaces(const char *s, int *count)
{
	int i = 0, start, len, n = 0, cap = 16;
	char **arr;

	*count = 0;
	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char*) * cap);
	if (!arr) return (NULL);
	while (s[i])
	{
		while (s[i] && ft_is_space(s[i])) i++;
		if (!s[i]) break;
		start = i;
		while (s[i] && !ft_is_space(s[i])) i++;
		len = i - start;
		if (n == cap)
		{
			char **tmp;
			cap *= 2;
			tmp = (char **)malloc(sizeof(char*) * cap);
			if (!tmp) { free_split(arr, n); return (NULL); }
			for (int k = 0; k < n; ++k) tmp[k] = arr[k];
			free(arr);
			arr = tmp;
		}
		arr[n] = (char*)malloc(len + 1);
		if (!arr[n]) { free_split(arr, n); return (NULL); }
		for (int k = 0; k < len; ++k) arr[n][k] = s[start + k];
		arr[n][len] = '\0';
		n++;
	}
	*count = n;
	return (arr);
}

void	free_split(char **arr, int count)
{
	if (!arr) return ;
	for (int i = 0; i < count; ++i)
		if (arr[i]) free(arr[i]);
	free(arr);
}
