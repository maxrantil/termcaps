/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 08:36:38 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

static void	disable_raw_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_orig_termios);
}

static void	kill_process(int sig)
{
	if (sig == 3)
	{
		disable_raw_mode();
		kill(getpid(), SIGINT); //should not kill just give prompt again
	}
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
	return (1);
}

int	ft_termcaps(char *input)
{
	int		c;
	int		bytes;
	int		cursor;
	int		quote;

	ft_memset(input, '\0', BUFFSIZE);
	init_var(&c, &bytes, &cursor, &quote);
	if (!init_raw())
	{
		ft_putstr_fd("error, raw mode\n", STDERR_FILENO);
		exit(1);
	}
	while (c != -1)
	{
		c = get_input();
		if (c == D_QUOTE || c == S_QUOTE)
			quote_count(&quote, &c);
		if (c == KILL)
			kill_process(c);
		else if (c == ENTER && !quote)
			break ;
		else if (c == CTRL_D && cursor < bytes)
			delete(input, &bytes, &cursor);
		else if (c == BACKSPACE && cursor > 0)
			backspace(input, &bytes, &cursor);
		if (c == ESCAPE)
			esc_parse(input, &bytes, &cursor, &c);
		if (isprint(c) || (c == ENTER && quote))
			char_print(input, &bytes, &cursor, c);
	}
	if (c == -1)
		ft_putstr_fd("error, read\n", STDERR_FILENO);
	disable_raw_mode();
	return (0);
}

int	main(void)
{
	char	input[BUFFSIZE];

	ft_termcaps(input);
	/*			Displaying Output					*/
	ft_putchar('\n');
	ft_putstr_fd(input, STDOUT_FILENO);
	ft_putchar('\n');
	/*			Displaying Output					*/
	return (0);
}
