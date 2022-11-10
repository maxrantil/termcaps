/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/10 11:44:41 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "vec.h"
# include <termcap.h>//control if all these are needed
# include <term.h>//same same
# include <curses.h>//same same
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
	char	inp[BUFFSIZE];
	char	quote;
	t_vec	v_history;
	size_t	q_qty;
	size_t	ws_col;
	size_t	ws_row;
	size_t	index;
	size_t	bytes;
	size_t	c_col;
	size_t	c_row;
	size_t	start_row;
	size_t	total_row;
	size_t	prompt_len;
	size_t	m_prompt_len;
	char	**nl_addr;
	char	*input_cpy;
	size_t	total_row_cpy;
}			t_term;

void	ft_init(t_term *t);
void	ft_input_cycle(t_term *t);
int		ft_putc(int c);
void	ft_clearscreen(void);
void	ft_setcursor(int col, int row);
void	ft_run_capability(char *cap);
void	ft_window_size(t_term *t);
void	ft_init_signals(void);
int		ft_get_linenbr(void);

/* void	kill_process(int sig); */

/*				History				*/
void	ft_history(t_term *t);
void	ft_history_get(t_term *t);
void	ft_history_write_to_file(t_term *t);
void	ft_history_trigger(t_term *t, int his);

/*		    Cursor Movement			*/
void	ft_opt_mv(t_term *t);
void	ft_line_mv(t_term *t);
void	ft_word_mv(t_term *t);

/*		  Printing to Display		*/
void	ft_print_trail(t_term *t);

/*		   New Line Mangement		*/
void	ft_shift_nl_addr(t_term *t, int num);
size_t	get_last_non_prompt_line(t_term *t);
size_t	ft_get_prompt_len(t_term *t, size_t row);
void	nl_addr_reset(t_term *t);
void	ft_remove_nl_addr(t_term *t, size_t row);
void	ft_reset_nl_addr(t_term *t);
char	*ft_is_prompt_line(t_term *t, size_t row);
void	nl_terminal_size(t_term *t);
void	ft_add_nl_last_row(t_term *t, size_t pos);
void	ft_add_nl_mid_row(t_term *t, size_t row, size_t pos);

/*		     Quote Handling 		*/
void	ft_quote_handling(t_term *t, char ch);
void	ft_quote_decrement(t_term *t, int num);

/*		        Deletion	 		*/
size_t	ft_row_lowest_line(t_term *t);
void	ft_delete(t_term *t);
void	ft_backspace(t_term *t);
void	ft_deletion_shift(t_term *t, int mode);

/*		       Insertion	 		*/
int		ft_get_input(void);
void	ft_insertion(t_term *t);
void	ft_arrow_input(t_term *t);
void	ft_esc_parse(t_term *t);
void	ft_create_prompt_line(t_term *t, size_t loc);

#endif
