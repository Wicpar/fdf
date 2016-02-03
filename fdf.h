/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:31:54 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/03 18:32:32 by fnieto           ###   ########.fr       */
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

typedef	struct		s_map
{
	t_buffer	*buf;
	t_vec2		height;
	t_list		*cur;
}					t_map;

extern void			*g_mlx_core;
extern void			*g_mlx_window_main;
extern t_mat4		g_camera;

void				puterr(int colored, char *text);
t_map				map_to_vert_buff(t_list *map);
t_list				*get_map_data(char *file);
t_list				*ft_str_split_lst(const char *src, const char div);
int					pass_shader(t_shader_info i);
int					funky_height_shader(t_shader_info i);
int					funky_sphere_shader(t_shader_info i);

t_map				map(t_vec4 dims);
t_vertex			get_vertex(t_map map, size_t x, size_t y);
void				set_vertex(t_map map, size_t x, size_t y, t_vertex v);

#endif
