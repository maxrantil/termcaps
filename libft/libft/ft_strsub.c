/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:31:50 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 16:05:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ss;

	if (!s)
		return (NULL);
	i = 0;
	ss = ft_strnew(len);
	while (i < len)
		ss[i++] = s[start++];
	return (ss);
}
