NAME = rush-01NAME = rush-01



SRCS = main.c parser.c utils.c vis.c solver.c output.c check.cSRCS = main.c parser.c utils.c vis.c solver.c



OBJS = $(SRCS:.c=.o)OBJS = $(SRCS:.c=.o)



CC = gccCC = gcc

CFLAGS = -Wall -Wextra -WerrorCFLAGS = -Wall -Wextra -Werror



all: $(NAME)all: $(NAME)



$(NAME): $(OBJS)$(NAME): $(OBJS)

	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)



clean:clean:

	rm -f $(OBJS)	rm -f $(OBJS)



fclean: cleanfclean: clean

	rm -f $(NAME)	rm -f $(NAME)



re: fclean allre: fclean all



.PHONY: all clean fclean re.PHONY: all clean fclean re