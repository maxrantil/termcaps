/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deletion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:37:39 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/02 12:45:45 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static void	ft_deletion_shift(char *input, t_term *term, int mode)
{
	int	indx_cpy;

	if (mode == BCK)
		term->indx--;
	indx_cpy = term->indx;
	input[indx_cpy] = '\0';
	while (&input[indx_cpy] < &input[term->bytes])
	{
		input[indx_cpy] = input[indx_cpy] ^ input[indx_cpy + 1];
		input[indx_cpy + 1] = input[indx_cpy] ^ input[indx_cpy + 1];
		input[indx_cpy] = input[indx_cpy] ^ input[indx_cpy + 1];
		indx_cpy++;
	}
	term->bytes--;
}

void	delete(t_term *term, char *input) // Have not properly tested this
{
	ft_deletion_shift(input, term, DEL);
	ft_run_capability("ce");
	ft_print_trail(term, input);
	update_nl_addr(input, term, -1);
}

static void remove_nl_addr(t_term *term, size_t row)
{
	size_t	i;
	size_t	j;
	char	**new_array;

	i = -1;
	j = -1;
	new_array = (char **)ft_memalloc(sizeof(char *) * term->total_row + 1);
	while (term->nl_addr[++i])
	{
		if (i != row) // this might need to take into account the sihifting from deletion for lines without prompt
			new_array[++j] = term->nl_addr[i];
	}
	new_array[++j] = NULL;
	ft_memdel((void **)&term->nl_addr);
	term->nl_addr = new_array;
}

// void	backspace(t_term *term, char *input) // THis removes input[term->indx - 1] work on here
// {
// 	size_t 	row;
// 	size_t	len;

// 	row = get_last_non_prompt_line(term);
// 	if (term->indx && (input[term->indx - 1] == D_QUOTE || input[term->indx - 1] == S_QUOTE))
// 		quote_decrement(input, term);
// 	if ((&input[term->indx] != term->nl_addr[term->c_row]))
// 	{
// 		if (term->c_col == term->ws_col)
// 			term->c_col--;
// 		ft_setcursor(--term->c_col, term->c_row);
// 		ft_run_capability("ce");
// 		ft_deletion_shift(input, term, BCK);
// 	}
// 	else if (term->c_row && (&input[term->indx] == term->nl_addr[term->c_row]) && !is_prompt_line(term, term->c_row)) // when you backspace to the most left byte of the line
// 	{
// 		term->c_col = term->ws_col;
// 		// ft_setcursor(0, term->ws_row - 2);
// 		// ft_run_capability("ce");
// 		ft_setcursor(term->c_col, term->c_row - 1);
// 		ft_run_capability("ce");
// 		if (term->nl_addr[row + 1])
// 			len = term->nl_addr[row + 1] - term->nl_addr[row];
// 		else
// 			len = &input[term->bytes] - term->nl_addr[row];
// 		ft_setcursor(0, term->ws_row - 3);
// 		ft_putnbr(len);
// 		// ft_run_capability("ce");
// 		ft_setcursor(term->c_col, term->c_row - 1);
// 		if (!len)
// 			ft_deletion_shift(input, term, BCK);
// 		remove_nl_addr(term, term->c_row);
// 		term->c_row--;
// 		term->total_row--;
// 	}
// 	if (input[term->indx])
// 		ft_print_trail(term, input);
// }

static void ft_nl_addr_update_delete(t_term *term)
{
	size_t row;

	row = term->c_row + 1;
	while (term->nl_addr[row] && !is_prompt_line(term, row))
		row++;
	while (term->nl_addr[row++])
		term->nl_addr[row - 1] = &term->nl_addr[row - 1][-1];	
}

static size_t get_last_non_prompt_line(t_term *term)
{
	size_t row;

	row = term->c_row;
	while (term->nl_addr[row + 1] && !is_prompt_line(term, row + 1))
		row++;
	return (row);
}

void	backspace(t_term *term, char *input) // THis removes input[term->indx - 1] work on here
{
	size_t 	row;
	size_t	len;

	if (&input[term->indx] == term->nl_addr[term->c_row] && is_prompt_line(term, term->c_row))
		return ;
	row = get_last_non_prompt_line(term);
	if (term->nl_addr[row + 1])
		len = (term->nl_addr[row + 1] - term->nl_addr[row]) - 1;
	else
		len = &input[term->bytes] - term->nl_addr[row];
	if (term->indx && (input[term->indx - 1] == D_QUOTE || input[term->indx - 1] == S_QUOTE))
		quote_decrement(input, term);
	if (!term->c_col)
	{
		term->c_col = term->ws_col;
		ft_setcursor(term->c_col, --term->c_row);
	}
	else
	{
		if (term->c_col == term->ws_col)
			term->c_col--;
		ft_setcursor(--term->c_col, term->c_row);
	}
	if (!len)
	{
		ft_setcursor(0, term->ws_row - 4);
		ft_putstr("CAR");
		ft_setcursor(term->c_col, term->c_row);
		remove_nl_addr(term, row);
		term->total_row--;
	}
	ft_run_capability("ce");
	ft_nl_addr_update_delete(term);
	ft_deletion_shift(input, term, BCK);
	if (input[term->indx])
		ft_print_trail(term, input);
}
