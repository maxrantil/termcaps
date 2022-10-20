#include <termterm.h>
#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <limits.h>
# include <ctype.h>

static struct termios	g_orig_termios;

static int	ft_putc(int c)
{
	return (write(1, &c, 1));
}

static void clearscreen(void)
{
	char *cl;
	
	cl = tgetstr("cl", NULL);
	if (cl == NULL)
		printf("Sorry, I cannot clear the screen...");
	else 
		tputs(cl, 1, ft_putc);
}

static int	init_raw(void)
{
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &g_orig_termios) == -1)
		return (0);
	raw = g_orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	raw.c_iflag &= ~(IXON | BRKINT);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1)
		return (0);
	tputs(tgetstr("ti", NULL), 1, ft_putc);
	clearscreen();
	return (1);
}

static void	ft_disable_raw_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
	tputs(tgetstr("te", NULL), 1, ft_putc);
}

static void	sig_handler(int num)
{
	write(1, "working\n", 8);
	num += '0';
	write(1, &num, 1);
	write(1, "\n", 1);
}

void setcursor(int x, int y)
{
	char *cm; // cursor move sequence
		
	cm = tgetstr("cm", NULL);
	tputs(tgoto(cm, x, y), 1, ft_putc);
}

static int	ft_get_input()(void)
{
	int	c;

	c = 0;
	read(STDIN_FILENO, &c, 1);
	return (c);
}

static void	input_cycle(void)
{
	char	input[2048];
	int		outchar;
	int		x;
	int		y;

	memset(input, '\0', 2048);
	x = 0;
	y = 0;
	while (42)
	{
		outchar = ft_get_input()();
		if (outchar == 3) //ctrl + c
		{
			signal(SIGINT, sig_handler); //need to know more about this
			break ;
		}
		else if (outchar == 4) //ctrl + d
		{
			clearscreen();
			x = 0;
		}
		else if (outchar == 10) //enter
		{
			x = 0;
			setcursor(x, ++y);
		}
		/* else if (outchar == 27) //esc
		{
			ft_esc_parse(term, input);
		} */
		else //print and cm
		{
			ft_putc(outchar);
			input[x] = outchar;
			setcursor(x++, y);
		}
	}
}

int main()
{
	char	term_buffer[2048];
	char	*termtype;
	int		status;

	status = tgetent(term_buffer, "ANSI");
	termtype = getenv("TERM");
	if (termtype == NULL)
	{
		printf("could not get the TERM env\n");
		exit(1);
	}
	status = tgetent(term_buffer, termtype);
	if (status > 0)
	{
		if (!init_raw())
		{
			printf("error, raw mode\n", STDERR_FILENO);
			exit(1);
		}	
		input_cycle();
		ft_disable_raw_mode();
	}
	else
	{
		printf("error, tgetent()\n");
		exit(1);
	}
	return 0;
}