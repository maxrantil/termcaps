/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/12 09:53:28 by mbarutel         ###   ########.fr       */
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
		write(STDOUT_FILENO, "^C", 2);
		disable_raw_mode();
		kill(getpid(), SIGINT);
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

int	main(void)
{
	int		c;
	int		bytes;
	int		cursor;
	char	input[1096];

	c = 0;
	bytes = 0;
	cursor = 0;
	memset(input, '\0', 1096);
	if (init_raw() < 0)
	{
		ft_putstr_fd("error, raw mode\n", STDERR_FILENO);
		exit(1);
	}
	while (c != -1)
	{
		c = get_input();
		if (c == KILL)
			kill_process(c);
		else if (c == ENTER)
			break ;
		else if (c == CTRL_D && cursor < bytes)
			delete(input, &bytes, &cursor);
		if (c == ESCAPE)
			cursor_mv(input, &bytes, &cursor, c);
		if (c == BACKSPACE && cursor > 0)
			backspace(input, &bytes, &cursor);
		if (isprint(c))
			char_print(input, &bytes, &cursor, c);
	}
	/*			Displaying Output					*/
	ft_putchar('\n');
	ft_putstr_fd(input, STDOUT_FILENO);
	ft_putchar('\n');
	/*			Displaying Output					*/
	if (c == -1)
		ft_putstr_fd("error, read\n", STDERR_FILENO);
	disable_raw_mode();
	return (0);
}
