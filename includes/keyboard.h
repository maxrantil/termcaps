/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 17:12:06 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H

# include "libft.h"
# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <ctype.h>
# include <stdlib.h>
# include <fcntl.h>

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

# define BUFFSIZE   2048

typedef struct s_termterm
{
	int		ch;
	int		bytes;
	int		c_col;
	int		c_row;
	int		total_col;
	int		total_row;
}			t_term;

static struct termios	g_orig_termios;

void	ft_init(t_term *term);
void	ft_input_cycle(t_term *term, char *input);
int		ft_putc(int c);
void	ft_clearscreen(void);
void	ft_setcursor(int col, int row);
void	ft_run_capability(char *cap);

/* void	kill_process(int sig); */

/*		    Cursor Movement			*/
void	ft_alt_mv_left(t_term *term, char *input);
void	ft_alt_mv_right(t_term *term, char *input);

int		ft_get_input(void);
void	ft_print_trail(t_term *term, char *input);
void	ft_clear_trail(void);

void	ft_insertion_shift(t_term *term, char *input);
void	ft_deletion_shift(char *input, t_term *term, int mode);

void	ft_cursor_mv(t_term *term);
void	ft_esc_parse(t_term *term, char *input);

#endif
