#ifndef RUSH_H
# define RUSH_H

# include <unistd.h>
# include <stdlib.h>

/* ----- Core types ----- */

typedef struct s_input {
	int N;        /* board size */
	int *top;     /* size N */
	int *bottom;  /* size N */
	int *left;    /* size N */
	int *right;   /* size N */
}	t_input;

typedef struct s_state {
	int N;
	int **g;          /* grid[N][N] */
	int *top;
	int *bottom;
	int *left;
	int *right;
	int row_used[9];  /* bitmask per row, N<=9 */
	int col_used[9];  /* bitmask per col, N<=9 */
}	t_state;

/* ----- Utils ----- */
int		ft_is_space(char c);
int		ft_is_digit(char c);
int		ft_atoi_strict(const char *s, int *ok);
void	ft_putchar(char c);
void	ft_putstr(const char *s);
void	ft_putnbr(int n);
char	**ft_split_spaces(const char *s, int *count);
void	free_split(char **arr, int count);

/* ----- Parser / IO ----- */
int		parse_input(const char *arg, t_input *in); /* return 1 if ok, else 0 */
void	free_input(t_input *in);
void	print_grid(int **g, int N);

/* ----- Fast contradiction precheck (optional but helpful) ----- */
int		precheck_contradictions(const t_input *in);

/* ----- Visibility ----- */
int		count_visible_left(const int *line, int N);
int		count_visible_right(const int *line, int N);
int		row_done_ok(const int *row, int N, int left_req, int right_req);
/* Column prefix feasibility (quick pruning) */
int		col_prefix_feasible(int **g, int N, int filled_rows, int top_req, int col);
/* Row prefix feasibility (left side) */
int     row_prefix_feasible(const int *row, int N, int filled_cols, int left_req);
/* Column final check when col is complete */
int		col_final_ok(int **g, int N, int col, int top_req, int bottom_req);

/* ----- Solver ----- */
int		solve_first_solution(t_input *in, int ***out_grid);

#endif
