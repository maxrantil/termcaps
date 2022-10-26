/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/26 07:58:10 by mbarutel         ###   ########.fr       */
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
# define D_QUOTE	34
# define S_QUOTE	39
# define ESCAPE     27
# define ENTER      10
# define DOWN		261
# define UP			262
# define LEFT       263
# define RIGHT      264
# define BACKSPACE	127
# define TAB		9

# define PROMPT "$SuperPinoyBoy> "
# define MINI_PROMPT "> " // This cannot be longer that PROMPT and both these string can not be changed

# define BUFFSIZE   2048

typedef struct s_term
{
	int		ch;
	char	quote;
	t_vec	v_history;
	size_t	q_qty;
	size_t	ws_col;
	size_t	ws_row;
	size_t	indx;
	size_t	q_prompt;
	size_t	bytes;
	size_t	c_col;
	size_t	c_row;
	size_t	total_row;
	size_t	prompt_len;
	size_t	m_prompt_len;
	char	**nl_addr;
	// int	total_col;
}			t_term;

static struct termios	g_orig_termios;

void	ft_init(t_term *term);
/* void	ft_disable_raw_mode(void); */
void	ft_input_cycle(t_term *term, char *input);
int		ft_putc(int c);
void	ft_clearscreen(void);
void	ft_setcursor(int col, int row);
void	ft_run_capability(char *cap);
void	ft_window_size(t_term *term);
void	ft_init_signals(void);

/* void	kill_process(int sig); */

/*	History	*/
void	ft_history(t_term *term);
void	ft_history_get(t_term *term);
void	ft_history_write_to_file(t_term *term);


/*		    Cursor Movement			*/
void	ft_alt_cursor_mv(t_term *term, char *input);

int		ft_get_input(void);
void	ft_print_trail(t_term *term, char *input);
void	ft_clear_trail(void);

void	ft_insertion_shift(t_term *term, char *input);
void	ft_deletion_shift(char *input, t_term *term, int mode);

void	ft_cursor_mv(t_term *term, char *input);
void	ft_esc_parse(t_term *term, char *input);



char	*get_str_end(char *str);

#endif
