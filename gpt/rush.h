#ifndef RUSH_H
# define RUSH_H

# define SIZE 4

int		write(int fd, const void *buf, unsigned long count);
void	*malloc(unsigned long size);
void	free(void *ptr);

typedef struct s_input
{
	int	clues[16];
}	t_input;

typedef struct s_grid
{
	int	cells[4][4];
	int	row_used[4];
	int	col_used[4];
}	t_grid;

int		ft_parse_input(char *str, t_input *input);
int		ft_solve_skyscraper(t_input *input, t_grid *grid);
int		ft_is_valid_placement(t_grid *grid, int row, int col, int val);
void	ft_place_value(t_grid *grid, int row, int col, int val);
void	ft_remove_value(t_grid *grid, int row, int col, int val);
int		ft_check_visibility(t_grid *grid, t_input *input);
int		ft_count_visible_left(int *row);
int		ft_count_visible_right(int *row);
int		ft_count_visible_top(t_grid *grid, int col);
int		ft_count_visible_bottom(t_grid *grid, int col);
void	ft_print_grid(t_grid *grid);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int n);
int		ft_atoi(char *str);
int		ft_is_digit(char c);
int		ft_is_space(char c);

#endif
