/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:38:04 by mrantil           #+#    #+#             */
/*   Updated: 2022/10/25 08:51:33 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

/**
 * It prints the history of the terminal with the help of the vector
 * and the function vec_get.
 * @param term The terminal structure.
 */
void	ft_history(t_term *term)
{
	size_t	num_incr;

	write(1, "\n", 1);
	num_incr = 0;
	while (++num_incr < term->v_history.len)
		ft_printf("%4d  %s\n", num_incr, \
		(char *)vec_get(&term->v_history, num_incr - 1));
}
