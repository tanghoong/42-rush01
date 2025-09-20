#include "rush.h"

/* Write "Error\n" and return 0 for convenience */
static int	fail_error(void)
{
	write(1, "Error\n", 6);
	return (0);
}

static int	validate_and_fill(int *dst, char **tok, int off, int N)
{
	for (int i = 0; i < N; ++i)
	{
		int ok, v = ft_atoi_strict(tok[off + i], &ok);
		if (!ok || v < 1 || v > N)
			return (0);
		dst[i] = v;
	}
	return (1);
}

int	parse_input(const char *arg, t_input *in)
{
	char	**tok;
	int		count;

	in->N = 0;
	in->top = in->bottom = in->left = in->right = NULL;
	if (!arg)
		return (fail_error());
	tok = ft_split_spaces(arg, &count);
	if (!tok)
		return (fail_error());
	if (count == 0 || (count % 4) != 0)
	{
		free_split(tok, count);
		return (fail_error());
	}
	in->N = count / 4;
	if (in->N < 2 || in->N > 9)
	{
		free_split(tok, count);
		return (fail_error());
	}
	in->top = (int*)malloc(sizeof(int) * in->N);
	in->bottom = (int*)malloc(sizeof(int) * in->N);
	in->left = (int*)malloc(sizeof(int) * in->N);
	in->right = (int*)malloc(sizeof(int) * in->N);
	if (!in->top || !in->bottom || !in->left || !in->right)
	{
		free_input(in);
		free_split(tok, count);
		return (fail_error());
	}
	/* fill and validate ranges 1..N */
	if (!validate_and_fill(in->top, tok, 0, in->N)
	 || !validate_and_fill(in->bottom, tok, in->N, in->N)
	 || !validate_and_fill(in->left, tok, 2 * in->N, in->N)
	 || !validate_and_fill(in->right, tok, 3 * in->N, in->N))
	{
		free_input(in);
		free_split(tok, count);
		return (fail_error());
	}
	free_split(tok, count);
	return (1);
}

void	free_input(t_input *in)
{
	if (!in) return ;
	if (in->top) free(in->top);
	if (in->bottom) free(in->bottom);
	if (in->left) free(in->left);
	if (in->right) free(in->right);
	in->top = in->bottom = in->left = in->right = NULL;
	in->N = 0;
}

void	print_grid(int **g, int N)
{
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			ft_putnbr(g[r][c]);
			if (c + 1 < N) ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
