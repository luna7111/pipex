# **************************************************************************** #
#                                                                              #
#                                                     _.._  .           .      #
#    Makefile                                       .' .-'`        *           #
#                                                  /  /       +        *       #
#    By: ldel-val <ldel-val@42madrid.com>          |  |           *            #
#                                                  \  '.___.;       +          #
#    Created: 2024/11/25 12:45:41 by ldel-val       '._  _.'   .        .      #
#    Updated: 2025/01/10 16:44:51 by ldel-val          ``                      #
#                                                                              #
# **************************************************************************** #

#Compiler and linker
CC 		:=	cc

#Remove tool
RM 		:=	rm -f

#Flags
LIBFT	:=	libft/libft.a
CFLAGS 	:=	-Wall -Wextra -Werror -O3 -Isrc

#Project stuff 

NAME 	:=	pipex
SRC 	:=	src/pipex.c
OBJ		:=	$(SRC:.c=.o)

#Bonus stuff

BONUS_NAME	:=	pipex_bonus
BONUS_SRC	:=	src_bonus/pipex.c
BONUS_OBJ	:=	$(BONUS_SRC:.c=.o)

#-----------------------------------------------------------------------------#
#                                    Rules                                    #
#-----------------------------------------------------------------------------#

all: $(NAME) $(BONUS_NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

clean:
	$(MAKE) -C libft fclean
	$(RM) $(OBJ)

fclean:
	$(MAKE) -C libft fclean
	$(RM) $(OBJ)
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
