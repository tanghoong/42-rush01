#include "rush.h"

/* Return 0 if a hard contradiction is detected, 1 otherwise. */
int	precheck_contradictions(const t_input *in)
{
	int N = in->N;
	int all_rows_inc = 1;   /* all rows demand left==N and right==1 */
	int all_cols_inc = 1;   /* all cols demand top==N and bottom==1 */

	/* Basic per-line bounds: for any permutation of size N,
	 * visible_left + visible_right is in [2 .. N+1].
	 * Same for columns (top + bottom).
	 */
	for (int i = 0; i < N; ++i)
	{
		int srow = in->left[i] + in->right[i];
		int scol = in->top[i] + in->bottom[i];

		if (srow < 2 || srow > N + 1)
			return (0);
		if (scol < 2 || scol > N + 1)
			return (0);

		/* Extreme cases: if left==N then the row must be strictly increasing,
		 * which forces right==1. Similarly, right==N forces left==1.
		 * Same logic for columns: top==N -> bottom==1, bottom==N -> top==1.
		 */
		if (in->left[i] == N && in->right[i] != 1)
			return (0);
		if (in->right[i] == N && in->left[i] != 1)
			return (0);
		if (in->top[i] == N && in->bottom[i] != 1)
			return (0);
		if (in->bottom[i] == N && in->top[i] != 1)
			return (0);

		if (!(in->left[i] == N && in->right[i] == 1))
			all_rows_inc = 0;
		if (!(in->top[i] == N && in->bottom[i] == 1))
			all_cols_inc = 0;
	}

	/* Global impossible patterns:
	 * 1) If ALL rows require strictly increasing (left==N, right==1),
	 *    every row must be "1..N". Then each column would be constant
	 *    (all 'j' in column j), violating column uniqueness => impossible.
	 * 2) If ALL columns require strictly increasing (top==N, bottom==1),
	 *    every column must be "1..N". Then each row would be constant,
	 *    violating row uniqueness => impossible.
	 */
	if (all_rows_inc)
		return (0);
	if (all_cols_inc)
		return (0);

	return (1);
}

/* Allocate 2D grid NxN */
static int	**alloc_grid(int N)
{
	int **g = (int**)malloc(sizeof(int*) * N);
	if (!g) return (NULL);
	for (int i = 0; i < N; ++i)
	{
		g[i] = (int*)malloc(sizeof(int) * N);
		if (!g[i])
		{
			for (int k = 0; k < i; ++k) free(g[k]);
			free(g);
			return (NULL);
		}
		for (int j = 0; j < N; ++j) g[i][j] = 0;
	}
	return (g);
}

static void	free_grid(int **g, int N)
{
	if (!g) return ;
	for (int i = 0; i < N; ++i) free(g[i]);
	free(g);
}

/* Try values 1..N with row/col bitmasks */
static int	can_place(t_state *st, int r, int c, int v)
{
	int bit = 1 << (v - 1);
	if (st->row_used[r] & bit) return (0);
	if (st->col_used[c] & bit) return (0);
	return (1);
}

static void	do_place(t_state *st, int r, int c, int v)
{
	int bit = 1 << (v - 1);
	st->g[r][c] = v;
	st->row_used[r] |= bit;
	st->col_used[c] |= bit;
}

static void	undo_place(t_state *st, int r, int c, int v)
{
	int bit = 1 << (v - 1);
	st->g[r][c] = 0;
	st->row_used[r] &= ~bit;
	st->col_used[c] &= ~bit;
}

/* Backtracking by cells (r,c). Returns 1 if found a solution. */
static int	bt(t_state *st, int r, int c)
{
	int N = st->N;

	if (r == N)
		return (1); /* filled all rows -> success */

	if (st->g[r][c])
	{
		int nr = r, nc = c + 1;
		if (nc == N) { nr = r + 1; nc = 0; }
		return (bt(st, nr, nc));
	}

	for (int v = 1; v <= N; ++v)
	{
		if (!can_place(st, r, c, v))
			continue;
		do_place(st, r, c, v);


        /* NEW: row-left prefix feasibility (we have filled c+1 cells in this row) */
        if (row_prefix_feasible(st->g[r], N, c + 1, st->left[r]))
        {
            /* Column top-side prefix feasibility */
            if (col_prefix_feasible(st->g, N, r + 1, st->top[c], c))
            {
                int ok = 1;
                /* If row completes, enforce left/right exactly. */
                if (c + 1 == N)
                    ok = row_done_ok(st->g[r], N, st->left[r], st->right[r]);
                /* If column completes, enforce top/bottom exactly. */
                if (ok && r + 1 == N)
                    ok = col_final_ok(st->g, N, c, st->top[c], st->bottom[c]);
                if (ok)
                {
                    int nr = r, nc = c + 1;
                    if (nc == N) { nr = r + 1; nc = 0; }
                    if (bt(st, nr, nc))
                        return (1);
                }
            }
        }
		undo_place(st, r, c, v);
	}
	return (0);
}

int	solve_first_solution(t_input *in, int ***out_grid)
{
	t_state st;
	int **g;

	g = alloc_grid(in->N);
	if (!g) return (0);
	for (int i = 0; i < in->N; ++i) { st.row_used[i] = 0; st.col_used[i] = 0; }
	st.N = in->N;
	st.g = g;
	st.top = in->top;
	st.bottom = in->bottom;
	st.left = in->left;
	st.right = in->right;

	for (int i = 0; i < in->N; i++)
	{
		if (st.top[i] == 1)
			do_place(&st, 0, i, st.N);
		if (st.bottom[i] == 1)
			do_place(&st, st.N - 1, i, st.N);
		if (st.left[i] == 1)
			do_place(&st, i, 0, st.N);
		if (st.right[i] == 1)
			do_place(&st, i, st.N - 1, st.N);
	}

	if (bt(&st, 0, 0))
	{
		*out_grid = g;
		return (1);
	}
	free_grid(g, in->N);
	return (0);
}
