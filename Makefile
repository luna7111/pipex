# **************************************************************************** #
#                                                                              #
#                                                     _.._  .           .      #
#    Makefile                                       .' .-'`        *           #
#                                                  /  /       +        *       #
#    By: ldel-val <ldel-val@42madrid.com>          |  |           *            #
#                                                  \  '.___.;       +          #
#    Created: 2024/11/25 12:45:41 by ldel-val       '._  _.'   .        .      #
#    Updated: 2025/01/18 17:03:07 by ldel-val          ``                      #
#                                                                              #
# **************************************************************************** #

#Compiler and linker
CC 		:=	cc

#Remove tool
RM 		:=	rm -f

#Flags
LIBFT	:=	libft/libft.a
CFLAGS 	:=	-Wall -Wextra -Werror -g3 -Isrc

#Project stuff 

NAME 	:=	pipex
SRC 	:=	src/pipex.c\
			src/children_behaviours.c\
			src/utils.c
OBJ		:=	$(SRC:.c=.o)

#Bonus stuff

BONUS_NAME	:=	pipex_bonus
BONUS_SRC	:=	src/pipex_bonus.c\
				src/children_behaviours.c\
				src/utils.c
BONUS_OBJ	:=	$(BONUS_SRC:.c=.o)

#-----------------------------------------------------------------------------#
#                                    Rules                                    #
#-----------------------------------------------------------------------------#

all: $(NAME) $(BONUS_NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) 

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_NAME) 

clean:
	$(MAKE) -C libft fclean
	$(RM) $(OBJ)

fclean:
	$(MAKE) -C libft fclean
	$(RM) $(OBJ)
	$(RM) $(BONUS_OBJ)
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
