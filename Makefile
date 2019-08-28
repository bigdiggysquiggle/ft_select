# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromansk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:18:25 by dromansk          #+#    #+#              #
#    Updated: 2019/08/28 16:18:14 by dromansk         ###   ########.fr        #
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
	gcc -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L)

clean:
	make -C ./libft clean
	rm -rf $(O)

fclean: clean
	make -C ./libft fclean
	rm -rf $(NAME) $(NAME).dSYM

re: fclean all

reclean: re
	make clean

sreclean: fclean
	make -C ./libft sreclean
	gcc -Wall -Werror -Wextra -c $(I) $(SRCS) -g
	gcc -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L) -g
	make clean

test: clean
	gcc -Wall -Werror -Wextra -c $(I) $(SRCS)
	gcc -Wall -Werror -Wextra -o $(NAME) $(O) $(I) $(L)
	make clean
	./$(NAME)

comptest: fclean all
	make -c libft reclean
	make test

recomp: clean
	rm -rf $(NAME)
	make all
	make clean
