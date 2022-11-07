/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_lines_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:34 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/07 12:39:22 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

void	remove_nl_addr(t_term *term, size_t row)
{
	size_t	i;
	size_t	j;
	char	**new_array;

	i = -1;
	j = -1;
	new_array = (char **)ft_memalloc(sizeof(char *) * term->total_row + 1);
	while (term->nl_addr[++i])
	{
		if (i != row)
			new_array[++j] = term->nl_addr[i];
	}
	new_array[++j] = NULL;
	ft_memdel((void **)&term->nl_addr);
	term->nl_addr = new_array;
}

size_t	get_prompt_len(t_term *term, size_t row)
{
	size_t	prompt_len;

	prompt_len = 0;
	if (!row)
		prompt_len = term->prompt_len;
	else if (is_prompt_line(term, row))
		prompt_len = term->m_prompt_len;
	return (prompt_len);
}

char	*is_prompt_line(t_term *term, size_t row)
{
	if (!row || term->nl_addr[row][-1] == '\n'
		|| term->nl_addr[row][-1] == '\\')
		return (term->nl_addr[row]);
	return (NULL);
}

void	update_nl_addr_del(t_term *term)
{
	size_t	row;

	row = term->c_row + 1;
	while (term->nl_addr[row])
	{
		if (is_prompt_line(term, row))
			term->nl_addr[row] = &term->nl_addr[row][-1];
		row++;
	}
}

void	update_nl_addr(char *input, t_term *term, int num)
{
	size_t		i;

	if (term->nl_addr[term->c_row + 1])
	{	
		i = term->c_row;
		while (++i <= term->total_row)
			term->nl_addr[i] = &term->nl_addr[i][num];
	}
	if (!term->index)
		term->nl_addr[0] = &input[0];
}
