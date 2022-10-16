/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 08:37:51 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAPS_H
# define TERMCAPS_H

# include "libft.h"
# include <termcap.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
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

typedef struct s_termcap
{
	int		ch;
	int		bytes;
	int		cursor;
	int		row;
	int		cur_row;
}			t_termcap;

static struct termios	g_orig_termios;

/* init */
int		init_raw(void);
void	disable_raw_mode(void);
void	kill_process(int sig);

/*		    Cursor Movement			*/
void	cursor_left(t_termcap *cap);
void	cursor_right(t_termcap *cap);
void	cursor_up(t_termcap *cap);
void	cursor_down(t_termcap *cap);
void	alt_mv_left(int *cursor, char *input);
void	alt_mv_right(int *cursor, char *input, int *bytes);
void	cursor_beginning(int *cur);
void	cursor_end(int *cur, int *bytes);

/*				 Utils				*/
int		get_input(void);
void	print_trail(char *input, t_termcap *cap);
void	clear_trail(void);

/*		      BITS Shifting			*/
void	insertion_shift(char *input, t_termcap *cap);
void	deletion_shift(char *input, t_termcap *cap, int mode);

/*		   Input Functions			*/
void	cursor_mv(t_termcap *cap);
void	backspace(char *input, t_termcap *cap);
void	delete(char *input, t_termcap *cap);
void	esc_parse(char *input, t_termcap *cap);
void	init_var(int *c, int *bytes, int *cur, int *quote);
void	char_print(char *input, t_termcap *cap);

#endif
