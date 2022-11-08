/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/08 17:15:34 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
**	If optional_actions is TCSAFLUSH, the change shall occur after all output
**	written to fildes is transmitted, and all input so far received but not
**	read shall be discarded before the change is made.
*/
static struct termios	ft_init_raw(void)
{
	struct termios	orig_termios;
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

/**
 * It disables raw mode by setting the terminal attributes to the original terminal attributes
 * 
 * @param orig_termios The original terminal attributes.
 */
static void	ft_disable_raw_mode(struct termios orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
	ft_run_capability("te");
}

static int ft_getent(void)
{
	char	*termtype;
	char	term_buffer[2048];
	int		status;

	termtype = getenv("TERM");
	if (termtype == NULL)
	{
		printf("could not get the TERM env\n");
		exit(1);
	}
	status = tgetent(term_buffer, termtype);
	if (status < 0)
	{
		printf("could not access the termcap data base\n");
		exit(1);
	}
	else if (status == 0)
	{
		printf("could not find the termtype\n");
		exit(1);
	}
	return (status);
}

/**
 * It initializes the terminal,
 * gets the environment variables, sets the terminal to raw mode, and then enters
 * the input cycle
 * 
 * @param input the string that will be modified by the user
 * 
 * @return The return value is the number of bytes read.
 */
static int	ft_keyboard(char *input)
{
	struct termios	orig_termios;
	t_term			term;

	ft_init(&term, input);
	ft_getent();
	orig_termios = ft_init_raw();
	ft_input_cycle(&term, input);
	ft_history_write_to_file(&term);
	ft_disable_raw_mode(orig_termios);
	return (0);
}

/**
 * It takes in a string and sets all the characters to null.
 * 
 * @return The return value is the number of bytes that were written to the file descriptor.
 */
int	main(void)
{
	char	input[BUFFSIZE];

	ft_memset(input, '\0', BUFFSIZE);
	ft_keyboard(input);
	return (0);
}
