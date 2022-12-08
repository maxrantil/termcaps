/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:04:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/12/08 13:34:08 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/*
 * It's called at the end of the main loop, and it handles the newline
 * character, the history, and the
 * input copy
 *
 * @param t the term struct
 */
void	ft_end_cycle(t_term *t)
{
	if (t->bytes)
	{
		ft_strclr(t->history_buff);
		// ft_memcpy(t->history_buff, t->inp, ft_strlen(t->inp));
		ft_nl_removal(t);
		// ft_putendl(t->history_buff);
		ft_putchar('\n');
		vec_push(&t->v_history, t->history_buff);
	}
	if (!ft_strncmp(t->inp, "history", 7)) // I think this should be a built in
		ft_history(t);
	ft_memdel((void **)&t->nl_addr);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
	if (t->input_cpy)
		ft_strdel(&t->input_cpy);
}
