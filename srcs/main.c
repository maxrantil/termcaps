/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 12:24:12 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void clearscreen(void)
{
	char *cl;
	
	cl = tgetstr("cl", NULL);
	if (cl == NULL)
		ft_putendl_fd("error, cannot clear the screen", 2);
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

static void	disable_raw_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
	tputs(tgetstr("te", NULL), 1, ft_putc);
}

static int	ft_keyboard(char *input)
{
	t_term		term;
	char		term_buffer[2048];
	char		*termtype;
	int			status;

	init(&term);
	ft_memset(input, '\0', BUFFSIZE);
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
		input_cycle(input, &term);
		disable_raw_mode();
	}
	else
	{
		printf("error, tgetent()\n");
		exit(1);
	}
	return (0);
}

int	main(void)
{
	char	input[BUFFSIZE];  //this should be output instead

	ft_keyboard(input);
	/*			Displaying Output					*/
	ft_putchar('\n');
	ft_putstr_fd(input, STDOUT_FILENO);
	ft_putchar('\n');
	/*			Displaying Output					*/
	return (0);
}
