#include "rush.h"

/* Count visible from left on a full row */
int	count_visible_left(const int *line, int N)
{
	int maxh = 0, vis = 0;
	for (int i = 0; i < N; ++i)
	{
		if (line[i] > maxh)
		{
			maxh = line[i];
			vis++;
		}
	}
	return (vis);
}

/* Count visible from right on a full row */
int	count_visible_right(const int *line, int N)
{
	int maxh = 0, vis = 0;
	for (int i = N - 1; i >= 0; --i)
	{
		if (line[i] > maxh)
		{
			maxh = line[i];
			vis++;
		}
	}
	return (vis);
}

/* Row prefix feasibility (left side only).
 * After placing 'filled_cols' cells in this row:
 *  - visible_so_far_from_left must not exceed left_req;
 *  - even in the *best* case, total visible by the end must be able to reach left_req.
 * A loose but effective upper bound is: vis_so_far + (N - filled_cols).
 */
int row_prefix_feasible(const int *row, int N, int filled_cols, int left_req)
{
    int maxh = 0;
    int vis  = 0;

    for (int c = 0; c < filled_cols; ++c)
    {
        int h = row[c];
        if (h > maxh) { maxh = h; vis++; }
    }
    /* cannot already exceed target */
    if (vis > left_req)
        return (0);
    /* even if all remaining become new maxima each time, can we still reach target? */
    if (vis + (N - filled_cols) < left_req)
        return (0);
    return (1);
}


/* When a row is completed, its left/right must match exactly */
int	row_done_ok(const int *row, int N, int left_req, int right_req)
{
	int L = count_visible_left(row, N);
	if (L != left_req) return (0);
	if (count_visible_right(row, N) != right_req) return (0);
	return (1);
}

/* Quick column prefix feasibility (top side only).
 * We check two things after filling 'filled_rows' rows:
 * 1) visible_so_far_from_top must not exceed top_req.
 * 2) even in the best case, total visible cannot exceed top_req by being too small.
 *    Upper bound: visible_so_far + (N - filled_rows).
 * This is a loose but effective pruning. Bottom is fully checked when column completes.
 */
int	col_prefix_feasible(int **g, int N, int filled_rows, int top_req, int col)
{
	int maxh = 0, vis = 0;

	for (int r = 0; r < filled_rows; ++r)
	{
		int h = g[r][col];
		if (h > maxh) { maxh = h; vis++; }
	}
	if (vis > top_req) return (0);
	if (vis + (N - filled_rows) < top_req) return (0);
	return (1);
}

/* Final check for a completed column (both top & bottom) */
int	col_final_ok(int **g, int N, int col, int top_req, int bottom_req)
{
	int maxh = 0, vis_top = 0;
	for (int r = 0; r < N; ++r)
	{
		int h = g[r][col];
		if (h > maxh) { maxh = h; vis_top++; }
	}
	maxh = 0;
	int vis_bot = 0;
	for (int r = N - 1; r >= 0; --r)
	{
		int h = g[r][col];
		if (h > maxh) { maxh = h; vis_bot++; }
	}
	return (vis_top == top_req && vis_bot == bottom_req);
}
