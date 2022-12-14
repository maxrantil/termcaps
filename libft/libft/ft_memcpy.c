/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:10:27 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 16:05:28 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <string.h>

static void	ft_copy_chunks(unsigned char **dst,
		const unsigned char **src, size_t n)
{
	unsigned long		*d;
	const unsigned long	*s;

	d = (unsigned long *)*dst;
	s = (const unsigned long *)*src;
	*dst += n * sizeof(long);
	*src += n * sizeof(long);
	while (n--)
		*d++ = *s++;
}

static void	ft_copy_trail(unsigned char **dst,
		const unsigned char **src, size_t n)
{
	unsigned int	chunk;
	unsigned int	trail;

	chunk = n / sizeof(int);
	trail = n % sizeof(int);
	if (chunk)
		*(*(unsigned int **)dst)++ = *(*(const unsigned int **)src)++;
	if (trail / sizeof(short))
		*(*(unsigned short **)dst)++ = *(*(const unsigned short **)src)++;
	if (n % sizeof(short))
		*(*dst)++ = *(*src)++;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	unsigned int		chunks;
	unsigned int		trail;

	if (n == 0 || dst == src)
		return (dst);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	chunks = n / sizeof(long);
	trail = n % sizeof(long);
	if (chunks)
		ft_copy_chunks(&d, &s, chunks);
	ft_copy_trail(&d, &s, trail);
	return (dst);
}
