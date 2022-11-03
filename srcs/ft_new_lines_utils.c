/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_lines_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:26:34 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/03 15:49:44 by mbarutel         ###   ########.fr       */
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

char	*is_prompt_line(t_term *term, size_t row)
{
	if (!row || term->nl_addr[row][-1] == '\n'
		|| term->nl_addr[row][-1] == '\\')
		return (term->nl_addr[row]);
	return (NULL);
}

void	nl_addr_reset(t_term *term, char *input)
{
	size_t	j;
	size_t	i;

	ft_memdel((void **)&term->nl_addr);
	term->nl_addr = (char **)ft_memalloc(sizeof(char *)
			* (term->total_row + 2));
	j = 0;
	i = -1;
	while (++i < term->bytes)
		if (!i || input[i] == '\n'
			|| input[i] == '\\' || i == (term->ws_col - 1))
			term->nl_addr[j++] = &input[i + 1];
	term->nl_addr[j] = NULL;
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
