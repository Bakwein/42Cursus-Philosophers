NAME = philo

HEADER = include/philo.h

CC = cc

FLAGS = -Wall -Wextra -Werror -O2

SRC = src/libft_func/ft_atoi.c \
			src/libft_func/ft_itoa.c \
			src/libft_func/ft_strlen.c \
			src/libft_func/ft_strncmp.c \
			src/init_philo_struct.c \
			src/monitor.c \
			src/parse_arg.c \
			src/main.c \
			src/philo_utils.c \
			src/start_philo.c \
			src/utils.c

OBJ = $(SRC:%.c= %.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(OBJ) -lpthread -O2 -o $(NAME)

%.o	: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean	:
	@rm -f $(OBJ)

fclean	:	clean
	@$(RM) $(NAME)

re	:	fclean all