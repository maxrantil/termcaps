# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/10/21 15:13:58 by mrantil          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
SHELL := /bin/bash
GREEN = \033[32m
GREEN_BACKGROUND = \033[42m
WHITE_BACKGROUND = \033[47m
VIOLET_BACKGROUND = \033[0;45m
YELLOW_BACKGROUND = \033[0;43m
WHITE = \033[37m
YELLOW = \033[33m
BLACK = \033[30m
VIOLET = \033[35m
RESET = \033[0m
RED = \033[31m
CYAN = \033[36m
BOLD = \033[1m

#PRINTING TOOLS
ERASE_LINE = \033[K
UP = A
DOWN = B
RIGHT = C
LEFT = D
MOVE = \033[

#FORBID KEYBOARD INTERACT
$(shell stty -echo)

MAKEFLAGS	+= --no-print-directory

NAME		=	keyboard
CC			=	gcc
CFLAGS 		= 	-Wall -Wextra
#CFLAGS		+= 	-Werror
CFLAGS		+=	-Wunreachable-code -Wtype-limits 
CFLAGS		+=	-Wpedantic
CFLAGS		+=	-O3

LEAK_CHECK	=	-g
EAK_CHECK	+=	-fsanitize=address

SOURCES 	= 	srcs
OBJECTS 	= 	objs
INCLUDES	= 	includes
LIBRARIES 	= 	libft

SOURCE_COUNT = $(words $(FILES))

H_FILES 	= 	keyboard
TERMCAP		=	-lncurses


FILES 		= 	main \
				ft_alt_mv \
				ft_cursor_mv \
				ft_run_capability \
				ft_setcursor \
				ft_insertion_shift \
				ft_deletion_shift \
				ft_print_trail \
				ft_clear_trail \
				ft_history \
				ft_history_get \
				ft_history_write_to_file \
				ft_init \
				ft_init_signals \
				ft_get_input \
				ft_input_cycle \
				ft_putc \
				ft_esc_parse \
				ft_disable_raw_mode \
				ft_window_size \

H_PATHS 	= 	$(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
C_PATHS 	= 	$(addsuffix .c, $(addprefix $(SOURCES)/, $(FILES)))
O_PATHS 	= 	$(addsuffix .o, $(addprefix $(OBJECTS)/, $(FILES)))

LIBS		= 	libft.a

HEADERS		=	-I$(INCLUDES)/ -Ilibft/includes/

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(GREEN)$(BOLD) ✔$(RESET)" || printf "$@ $(RED)$(BOLD)✘$(RESET)\n"

all: libft $(NAME)

$(NAME): $(OBJECTS) $(O_PATHS)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ $(O_PATHS) $(TERMCAP) $(LIBS) $(LEAK_CHECK)
	@printf "Compiled $(BOLD)$(GREEN)$(NAME)$(RESET)!\n\n"

$(OBJECTS):
	@make -C $(LIBRARIES)
	@mkdir -p $(OBJECTS)
	@printf "$(GREEN)_________________________________________________________________\n$(RESET)"
	@printf "$(NAME): $(GREEN)$(OBJECTS) directory was created.$(RESET)\n\n\n"

$(O_PATHS): $(OBJECTS)/%.o:$(SOURCES)/%.c $(H_PATHS) Makefile
	@printf "$(MOVE)2$(UP)"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ $(LEAK_CHECK) $(ASSERT_OBJECT)
	@make pbar

libft:
	@make -C $(LIBRARIES)
	@cp $(LIBRARIES)/$(LIBS) .

clean:
	@make -C $(LIBRARIES) clean
	@rm -rf $(OBJECTS)
	@printf "$(NAME):	$(RED)$(OBJECTS) was deleted$(RESET)\n"

fclean: clean
	@make -C $(LIBRARIES) fclean
	@rm -f $(LIBS)
	@rm -f $(NAME)
	@printf "$(NAME):	$(RED)binary was deleted$(RESET)\n"

re: fclean all

pbar:
	$(eval LOADED_COUNT = $(words $(wildcard $(OBJECTS)/*.o)))
	@printf "\r$(MOVE)76$(RIGHT)Files compiled [$(BOLD)$(GREEN)$(LOADED_COUNT)$(RESET) / $(BOLD)$(GREEN)$(SOURCE_COUNT)$(RESET)]\n"
	@for ((i = 1; i <= $(LOADED_COUNT) * 100 / $(SOURCE_COUNT); i++)); do\
		printf "$(GREEN_BACKGROUND) $(RESET)" ;\
	done ;
	@for ((i = 1; i <= 100 - ($(LOADED_COUNT) * 100 / $(SOURCE_COUNT)); i++)); do\
		printf "$(WHITE_BACKGROUND) $(RESET)" ;\
	done ;
	@printf "$(GREEN_BACKGROUND)$(BOLD)$(WHITE)$(MOVE)55$(LEFT)[$$(($(LOADED_COUNT) * 100 / $(SOURCE_COUNT))).$$(($(LOADED_COUNT) * 1000 / $(SOURCE_COUNT) % 10))%%]$(MOVE)54$(RIGHT)$(RESET)\n"


.PHONY: all libft clean fclean re

#ALLOW KEYBOARD INTERACT
$(shell stty echo)
