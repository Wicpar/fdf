/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:36:19 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/06 13:09:46 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

#include <stdio.h>
#include <math.h>

int		main(int ac, char **av)
{
	if (ac == 2)
		ft_putendl(av[1]);
	double i = 0;
	while (i < PI * 4)
	{
		printf("%lf : %lf\n", sin(i), SIN(i));
		i += 0.01;
	}
}
