/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 09:51:26 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/12 09:54:05 by mbarutel         ###   ########.fr       */
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
# define ESCAPE      0x001b
# define ENTER       0x000a
# define UP          0x0105
# define DOWN        0x0106
# define LEFT        0x0107
# define RIGHT       0x0108
# define BACKSPACE	0x007F
# define TAB			0x0009

# define DEL			0x0000
# define BCK			0x0001

static struct termios	g_orig_termios;

/*		    Cursor Movement			*/
void	cursor_left(int *cursor);
void	cursor_right(int *cursor);
void	alt_mv_left(int *cursor, char *input);
void	alt_mv_right(int *cursor, char *input, int *i);

/*				 Utils				*/
int		get_input(void);
void	print_trail(char *input, int cursor);
void	clear_trail(void);

/*		      BITS Shifting			*/
void	insertion_shift(char *input, int *i, int cur);
void	deletion_shift(char *input, int *i, int *cur, int mode);

/*		   Input Functions			*/
void	cursor_mv(char *input, int *i, int *cur, int c);
void	char_print(char *input, int *i, int *cur, int c);
void	backspace(char *input, int *i, int *cur);
void	delete(char *input, int *i, int *cur);

#endif
