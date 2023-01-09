/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:09:01 by ayassin           #+#    #+#             */
/*   Updated: 2023/01/09 16:44:21 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINIRT_H
# define MINIRT_H
# include "minilibx_macos/mlx.h"
# include "minilibx_linux/mlx.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "structs.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# define WIN_WIDTH 600
# define WIN_HIGHT 600

# ifdef linux
#  define ESC_KEY 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define Q_KEY 81
#  define E_KEY 69
#  define UP_KEY 65362
#  define DOWN_KEY 65364
// #  define LEFT_KEY 65361
// #  define RIGHT_KEY 65363
// #  define M_KEY 109
// #  define H_KEY 104
// #  define I_KEY 34
# endif

# ifdef __MACH__
#  define ESC_KEY 53
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define UP_KEY 126
#  define DOWN_KEY 125
// #  define Q_KEY 81
// #  define E_KEY 69
// #  define LEFT_KEY 123
// #  define RIGHT_KEY 124
// #  define M_KEY 46
// #  define H_KEY 4
// #  define C_KEY 8
// #  define I_KEY 34
# endif

/*------------------Parsing-------------------*/
int			init_scene(
				char **argv, t_scene *scene, t_win *win);
void		clean_scene(t_scene scene);
int			fill_scene(char **argv, t_scene *scene);
t_list		*parsing_map(int fd);
void		init_parsing_kit(
				t_parsing_kit *s, t_list **head, char *line);
void		update_parsing_kit(
				t_parsing_kit *s, char *line);
char		line_classifier(t_parsing_kit *s, char *line);
int			check_new_line(char *line, int i);
int			filling_loop(t_parsing_kit *s, char *line, t_list **head);
t_list		*fill_line_node(char *arg, char type);
int			fill_new_line(
				t_parsing_kit *s, char *line, t_list **head, int i);
void		spaces_smash(t_parsing_kit *s, char *line, t_list **head);
void		filling_normal_spaced_word(
				t_parsing_kit *s, char *smashed_line, t_list **head);
int			check_all_elements_for_errors(
				t_list **all_map_items, t_scene *scene);
int			check_camera_data(t_list **all_map_items, t_scene *scene);
int			check_light_data(t_list **all_map_items, t_scene *scene);
int			check_ambient_light_data(t_list **all_map_items, t_scene *scene);
int			count_occurance_in_map(t_list **all_map_items, char *element);
t_list		*fetch_next_element(t_list *tmp);
int			is_cordinate(char *coordinate);
int			check_coordinates_error(t_list *tmp);
int			ft_is_float_and_update_i(char *check_me, int *i);
t_list		*get_next_occurance(t_list *tmp, char *element);
int			check_int_range(t_list *tmp, int start, int end);
int			check_float_range(t_list *tmp, float start, float end);
int			check_there_is_next_elements(t_list **head, int layers);
int			scan_camera_errors(t_list *tmp, int occurance);
int			scan_light_errors(t_list *tmp, int occurance);
int			ft_is_float(char *check_me);
int			scan_ambient_light_errors(t_list *tmp, int occurance);
int			check_coordinate_range(t_list *tmp);
int			check_sphere(t_list **all_map_items, t_scene *scene);
int			check_cylender(t_list **all_map_items, t_scene *scene);
int			check_plane(t_list **all_map_items, t_scene *scene);
int			scan_sphere_errors(t_list *tmp);
int			scan_plane_errors(t_list *tmp);
int			scan_cylender_errors(t_list *tmp);
int			inspect_first_element(char *coord);
int			inspect_second_element(char *coord);
int			inspect_thrid_element(char *coord);
/*-----------------FILLERS-------------------*/
int			fill_all_elements_in_scene(
				t_list **all_map_items, t_scene *scene);
