/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:23:30 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/09 22:03:27 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

struct	s_img;
struct	s_win;
struct	s_scene;
struct	s_camera;
struct	s_amb_light;
struct	s_light;
struct	s_sphere;
struct	s_plane;
struct	s_cylinder;
struct	s_coordinate;
struct	s_plane_equation;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_vec4
{
	float	t;
	t_vec	child;
}	t_vec4;

typedef struct s_plane_equation
{
	t_vec	abc;
	float	d;
}	t_pln_equ;

typedef struct s_plane
{
	t_vec		pos;
	t_vec		orientation;
	t_vec		color;
	int			n_planes;
	t_pln_equ	equation;
}	t_plane;
typedef struct s_sphere
{
	t_vec		center;
	float		diameter;
	t_vec		color;
	int			n_spheres;
}	t_sphere;

typedef struct s_cylinder
{
	t_vec		pos;
	t_vec		orientation;
	float		diameter;
	float		height;
	t_vec		color;
	int			n_cylinders;
	t_vec		pos_top ;
	t_vec		vec_height;
	float		in_cylinder;
}	t_cylinder;
typedef struct s_light
{
	t_vec	pos;
	float	brightness;
	t_vec	color;
}	t_light;
typedef struct s_camera
{
	t_vec	view_point;
	t_vec	orientation;
	t_vec	xyz_angles;
	float	view_field;
}	t_camera;
typedef struct s_amb_light
{
	float	ratio;
	t_vec	color;
}	t_amb_light;
// hold image related information
typedef struct s_img
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				hight;
	int				zoom;
	int				x_pos;
	int				y_pos;
	struct s_sphere	test;
	struct s_win	*win;
	struct s_scene	*scene;
}	t_img;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
}	t_win;

typedef struct s_scene
{
	t_win		*win;
	t_camera	camera;
	t_amb_light	amb_light;
	t_light		light;
	t_sphere	*spheres;
	t_plane		*plane;
	t_cylinder	*cylinder;
	int			n_spheres;
	int			n_planes;
	int			n_cylinders;
	int			error_code;
	int			number_of_shapes;
}	t_scene;

typedef struct parsing_kit
{
	int		i;
	t_list	*tmp;
	int		start;
	int		end;
	int		last_end;
	char	flag;
	int		parse_error_code;
	int		line_len;
	char	*line;
}	t_parsing_kit;

typedef struct ray_trace_kit
{
	int		color;
	t_vec	dir;
	float	aspectratio;
	float	invwidth;
	float	invheight;
	float	angle;
	float	new_x;
	float	new_y;
	int		x;
	int		y;
}	t_ray_trace_kit;
#endif