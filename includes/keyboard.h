/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 13:44:08 by mrantil          ###   ########.fr       */
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

# define BUFFSIZE   4096

typedef struct s_termterm
{
	int		ch;
	int		col;
	int		cursor;
	int		row;
	int		cur_row;
}			t_term;

static struct termios	g_orig_termios;

void	init(t_term *term);
void	input_cycle(t_term *term, char *input);
int		ft_putc(int c);
void	ft_clearscreen(void);
void	ft_setcursor(int row, int col);

/* init */
/* void	kill_process(int sig); */

/*		    Cursor Movement			*/
void	ft_cursor_left(t_term *term);
void	ft_cursor_right(t_term *term);
void	ft_cursor_up(t_term *term);
void	ft_cursor_down(t_term *term);
void	ft_cursor_beginning(int *cur);
void	ft_cursor_end(int *cur, int *col);
void	alt_mv_left(int *cursor, char *input);
void	alt_mv_right(int *cursor, char *input, int *col);

/*				 Utils				*/
int		get_input(void);
void	print_trail(t_term *term, char *input);
void	clear_trail(void);

/*		      BITS Shifting			*/
void	insertion_shift(t_term *term, char *input);
void	deletion_shift(char *input, t_term *term, int mode);

/*		   Input Functions			*/
void	ft_cursor_mv(t_term *term);
void	esc_parse(t_term *term, char *input);
void	init_var(int *c, int *col, int *cur, int *quote);


#endif
