/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_lines_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:34 by mbarutel          #+#    #+#             */
/*   Updated: 2022/10/27 20:08:02 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	nl_addr_reset(t_term *term, char *input)
{
	size_t	j;
	size_t	i;

	ft_memdel((void **)&term->nl_addr);
	term->nl_addr = (char **)ft_memalloc(sizeof(char *) * (term->total_row + 2));
	j = 0;
	i = -1;
	while (++i < term->bytes)
		if (!i || input[i] == '\n' || input[i] == '\\' || i == (term->ws_col - 1))
			term->nl_addr[j++] = &input[i + 1];
	term->nl_addr[j] = NULL;
}

void	update_nl_addr(char *input, t_term *term, int num)
{
	size_t		i;
	size_t		len;

	if (!term->c_row)
		len = term->prompt_len + (term->nl_addr[term->c_row] - term->nl_addr[term->c_row + 1]);
	else
		len = term->m_prompt_len + (term->nl_addr[term->c_row] - term->nl_addr[term->c_row + 1]);
	if (term->nl_addr[term->c_row + 1])
	{	
		i = term->c_row + 1;
		while (i <= term->total_row)
		{
			if (len <= term->ws_col)
				term->nl_addr[i] = &term->nl_addr[i][num];
			i++;
		}
	}
	if (!term->indx)
		term->nl_addr[0] = &input[0];
}

void	get_nl_addr(t_term *term, char *input)
{
	int		index;
	char	**fresh_array;

	index = -1;
	fresh_array = NULL;
	if (!term->nl_addr)
	{
		term->nl_addr = (char **)ft_memalloc(sizeof(char *) * 2);
		term->nl_addr[++index] = &input[term->indx];
		term->nl_addr[++index] = NULL;
	}
	else
	{
		fresh_array = (char **)ft_memalloc(sizeof(char *) * (term->total_row + 2));
		while (term->nl_addr[++index])
			fresh_array[index] = term->nl_addr[index];
		fresh_array[index++] = &input[term->indx];
		fresh_array[index] = NULL;
		ft_memdel((void **)&term->nl_addr);
		term->nl_addr = fresh_array;
	}
}
