/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnieto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:31:54 by fnieto            #+#    #+#             */
/*   Updated: 2016/02/04 23:48:55 by fnieto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <string.h>
# include "fred_gl.h"

# define MLX_CORE	0
# define MLX_WINDOW	1
# define MLX_FRAME	2
# define F_RES		3
# define F_FILEPTR	4
# define F_MAPPTR	5
# define C_TRANS	6
# define C_ANGLS	7
# define C_HEIGHT	8
# define C_ZOOM		9
# define C_SHADER	10

# define GV(i)		(*var(i))
# define SV(i, val)	(*var(i) = (t_type)(val))

# define SHADERS	{&palette_height, &height, &sphere, &pass_shader}

typedef	struct		s_map
{
	t_buffer	*buf;
	t_vec2		height;
	t_list		*cur;
}					t_map;

void				puterr(int colored, char *text);
t_map				map_to_vert_buff(t_list *map);
t_list				*get_map_data(char *file);
t_list				*ft_str_split_lst(const char *src, const char div);
int					pass_shader(t_shader_info i);
int					height(t_shader_info i);
int					sphere(t_shader_info i);
int					palette_height(t_shader_info i);

t_map				map(t_vec4 dims);
t_vertex			get_vertex(t_map map, size_t x, size_t y);
void				set_vertex(t_map map, size_t x, size_t y, t_vertex v);

void				init_verts(t_map *b);

t_type				*var(int i);
void				init_controls(t_vec2 map);

#endif
