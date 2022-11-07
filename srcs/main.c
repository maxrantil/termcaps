/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/07 16:21:38 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
**	If optional_actions is TCSAFLUSH, the change shall occur after all output
**	written to fildes is transmitted, and all input so far received but not
**	read shall be discarded before the change is made.
*/
static struct termios	init_raw(struct termios	orig_termios)
{
	struct termios	raw;

	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
	{
		write(2, "error tcgetattr\n", 16);
		exit(1);
	}
	raw = orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	raw.c_iflag &= ~(IXON | BRKINT);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		write(2, "error tcsetattr\n", 16);
		exit(1);
	}
	ft_run_capability("ti");
	ft_run_capability("cl");
	return (orig_termios);
}

//why doesnt this work without being a static in same file???
static void	ft_disable_raw_mode(struct termios	orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
	ft_run_capability("te");
}

static int	ft_keyboard(char *input) //more then 25 lines!
{
	struct termios	orig_termios;
	t_term			term;
	int				status;
	char			*termtype;
	char			term_buffer[2048];

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
		init_raw(orig_termios);
		ft_input_cycle(&term, input);
		ft_history_write_to_file(&term);
		ft_disable_raw_mode(orig_termios);
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
