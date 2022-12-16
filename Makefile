# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/17 18:22:31 by mrantil           #+#    #+#              #
#    Updated: 2022/12/14 17:29:55 by mbarutel         ###   ########.fr        #
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
C_INVISIBLE = \033[?25l
C_VISIBLE = \033[?25h

MAKEFLAGS	+= --no-print-directory

NAME		=	keyboard
CC			=	gcc
CFLAGS 		= 	-Wall -Wextra
CFLAGS		+=	-Wunreachable-code -Wtype-limits
# CFLAGS		+=	-Wpedantic -Wconversion
CFLAGS		+=	-O3

LEAK_CHECK	=	-g
# EAK_CHECK	+=	-fsanitize=address

SOURCES 	= 	srcs
OBJECTS 	= 	objs
INCLUDES	= 	includes
LIBRARIES 	= 	libft

SOURCE_COUNT = $(words $(FILES))

H_FILES 	= 	keyboard

UNAME		= $(shell uname)
ifeq ($(UNAME), Darwin)
TERMCAP		=	-ltermcap
CFLAGS		+= 	-Werror
endif
ifeq ($(UNAME), Linux)
TERMCAP		=	-lncurses
endif

FILES 		= 	ft_add_nl_last_row \
				ft_add_nl_mid_row \
				ft_alt_mv \
				ft_arrow_input \
				ft_backspace \
				ft_bslash_escape_check \
				ft_copy \
				ft_create_prompt_line \
				ft_ctrl \
				ft_cut \
				ft_delete \
				ft_deletion_shift \
				ft_end_cycle \
				ft_esc_parse \
				ft_quote_flag_reset \
				ft_get_input \
				ft_get_prompt_len \
				ft_getline_nbr \
				ft_heredoc_handling \
				ft_history_file_get \
				ft_history_get \
				ft_history_reset_nl \
				ft_history_trigger \
				ft_history_write_to_file \
				ft_history \
				ft_init_signals \
				ft_init \
				ft_input_cycle \
				ft_insertion \
				ft_is_prompt_line \
				ft_len_lowest_line \
				ft_line_down \
				ft_line_mv \
				ft_line_up \
				ft_mv_prompt_len \
				ft_nl_removal \
				ft_paste \
				ft_print_input \
				ft_print_trail \
				ft_putc \
				ft_quote_decrement \
				ft_quote_flag_check \
				ft_quote_handling \
				ft_remove_nl_addr \
				ft_reset_nl_addr \
				ft_restart_cycle \
				ft_row_lowest_line \
				ft_run_capability \
				ft_setcursor \
				ft_shift_insert \
				ft_shift_nl_addr \
				ft_trigger_nl \
				ft_window_size \
				ft_word_mv \
				main \

H_PATHS 	= 	$(addsuffix .h, $(addprefix $(INCLUDES)/, $(H_FILES)))
O_PATHS 	= 	$(addsuffix .o, $(addprefix $(OBJECTS)/, $(FILES)))

LIBS		= 	libft.a

HEADERS		=	-I$(INCLUDES)/ -Ilibft/includes/

ASSERT_OBJECT = && printf "$(ERASE_LINE)" && printf "$@ $(GREEN)$(BOLD) ✓$(RESET)" || (printf "$@ $(RED)$(BOLD)✘$(RESET)\n\n" | printf "$(C_VISIBLE)" && exit 1)

all: libft $(NAME)

$(NAME): $(OBJECTS) $(O_PATHS)
	@$(CC) $(CFLAGS) $(HEADERS) $(O_PATHS) $(LEAK_CHECK) $(LIBS) $(TERMCAP) -o $@
	@printf "Compiled $(BOLD)$(GREEN)$(NAME)$(RESET)!\n\n"
	@printf "$(C_VISIBLE)"

$(OBJECTS):
	@make -C $(LIBRARIES)
	@mkdir -p $(OBJECTS)
	@printf "$(GREEN)_________________________________________________________________\n$(RESET)"
	@printf "$(NAME): $(GREEN)$(OBJECTS) directory was created.$(RESET)\n\n\n"

$(O_PATHS): $(OBJECTS)/%.o:$(SOURCES)/%.c $(H_PATHS) Makefile
	@printf "$(C_INVISIBLE)"
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
	@printf "keyboard:	$(RED)executeable was deleted$(RESET)\n"

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
