# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkryvono <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/30 10:08:04 by vkryvono          #+#    #+#              #
#    Updated: 2018/12/29 16:53:46 by vkryvono         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = lem-in

CC			=	gcc
FLAGS 		=	-Wall -Wextra -Werror

INC_PATH	=	./inc
SRC_PATH	=	./src
OBJ_PATH	=	./obj

SRC			=	main.c\
                reader.c\
                validator.c\
                graph.c\
                simulator.c\
                solver.c\
                new_solving.c\
                flow_calculation.c\
                bfsearch.c\
                todelete.c\
                output.c

OBJ			=	$(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))

INC			=	-I./libft/includes\
				-I./inc

LIBFT 		=	-L./libft -lft

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o:$(SRC_PATH)/%.c
	$(CC) $(INC) -o $@ -c $< #$(FLAGS)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
