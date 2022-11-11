/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 10:52:49 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 15:28:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_arrfree(void ***arr, ssize_t len)
{
	ssize_t	i;

	if (!arr || !len)
		return ;
	i = 0;
	while (i < len)
	{
		if (*((*arr) + i))
		{
			free(*((*arr) + i));
			*((*arr) + i) = NULL;
		}
		i++;
	}
	free(*arr);
	*arr = NULL;
}
