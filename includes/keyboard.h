/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 12:38:06 by mrantil          ###   ########.fr       */
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

# define KILL		3
# define CTRL_D		4
# define D_QUOTE	34
# define S_QUOTE	39
# define ESCAPE     0x001b
# define ENTER      0x000a
# define DOWN		0x0105
# define UP			0x0106
# define LEFT       0x0107
# define RIGHT      0x0108
# define BACKSPACE	0x007F
# define TAB		0x0009

# define DEL		0x0000
# define BCK		0x0001

# define BUFFSIZE   4096

typedef struct s_termterm
{
	int		ch;
	int		bytes;
	int		cursor;
	int		row;
	int		cur_row;
}			t_term;

static struct termios	g_orig_termios;

void	init(t_term *term);
void	input_cycle(char *input, t_term *term);
int		ft_putc(int c);

/* init */
/* void	kill_process(int sig); */

/*		    Cursor Movement			*/
void	ft_cursor_left(t_term *term);
void	ft_cursor_right(t_term *term);
void	ft_cursor_up(t_term *term);
void	ft_cursor_down(t_term *term);
void	ft_cursor_beginning(int *cur);
void	ft_cursor_end(int *cur, int *bytes);
void	alt_mv_left(int *cursor, char *input);
void	alt_mv_right(int *cursor, char *input, int *bytes);

/*				 Utils				*/
int		get_input(void);
void	print_trail(char *input, t_term *term);
void	clear_trail(void);

/*		      BITS Shifting			*/
void	insertion_shift(char *input, t_term *term);
void	deletion_shift(char *input, t_term *term, int mode);

/*		   Input Functions			*/
void	ft_cursor_mv(t_term *term);
void	esc_parse(char *input, t_term *term);
void	init_var(int *c, int *bytes, int *cur, int *quote);


#endif
