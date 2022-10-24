/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_esc_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:31:54 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/20 16:52:30 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_cursor_beginning(t_term *term)
{
	if (!term->c_row)
	{
		term->c_col = 3;
		term->indx = 0;
	}
	else
	{
		term->c_col = 2;
		term->indx = term->new_line_addr[term->c_row] - term->new_line_addr[0];
	}
	ft_setcursor(term->c_col, term->c_row);
}

static char	*get_str_end(char *str)
{
	while (*str)
		str++;
	return (str + 1);
}

static void	ft_cursor_end(t_term *term)
{
	if (term->new_line_addr[term->c_row + 1])
		term->c_col = term->new_line_addr[term->c_row + 1] - term->new_line_addr[term->c_row];
	else
	{
		if (!term->c_row)
		{
			term->c_col = (get_str_end(term->new_line_addr[term->c_row]) -  term->new_line_addr[term->c_row]) + 2;
			term->indx = term->c_col - 3;
		}
		else
		{
			term->c_col = (get_str_end(term->new_line_addr[term->c_row]) -  term->new_line_addr[term->c_row]) + 1;
			term->indx = (get_str_end(term->new_line_addr[term->c_row]) - term->new_line_addr[0]) - 1;
		}
	}
	ft_setcursor(term->c_col, term->c_row);
}

static void	shift_arrow(t_term *term)
{
	if (term->ch == 'D' && term->bytes)
		ft_cursor_beginning(term);
	if (term->ch == 'C' && term->c_col < term->bytes)
		ft_cursor_end(term);
}

static void	vert_cur_mv(char *input, t_term *term)
{
	int	len;
	int index;

	len = 0;
	index = 0;
	if (term->ch == 'A' && term->c_row) // UP
	{
		index = &input[term->indx] - term->new_line_addr[term->c_row];
		len = term->new_line_addr[term->c_row] - term->new_line_addr[term->c_row - 1];
		if (index < len)
		{
			if (term->c_row == 1)
			{
				if (!index)
					term->c_col++;
				else
					index--;
			}
			term->indx = (&term->new_line_addr[term->c_row - 1][index] - term->new_line_addr[0]);
			term->c_row--;
		}
		else
		{
			if (term->c_row == 1)
			{
				term->c_col = len + 2;
				term->indx = (term->new_line_addr[term->c_row] - term->new_line_addr[0]) - 1;
			}
			else if (term->c_row > 1)
			{
				term->c_col = len + 1;
				term->indx = (term->new_line_addr[term->c_row] - term->new_line_addr[0]) - 1;
			}
			term->c_row--;
		}
		ft_setcursor(term->c_col, term->c_row);
	}
	if (term->ch == 'B' && term->c_row < term->total_row) // DOWN Look into this and confirm INDEX and len
	{
		index = &input[term->indx] - term->new_line_addr[term->c_row];
		if (term->c_row < term->total_row - 1)
			len = term->new_line_addr[term->c_row + 2] - term->new_line_addr[term->c_row + 1];
		else
			len = (get_str_end(term->new_line_addr[term->c_row + 1]) - term->new_line_addr[term->c_row + 1]);
		if (index < len) // This has a problem when moving down the last line
		{
			if (!term->c_row)
				term->indx = &term->new_line_addr[term->c_row + 1][index] - term->new_line_addr[0] + 1;
			else
				term->indx = &term->new_line_addr[term->c_row + 1][index] - term->new_line_addr[0];
			term->c_row++;
		}
		else // when cursur is greater position than lower line
		{
			term->c_col = len + 1;
			if (term->c_row < (term->total_row - 1))
				term->indx = &term->new_line_addr[term->c_row + 2][-1] - term->new_line_addr[0];
			else
				term->indx = (get_str_end(term->new_line_addr[term->c_row + 1]) - term->new_line_addr[0]) - 1;
			term->c_row++;
		}
		ft_setcursor(term->c_col, term->c_row);
	}
	term->ch = 0;
}

void	ft_esc_parse(t_term *term, char *input)
{
	term->ch = ft_get_input();
	if (term->ch == '[')
	{
		term->ch = ft_get_input();
		if (term->ch == 'D' || term->ch == 'C' || term->ch == 'A' || term->ch == 'B')
		{
			ft_cursor_mv(input, term);
		}
		if (term->ch == 49)
			ft_alt_cursor_mv(term, input);
		if (term->ch == 'H' && term->bytes)
		{
			ft_cursor_beginning(term);
		}
		if (term->ch == 'F' && term->c_col < term->bytes)
			ft_cursor_end(term);
		if (term->ch == '2')
		{
			term->ch = ft_get_input();
			if (term->ch == 'A' || term->ch == 'B')
				vert_cur_mv(input, term);
			else
				shift_arrow(term);
		}
	}
	if (term->ch == 98 || term->ch == 102)
		ft_alt_cursor_mv(term, input);
	term->ch = 0;
}
