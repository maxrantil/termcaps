/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:15:06 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 15:28:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_strlcat(char *dst, const char *src, ssize_t dstsize)
{
	ssize_t	dst_strlen;
	ssize_t	src_strlen;
	ssize_t	ret;

	dst_strlen = ft_strlen(dst);
	src_strlen = ft_strlen(src);
	ret = dst_strlen + src_strlen;
	if (dst_strlen > dstsize)
		return (src_strlen + dstsize);
	while (dst_strlen < dstsize - 1 && *src)
		dst[dst_strlen++] = *src++;
	dst[dst_strlen] = '\0';
	return (ret);
}
