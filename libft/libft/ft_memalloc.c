/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:24:28 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 16:05:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = malloc(sizeof(mem) * size);
	if (!mem)
	{
		ft_putstr_fd("error, malloc error\n", STDERR_FILENO);
		exit(1);
	}
	ft_bzero(mem, size);
	return (mem);
}
