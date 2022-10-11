/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:52:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/11 16:48:51 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "termcaps.h"

static void	disableRawMode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

static void kill_process(int sig)
{
	if (sig == 3)
	{
		write(STDOUT_FILENO, "^C", 2);
		disableRawMode();
		kill(getpid(), SIGINT);
	}
}

static void shift_bits(char *input, int i, int cur)
{
    while (&input[i] >= &input[cur])
    {
        input[i] = input[i] ^ input[i + 1];
        input[i + 1] = input[i] ^ input[i + 1];
        input[i] = input[i] ^ input[i + 1];
        i--;
    }
}

static int get_input(void)
{
    int c;

    c = 0;
    read(STDIN_FILENO, &c, 1);
	// printf("code: %s\n", ft_itoa(c));
    return (c);
}

static void backspace(char *input, int *i, int *cur)
{
    int cur_cpy;

    if (*cur == *i)
    {
        i[0]--;
        cur[0]--;
        input[*cur] = '\0';
    }
    else
    {
        cur[0]--;
        cur_cpy = *cur;
        input[cur_cpy] = '\0';
        while (&input[cur_cpy] < &input[*i])
        {
            input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
            input[cur_cpy + 1] = input[cur_cpy] ^ input[cur_cpy + 1];
            input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
            cur_cpy++;
        }
        i[0]--;
    }
}

static int esc_parse(int c)
{
    if (c == '[')
    {
        c = get_input();
        if (c == 'D')
            c = LEFT;
        if (c == 'C')
            c = RIGHT;
    }
    return (c);
}

static int	init_raw(void)
{
	struct termios raw;
	
	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
		return (0);
	raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	raw.c_iflag &= ~(IXON | BRKINT);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) == -1)
		return (0);
	return (1);
}

static void delete(char *input, int *i, int *cur)
{
    int cur_cpy;

    cur_cpy = *cur;
    input[cur_cpy] = '\0';
    while (&input[cur_cpy] < &input[*i])
    {
        input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
        input[cur_cpy + 1] = input[cur_cpy] ^ input[cur_cpy + 1];
        input[cur_cpy] = input[cur_cpy] ^ input[cur_cpy + 1];
        cur_cpy++;
    }
    i[0]--;
}

int main(void)
{
    int     c;
    int     bytes;
    int     cursor;
    char    input[1096];

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
            break;
		else if ( c == CTRL_D && cursor < bytes)
		{
			delete(input, &bytes, &cursor);
            ft_putstr("\033[s");
            ft_putstr("\033[K");
            ft_putstr(&input[cursor]);
            ft_putstr("\033[H");
            ft_putstr("\033[u");
		}
        if (c == ESCAPE)
        {
            c = get_input();
            if (c == '[')
                c = esc_parse(c);
			if (c == 'b')
			{
				alt_mv_left(&cursor, input);
				continue ;
			}
			else if (c == 'f')
			{
				alt_mv_right(&cursor, input);
				continue ;
			}
        }
        if (c == LEFT && cursor)
        {
            cursor--;
            write(1, "\033[1D", 4);
        }
        else if (c == RIGHT && (cursor < bytes))
        {
            cursor++;
            write(1, "\033[1C", 4);
        }
        else if (c == BACKSPACE && cursor >= 0)
        {
            write(1, "\033[1D", 4);
            ft_putstr("\033[K");
            backspace(input, &bytes, &cursor);
            if (input[cursor])
            {
                ft_putstr("\033[s");
                ft_putstr(&input[cursor]);
                ft_putstr("\033[H");
                ft_putstr("\033[u");
            }
        }
        else if (isprint(c))
        {
            write(1, &c, 1);
            if (input[cursor])
            {   
                ft_putstr("\033[K");
                shift_bits(input, bytes, cursor);
            }
            input[cursor++] = c;
            if (input[cursor])
            {
                ft_putstr("\033[s");
                ft_putstr(&input[cursor]);
                ft_putstr("\033[H");
                ft_putstr("\033[u");
            }
            bytes++;
        }
    }
	if (c == ENTER)
	{
		ft_putchar('\n');
		ft_putstr_fd(input, STDOUT_FILENO);
		ft_putchar('\n');
	}
	else if (c == -1)
		ft_putstr_fd("error, read\n", STDERR_FILENO);
	disableRawMode();
    return 0;
}
