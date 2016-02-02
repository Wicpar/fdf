/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:31:54 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/02 21:11:49 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <string.h>
# include "fred_gl.h"

typedef	struct		s_param
{
	t_vec2		res;
	char		*file;
}					t_param;

extern void			*g_mlx_core;
extern void			*g_mlx_window_main;
extern t_mat4		g_camera;

void				puterr(int colored, char *text);
t_buffer			*map_to_vert_buff(t_list *map);
t_list				*get_map_data(char *file);
t_list				*ft_str_split_lst(const char *src, const char div);
int					pass_shader(t_shader_info i);
int					funky_height_shader(t_shader_info i);

#endif
