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

static void	quote_count(int *quote, int c)
{
	if (!*quote)
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

static void	input_cycle(char *input, t_termcap *cap)
{
	int		quote;

	quote = 0;
	while (cap->ch != -1)
	{
		cap->ch = get_input();
		if (cap->ch == D_QUOTE || cap->ch == S_QUOTE)
			quote_count(&quote, cap->ch);
		if (cap->ch == KILL)
			kill_process(cap->ch);
		else if (cap->ch == ENTER && !quote)
			return ;
		else if (cap->ch == CTRL_D && cap->cursor < cap->bytes)
			delete(input, cap);
		else if (cap->ch == BACKSPACE && cap->cursor > 0)
			backspace(input, cap);
		if (cap->ch == ESCAPE)
			esc_parse(input, cap);
		if (isprint(cap->ch) || (cap->ch == ENTER && quote))
		{
			char_print(input, cap);
			if (cap->ch == ENTER && quote)
			{
				write(1, "> ", 2);
				cap->row++; 
				cap->cur_row++;
				//cap->bytes += 3; ???? lets talk about this
			}
		}
		if (cap->ch == -1)
			ft_putstr_fd("error, read\n", STDERR_FILENO);
	}
}

int	ft_termcaps(char *input)
{
	t_termcap	cap;

	cap.ch = 0;			//make funciton
	cap.bytes = 0;
	cap.cursor = 0;
	cap.row = 0;
	cap.cur_row = 0;
	ft_memset(input, '\0', BUFFSIZE);
	if (!init_raw())
	{
		ft_putstr_fd("error, raw mode\n", STDERR_FILENO);
		exit(1);
	}
	input_cycle(input, &cap);
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
