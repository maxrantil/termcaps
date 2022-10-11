#ifndef TERMCAPS_H
# define TERMCAPS_H

#include "libft.h"
#include <termcap.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>

#define KILL		3
#define CTRL_D		4
#define ESCAPE      0x001b
#define ENTER       0x000a
#define UP          0x0105
#define DOWN        0x0106
#define LEFT        0x0107
// #define CTRL_LEFT   0x0107
#define RIGHT       0x0108
#define BACKSPACE	0x007F
#define TAB			0x0009

static struct termios orig_termios;

void	alt_move(char *input);

#endif
