#ifndef RUSH_H
# define RUSH_H

# define SIZE 4

int		write(int fd, const void *buf, unsigned long count);
void	*malloc(unsigned long size);
void	free(void *ptr);

/* Parser functions */
int		ft_parse_input(char *str, int *clues);
int		ft_count_numbers(char *str);
int		ft_extract_numbers(char *str, int *numbers);
int		ft_validate_clues(int *clues);

/* Solver functions */
int		ft_solve_skyscraper(int *clues, int *grid);
int		ft_backtrack(int *grid, int *clues, int pos);
int		ft_is_valid_placement(int *grid, int row, int col, int val);
void	ft_place_value(int *grid, int *row_used, int *col_used, int row);

/* Visibility checking functions */
int		ft_check_visibility(int *grid, int *clues);
int		ft_count_visible_left(int *row);
int		ft_count_visible_right(int *row);
int		ft_count_visible_top(int *grid, int col);
int		ft_count_visible_bottom(int *grid, int col);

/* Output functions */
void	ft_print_grid(int *grid);

/* Utility functions */
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int n);

/* String utility functions */
int		ft_is_digit(char c);
int		ft_is_space(char c);
int		ft_count_numbers(char *str);

/* Grid utility functions */
void	ft_init_grid(int *grid);
void	ft_init_arrays(int *row_used, int *col_used);
int		ft_get_cell_value(int *grid, int row, int col);
void	ft_set_cell_value(int *grid, int row, int col, int val);

#endif