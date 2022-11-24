/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbarutel <mbarutel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:56:52 by mbarutel          #+#    #+#             */
/*   Updated: 2022/11/24 20:34:24 by mbarutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"

static char	*ft_strndup(char *str, size_t n) // Here temporarily. This function should be in libft
{
	char	*res;

	res = ft_memalloc(n + 1);
	if (!res)
		return (NULL);
	ft_strncpy(res, str, n);
	res[n] = '\0';
	return (res);
}

void	ft_copy(t_term *t)
{
	if (t->nl_addr[t->c_row + 1])
		t->clipboard = ft_strndup(t->nl_addr[t->c_row], \
			(size_t)((t->nl_addr[t->c_row + 1] - t->nl_addr[t->c_row]) - 1));
	else
		t->clipboard = ft_strdup(t->nl_addr[t->c_row]);
	ft_setcursor(0, t->ws_row - 1);
	ft_putstr(t->clipboard);
}