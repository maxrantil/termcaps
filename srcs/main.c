/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/06 17:26:14 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
**	If optional_actions is TCSAFLUSH, the change shall occur after all output 
**	written to fildes is transmitted, and all input so far received but not
**	read shall be discarded before the change is made.
*/
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
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
		return (0);
	ft_run_capability("ti");
	ft_run_capability("cl");
	return (1);
}

static void	ft_disable_raw_mode(void) //why doesnt this work without being a static in same file???
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
	ft_run_capability("te");
}

static int	ft_keyboard(char *input)
{
	t_term		term;
	int			status;
	char		*termtype;
	char		term_buffer[2048];

	ft_init(&term, input);
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
			ft_putendl_fd("error, raw mode", STDERR_FILENO);
			exit(1);
		}
		ft_input_cycle(&term, input);
		ft_history_write_to_file(&term);
		ft_disable_raw_mode();
		ft_putendl_fd(input, STDOUT_FILENO);
		ft_memset(input, '\0', BUFFSIZE);
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
