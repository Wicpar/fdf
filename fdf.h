/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:31:54 by fnieto            #+#    #+#             */
/*   Updated: 2016/01/11 18:22:54 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <string.h>
# include "fred_gl.h"

# define PI 3.141592653589793238L

typedef	struct		s_param
{
	t_vec2		res;
	char		*file;
}					t_param;

extern void			*g_mlx_core;
extern void			*g_mlx_window_main;
extern t_mat4		g_camera;

void				puterr(int colored, char *text);

#endif
