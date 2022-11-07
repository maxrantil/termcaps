/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/07 16:07:33 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "vec.h"
# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <ctype.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ioctl.h>

# define DEL		0
# define BCK		1
# define CTRL_C		3
# define CTRL_D		4
# define D_QUO	34
# define S_QUO	39
# define ESCAPE     27
# define ENTER      10
# define DOWN		261
# define UP			262
# define LEFT       263
# define RIGHT      264
# define BACKSPACE	127
# define TAB		9

# define PROMPT "$> "
# define MINI_PROMPT "> "

# define BUFFSIZE   2048

typedef struct s_term
{
	int		ch;
	char	*inp;
	char	quote;
	t_vec	v_history;
	size_t	q_qty;
	size_t	ws_col;
	size_t	ws_row;
	size_t	index;
	size_t	bytes;
	size_t	c_col;
	size_t	c_row;
	size_t	total_row;
	size_t	prompt_len;
	size_t	m_prompt_len;
	char	**nl_addr;
	char	*input_cpy;
	size_t	total_row_cpy;
}			t_term;



void	ft_init(t_term *term, char *input);
void	ft_input_cycle(t_term *term, char *input);
int		ft_putc(int c);
void	ft_clearscreen(void);
void	ft_setcursor(int col, int row);
void	ft_run_capability(char *cap);
void	ft_window_size(t_term *term);
void	ft_init_signals(void);

/* void	kill_process(int sig); */

/*				History				*/
void	ft_history(t_term *term);
void	ft_history_get(t_term *term);
void	ft_history_write_to_file(t_term *term);
void	ft_history_trigger(t_term *term, char *input, int his);

/*		    Cursor Movement			*/
void	ft_opt_mv(t_term *term, char *input);
void	ft_line_mv(t_term *term, char *input);
void	ft_word_mv(t_term *term, char *input);

/*		  Printing to Display		*/
void	ft_print_trail(t_term *term, char *input);

/*		   New Line Mangement		*/
void	ft_shift_nl_addr(t_term *term, int num);
size_t	get_last_non_prompt_line(t_term *term);
size_t	ft_get_prompt_len(t_term *term, size_t row);
void	nl_addr_reset(t_term *term, char *input);
void	ft_remove_nl_addr(t_term *term, size_t row);
void	ft_reset_nl_addr(t_term *term, char *input);
char	*ft_is_prompt_line(t_term *term, size_t row);
void	nl_terminal_size(t_term *term, char *input);
void	ft_add_nl_last_row(t_term *term, char *input, size_t pos);
void	ft_add_nl_mid_row(t_term *term, char *input, size_t row, size_t pos);

/*		     Quote Handling 		*/
void	quote_handling(t_term *term, char ch);
void	ft_quote_decrement(char *input, t_term *term);

/*		        Deletion	 		*/
size_t	ft_row_lowest_line(t_term *term);
void	ft_delete(t_term *term, char *input);
void	ft_backspace(t_term *term, char *input);
void	ft_deletion_shift(char *input, t_term *term, int mode);

/*		       Insertion	 		*/
int		ft_get_input(void);
void	ft_insertion(t_term *term, char *input);
void	ft_arrow_input(t_term *term, char *input);
void	ft_esc_parse(t_term *term, char *input);

#endif
