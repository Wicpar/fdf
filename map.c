/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 11:40:11 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/19 17:03:10 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

t_vec2		map_dim(char *file)
{
	int		fd;
	t_vec2	dim;
	size_t	cnt;
	char	*tmp;
	char	*i;

	dim = vec2(1, 0);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &tmp) > 0)
	{
		i = tmp;
		cnt = 0;
		while (*i)
		{
			if (*i && *i == ' ' && i[1] && i[1] != ' ')
				cnt++;
		}
		free(tmp);
		if (dim.x == 0)
			dim.x = cnt;
		else if (dim.x > 0 && dim.x != cnt)
			dim.x = -1;
		dim.y++;
	}
	close(fd);
	return (dim);
}
