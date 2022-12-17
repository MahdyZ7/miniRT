/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:23:30 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/18 02:11:24 by ahsalem          ###   ########.fr       */
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

typedef struct t_coordinate
{
	float	x;
	float	y;
	float	z;
}	t_coordinate;
typedef struct s_plane
{
	t_coordinate	position;
	t_coordinate	orientation;
	t_coordinate	color;
}	t_plane;
typedef struct s_sphere
{
	t_coordinate	center;
	float			diameter;
	t_coordinate	color;
}	t_sphere;
typedef struct s_cylinder
{
	t_coordinate	position;
	t_coordinate	orientation;
	float			diameter;
	float			height;
	t_coordinate	color;
}	t_cylinder;
typedef struct s_light
{
	t_coordinate	position;
	float			brightness;
}	t_light;
typedef struct s_camera
{
	t_coordinate	view_point;
	t_coordinate	orientation;
	float			view_field;
}	t_camera;
typedef struct s_amb_light
{
	float			ratio;
	t_coordinate	color;
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
	struct s_win	*win;	
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
}	t_scene;

#endif