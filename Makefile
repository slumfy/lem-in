# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vifonne <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/05 18:03:13 by vifonne           #+#    #+#              #
#    Updated: 2019/01/25 11:29:46 by vifonne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=		main.c				\
					parser.c			\
					map_pipe_list.c		\
					tools.c				\
					link_pipe.c			\
					check_stdin.c		\
					ft_error.c			\
					explore.c			\
					check_map.c			\
					path_list.c			\
					sort_path_tab.c		\
					ant_path.c			\
					tab_struc_len.c		\
					check_path.c		\
					path_calculator.c	\
					count_connex.c		\
					set_dimension.c		\
					path_totab.c		\
					free_struct.c
SRCS_DIR	=		$(addprefix srcs/, $(SRCS))
LIBFT		=		libft/
OBJ			=		$(SRCS_DIR:.c=.o)
CC			=		gcc -Wall -Wextra -Werror
HDR			=		-I $(LIBFT) -I .
NAME		=		lem-in
.PHONY		=		all $(NAME) $(OBJ) clean fclean re
UNDER		=		$'\x1b[4m$'
RED			=		$'\x1b[31m$'
GREEN		=		$'\x1b[32m$'
YELLOW		=		$'\x1b[33m$'
WHITE		=		$'\x1b[37m$'
END			=		$'\x1b[0m$'

all:	$(NAME)

$(NAME): $(OBJ)
	@echo "\n$(UNDER)Compiling libft :$(END)\t\t$(YELLOW)$(CC)$(WHITE)\n"
	@/bin/echo -n "0% ["
	@make -C libft/
	@echo "] 100%"
	@echo "\n$(UNDER)Compiling $(NAME) :$(END)\t\t$(YELLOW)$(CC)$(WHITE)\n"
	$(CC) $(OBJ) -o $(NAME) $(HDR) -L $(LIBFT) -lft

%.o: %.c
	$(CC) $(HDR) -c $< -o $@

clean:
	@echo "$(UNDER)Cleaning project :$(END)$(RED)"
	rm -rf $(OBJ)
	@echo "$(GREEN)[OK]$(RED)\n"
	make clean -C $(LIBFT)
	@echo "$(GREEN)[OK]$(WHITE)"

fclean:	clean
	@echo "\n$(UNDER)Full cleaning project :$(END)$(RED)"
	rm -f $(NAME)
	@echo "$(GREEN)[OK]$(RED)\n"
	make fclean -C $(LIBFT)
	@echo "$(GREEN)[OK]$(WHITE)"

re:	fclean all
