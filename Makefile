# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromansk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:18:25 by dromansk          #+#    #+#              #
#    Updated: 2019/10/23 18:28:50 by dromansk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

SRCS = ./src/*.c

I = -I ./includes -I ./libft/includes

O = *.o

L = -L ./libft -lft

all: $(NAME)

$(NAME):
	make -C ./libft reclean
	gcc -Wall -Werror -Wextra -c $(I) $(SRCS) 
	gcc -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L) -lcurses

clean:
	make -C ./libft clean
	rm -rf $(O)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME) $(NAME).dSYM

re: fclean all

reclean: re
	make clean

sre: fclean
	make -C ./libft sreclean
	gcc -g -Wall -Werror -Wextra -c $(I) $(SRCS)
	gcc -g -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L) -lcurses

sreclean: sre
	make clean

fre: fclean
	make -C ./libft reclean
	gcc -fsanitize=address -Wall -Werror -Wextra $(I) -c $(SRCS)
	gcc -fsanitize=address -Wall -Werror -Wextra $(I) -o $(NAME) $(O) $(L) -lcurses

test: clean
	gcc -Wall -Werror -Wextra -c $(I) $(SRCS) 
	gcc -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L) -lcurses
	make clean
	./$(NAME) *

comptest: fclean all
	make -C libft reclean
	make test

recomp: clean
	rm -rf $(NAME)
	make all
	make clean
