/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrantil <mrantil@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:07:48 by mrantil           #+#    #+#             */
/*   Updated: 2022/11/11 15:28:40 by mrantil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "libft.h"

typedef struct s_vec
{
	unsigned char	*memory;
	ssize_t			elem_size;
	ssize_t			alloc_size;
	ssize_t			len;
}	t_vec;

int		vec_new(t_vec *src, ssize_t init_len, ssize_t elem_size);
void	vec_free(t_vec *src);
int		vec_resize(t_vec *src, ssize_t target_size);
void	*vec_get(t_vec *src, ssize_t index);
int		vec_push(t_vec *src, void *elem);

#endif
