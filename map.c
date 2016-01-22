/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:40:11 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/22 17:01:34 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

t_vec3		map_dim(char *file)
{
	int		fd;
	t_vec3	dim;
	size_t	cnt;
	char	*tmp;
	size_t	i;

	dim = vec3(1, 0, 0);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &tmp) > 0)
	{
		i = -1;
		cnt = 1;
		while (tmp[++i])
			if (tmp[i] != ' ' && tmp[i + 1] == ' ')
				cnt++;
		free(tmp);
		if (cnt > dim.x)
			dim.x = cnt;
		dim.y++;
	}
	close(fd);
	return (dim);
}

t_buffer	*map_to_buff(char *file)
{
	t_vec3		dims;
	t_buffer	*new;
	int			fd;
	char		*tmp;
	char		**tbl;

	dims = map_dim(file);
	if (dims.y == 0)
		return (0);
	new = buffer(dims.x, dims.y, sizeof(void*));
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &tmp) > 0)
	{
		tbl = ft_strsplit(tmp, ' ');
		ft_memcpy(new->buf + (size_t)(dims.z * dims.x), tbl, dims.x);
		free(tmp);
		free(tbl);
		dims.z++;
	}
	close(fd);
	return (new);
}
