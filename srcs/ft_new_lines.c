/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_lines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 13:42:45 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/03 12:46:47 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	create_prompt_line(t_term *term, char *input)
{
	term->c_row++;
	term->total_row++;
	term->c_col = term->m_prompt_len;
	ft_setcursor(0, term->c_row);
	write(1, MINI_PROMPT, term->m_prompt_len);
	if (term->nl_addr[term->c_row])
		add_nl_mid_row(term, input, term->c_row, term->index);
	else
		add_nl_last_row(term, input, term->index);
}

void	add_nl_last_row(t_term *term, char *input, size_t pos)
{
	int		index;
	char	**fresh_array;

	index = -1;
	fresh_array = NULL;
	if (!term->nl_addr)
	{
		term->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		term->nl_addr[++index] = &input[pos];
		term->nl_addr[++index] = NULL;
	}
	else
	{
		fresh_array = (char **)ft_memalloc(sizeof(char *)
				* (term->total_row + 2));
		while (term->nl_addr[++index])
			fresh_array[index] = term->nl_addr[index];
		fresh_array[index++] = &input[pos];
		fresh_array[index] = NULL;
		ft_memdel((void **)&term->nl_addr);
		term->nl_addr = fresh_array;
	}
}

void	add_nl_mid_row(t_term *term, char *input, size_t row, size_t pos)
{
	size_t	i;
	size_t	j;
	char	**new_arr;

	j = 0;
	i = -1;
	new_arr = (char **)ft_memalloc(sizeof(char *) * (term->total_row + 2));
	while (++i <= term->total_row)
	{
		if (i == row)
			new_arr[i] = &input[pos];
		else
			new_arr[i] = term->nl_addr[j++];
	}
	new_arr[i] = NULL;
	ft_memdel((void **)&term->nl_addr);
	term->nl_addr = new_arr;
}
