/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/13 06:03:38 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/04 13:06:09 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <string.h>
# define BUFF_SIZE 32

typedef	struct		s_fd
{
	int				fd;
	char			**buf;
}					t_fd;

int					get_next_line(int const fd, char **line);

#endif
