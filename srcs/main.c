/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/14 08:53:58 by mbarutel         ###   ########.fr       */
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

static void	input_cycle(char *input, int *bytes, int *cur, int *ch)
{
	int		quote;

	quote = 0;
	while (*ch != -1)
	{
		*ch = get_input();
		if (*ch == D_QUOTE || *ch == S_QUOTE)
			quote_count(&quote, ch);
		if (*ch == KILL)
			kill_process(*ch);
		else if (*ch == ENTER && !quote)
			return ;
		else if (*ch == CTRL_D && *cur < *bytes)
			delete(input, bytes, cur);
		else if (*ch == BACKSPACE && *cur > 0)
			backspace(input, bytes, cur);
		if (*ch == ESCAPE)
			esc_parse(input, bytes, cur, ch);
		if (isprint(*ch) || (*ch == ENTER && quote))
		{
			char_print(input, bytes, cur, *ch);
			if (*ch == ENTER && quote)
				write(1, "> ", 2);
		}
	}
}

int	ft_termcaps(char *input)
{
	int		ch;
	int		bytes;
	int		cursor;

	ch = 0;
	bytes = 0;
	cursor = 0;
	ft_memset(input, '\0', BUFFSIZE);
	if (!init_raw())
	{
		ft_putstr_fd("error, raw mode\n", STDERR_FILENO);
		exit(1);
	}
	input_cycle(input, &bytes, &cursor, &ch);
	if (ch == -1)
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
