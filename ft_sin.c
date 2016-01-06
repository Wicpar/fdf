/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 11:44:49 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/06 13:00:15 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_float		ft_sin_fast(t_float x)
{
	t_float	sin;

	if (x < 0)
		while (x < -PI)
			x += 2 * PI;
	else
		while (x > PI)
			x -= 2 * PI;
	if (x < 0)
		sin = 1.27323954 * x + .405284735 * x * x;
	else
		sin = 1.27323954 * x - 0.405284735 * x * x;
	return (sin);
}

t_float		ft_sin_med(t_float x)
{
	t_float	sin;

	if (x < 0)
		while (x < -PI)
			x += 2 * PI;
	else
		while (x > PI)
			x -= 2 * PI;
	if (x < 0)
		sin = 1.27323954 * x + .405284735 * x * x;
	else
		sin = 1.27323954 * x - 0.405284735 * x * x;
	sin = .225 * (sin * ABS(sin) - sin) + sin;
	return (sin);
}
