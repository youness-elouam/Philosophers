FILES = ./philosophers.c ./ft_atoi.c ./timer.c ./ft_isdigit.c ./utils.c

OBJS = $(FILES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = philo

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean

.SECONDARY: $(OBJS)