NAME 		= pipex
CC		= cc
CFLAGS 		= -Wall -Wextra -Werror
SRCS		= pipex.c pipex_utils.c \
		  
BONUSSRCS	= deneme.c pipex_bonus_utils.c \
		  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

LIBFT		= libft/libft.a
DIR_LIBFT	= libft

all: $(NAME)

$(NAME): $(SRCS)
	make -s -C $(DIR_LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)

bonus: $(BONUSSRCS)
	make -s -C $(DIR_LIBFT)
	$(CC) $(CFLAGS) $(BONUSSRCS) $(LIBFT) -o $(NAME)
clean:
	make -s -C $(DIR_LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -s -C $(DIR_LIBFT) fclean

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean bonus re rebonus