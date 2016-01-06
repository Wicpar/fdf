/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 16:06:01 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/06 16:09:30 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	puterr(int colored, char *text)
{
	if (colored)
		ft_putstr_fd("\033[31m", 2);
	ft_putendl(text ? text : "error");
	if (colored)
		ft_putstr_fd("\033[0m", 2);
	exit(1);
}
