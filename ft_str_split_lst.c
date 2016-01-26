/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_split_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 18:11:52 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/26 18:22:14 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_str_split_lst(const char *src, const char div)
{
	char	**buf;
	t_list	*new;
	size_t	i;

	buf = ft_strsplit(src, div);
	new = 0;
	i = -1;
	while (buf[++i])
	{
		ft_lstpush(&new, ft_lstnew(buf[i], ft_strlen(buf[i]) + 1));
		ft_memdel((void**)&(buf[i]));
	}
	ft_memdel((void**)&buf);
	return (new);
}
