# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: idouni <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 12:19:44 by idouni            #+#    #+#              #
#    Updated: 2023/03/26 20:58:34 by idouni           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = philo

CC     = cc

RM     = rm -rf

FLAGS  =  -Wall -Wextra -Werror #-fsanitize=thread

HR     = philo.h

MND    = philo.c

TLS    = lists.c \
		tools.c \
		tools_1.c \
		tools_2.c \
		tools_3.c \

OBJ_M  = $(MND:%.c=%.o)

OBJ_T  = $(TLS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ_M) $(OBJ_T) $(HR) 
	@$(CC) $(FLAGS) $(OBJ_T) $(OBJ_M) -o $(NAME)
	@clear && echo "==$(NAME)_compiled=============="

%.o: %.c $(HR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_M)
	$(RM) $(OBJ_T)
	@clear && echo "==Object_files_deleted=========="

fclean: clean
	$(RM) $(NAME)
	@clear && echo "==All_created_files_deleted====="

re: fclean all
	@clear && echo "==Compilation_reseted==========="

.PHONY: all clean fclean re