int			fill_ambient_light(t_list **all_map_items, t_scene *scene);
int			fill_light(t_list **all_map_items, t_scene *scene);
int			fill_camera(t_list **all_map_items, t_scene *scene);
int			fill_coord(char *coord, float *x, float *y, float *z);
int			fill_spheres(t_list **all_map_items, t_scene *scene);
int			fill_single_sphere(t_scene *scene, t_list *tmp, int i);
int			fill_planes(t_list **all_map_items, t_scene *scene);
int			fill_single_plane(t_scene *scene, t_list *tmp, int i);
int			fill_first_element(char *coord, float *x);
int			fill_second_element(char *coord, float *y);
int			fill_thrid_element(char *coord, float *z);
int			vector_init(t_vec *vec, t_list *tmp);
int			fill_cylinders(t_list **all_map_items, t_scene *scene);
int			fill_single_cylinder(t_scene *scene, t_list *tmp, int i);
void		fill_4vec(t_vec4 *vec, float t, t_vec child);
/*------------------FT_MATH--------------------*/
void		fill_single_vector(t_vec *vec, float x, float y, float z);
float		vec_dot(t_vec *vec1, t_vec *vec2);
t_vec		vec_cross(t_vec *vec1, t_vec *vec2);
void		test_vec_dot(void);
t_vec		vec_add(t_vec *vec1, t_vec *vec2);
t_vec		vec_sub(t_vec *vec1, t_vec *vec2);
t_vec		vec_scalar_mult(t_vec *vec1, float scalar);
t_vec		qudratic_equation(float a, float b, float c);
float		normalize_vec_to_float(t_vec *vec);
t_vec		normalize_vec_to_vec(t_vec *vec);
void		normalize(t_vec *v);
float		vector_magnitude(t_vec *vec);
t_vec		vec_scalar_add(t_vec *vec1, float scalar);
t_vec		vec_scalar_sub(t_vec *vec1, float scalar);
t_vec		vec_multiply_two_vectors(t_vec *vec1, t_vec *vec2);
float		sign(float x);
t_pln_equ	fill_plane_equation(t_plane plane);
void		normalize(t_vec *v);
t_vec	find_rotation_matrix(t_vec *orientation, t_vec *dir);
void	rotate_around_x(t_vec *result, t_vec *dir, float theta_x);
void	rotate_around_y(t_vec *result, t_vec *dir, float theta_y);
void	rotate_around_z(t_vec *result, t_vec *dir, float theta_z);
/*------------------RENDERING_PREPARATION--------------*/
int			color_vec_to_int(t_vec *color);
float		color_by_intesity_to_float(t_vec *color, float intensity);
t_vec		fit_coordinate_to_screen(float x, float y, t_scene *scene);
t_vec		get_cylinder_height(t_cylinder *cylinder);
t_vec		plane_color(t_vec *dir, t_plane *pln, t_scene *scene);
/*------------------RENDERING-----------------*/
t_vec		trace_plane(t_vec *dir, t_scene *scene);
float		hit_plane(t_plane *plane, t_scene *scene, t_vec *dir);
float	his_hit_cylinder(t_cylinder *cylinder, t_vec *origin, t_vec *dir, float t_min);
void		init_ray_trace_kit(t_ray_trace_kit *r, t_img *img);
t_vec4		hit_cylinder(t_cylinder *cylinder,
				t_vec *origin, t_vec *dir, float t_min);
float		check_capped_part(float t0, float t1,
				t_vec *origin, t_vec *dir, t_cylinder *cylinder);
t_vec		add_sphere_spot_light(t_scene *scene,
				t_vec *normal, t_vec *light_vec, t_vec *i);
t_vec		trace_cylinder(t_vec *dir, float t_min, t_scene *scene);
t_vec		compute_color_to_vec(t_vec *dir,
				t_sphere *sphr, t_scene *scene, float close_t);
float		compute_color(t_vec *dir,
				t_sphere *sphr, t_scene *scene, float close_t);
int			vec_to_color(t_vec vec);
t_vec		hit_actual_plane(t_plane *pln, t_scene *scene, t_vec *dir);
int			hit_other_object(t_vec hit_point, t_vec light_vec, t_scene *scene);
t_vec		add_plane_spot_light(
				t_scene	*scene, t_vec *normal, t_vec *light_vec, t_vec *i);
t_plane		*find_closest_plane(t_scene *scene, t_vec *dir, float *closest_t);
t_sphere	*find_closest_sphere(
				t_scene *scene, t_vec *dir, float *closest_t, float *t_min);
t_vec		dir_with_camera_orientation(t_vec *dir, t_scene *scene);
t_vec		compute_cylinder_color(t_scene *scene, t_vec *dir,t_cylinder *closest_cylinder, float close_t);
/*------------------MLX_RELATED---------------*/
void		pixel_put(t_img *data, int x, int y, int color);
void		redraw(t_win *s, t_img *img, void (*draw)(t_img *));
void		setup_img(t_img *img, t_win *win, int width, int hight);
int			window_setup(t_win *win, t_img *img, char *map_title);
int			exit_code(t_win *win);
int			key_hook(int key, t_win *win);

/*----------------ERRORS-----------------------*/
int			not_valid_file(int argc, char **argv);
int			bad_file(char **argv);
int			parse_error_message(void);
int			file_reading_error_message(void);
int			initial_error_scan(t_list **all_map_items);
int			not_valid_element(t_list *check_me);
int			check_normalized_coord(t_vec	vec);
/*------------------DUMMY---------------------*/
void		put_ellipse(t_img *img, int width, int hight);
void		put_serpenski(t_img *img, int width, int hight);
void		put_ellipse2(t_img *img, int x, int y);
void		put_border(t_img *img);
/*------------------trials---------------------*/
void		basic_raytracing(t_img *img);
void		unknown_raytracing(t_img *img);
void		vec_init(t_vec *vec, float x, float y, float z);
float		vec_dot(t_vec *vec1, t_vec *vec2);
float		hit_sphere(t_sphere *sphere,
				t_vec *origin, t_vec *dir, float t_min);
t_vec		trace_sphere(
				t_vec *dir, float t_min, t_scene *scene);
/*--------------------TESTERS-----------------------------*/
void		vis_list(t_list **head);
void		vis_scene(t_scene *scene);
void		vis_elements(t_scene *scene);
void		vis_spheres(t_scene *scene);
void		vis_single_sphere(t_sphere sphere);
void		vis_planes(t_scene *scene);
void		vis_single_plane(t_plane plane);
void		vis_cylinders(t_scene *scene);
void		vis_single_cylinder(t_cylinder cylinder);
void		vis_vector(t_vec vec);
void		test_vec_cross(void);
void		test_vec_dot(void);
void		test_vec_add(void);
void		test_vec_sub(void);
void		test_vec_scalar_mult(void);
void		test_quadratic(void);
void		test_normalized_float(void);
void		test_normalized_vec(void);
#endif