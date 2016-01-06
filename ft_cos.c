/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 11:56:17 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/06 12:57:01 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_float		ft_cos_fast(t_float x)
{
	t_float cos;

	x += PI / 2;
	if (x < 0)
		while (x < -PI)
			x += 2 * PI;
	else
		while (x > PI)
			x -= 2 * PI;
	if (x < 0)
		cos = 1.27323954 * x + 0.405284735 * x * x;
	else
		cos = 1.27323954 * x - 0.405284735 * x * x;
	return (cos);
}

t_float		ft_cos_med(t_float x)
{
	t_float cos;

	x += PI / 2;
	if (x < 0)
		while (x < -PI)
			x += 2 * PI;
	else
		while (x > PI)
			x -= 2 * PI;
	if (x < 0)
		cos = 1.27323954 * x + 0.405284735 * x * x;
	else
		cos = 1.27323954 * x - 0.405284735 * x * x;
	cos = .225 * (cos * ABS(cos) - cos) + cos;
	return (cos);
}
