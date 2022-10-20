/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/20 17:11:15 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

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
	ft_run_capability("ti");
	ft_run_capability("cl");
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

	ft_init(&term);
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
		ft_input_cycle(&term, input);
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
	char	input[BUFFSIZE];

	ft_keyboard(input);
	return (0);
}
