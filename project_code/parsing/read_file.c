/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:58:04 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/23 16:04:57 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

//parse everything and fill the scene here inshalla
int	init_scene(
		char **argv, t_scene *scene, t_win *win)
{
	scene->win = win;
	scene->spheres = NULL;
	scene->plane = NULL;
	scene->cylinder = NULL;
	scene->error_code = 0;
	scene->number_of_shapes = 0;
	if (fill_scene(argv, scene))
		return (1);
	return (0);
}

int	fill_scene(char **argv, t_scene *scene)
{
	int		fd;
	t_list	*all_map_items;
	int		i;

	(void)scene;
	i = 0;
	fd = open(argv[1], O_RDONLY);
	all_map_items = parsing_map(fd);
	if (fd < 0 || !all_map_items)
		return (file_reading_error_message());
	if (classify_elements(&all_map_items, scene))
		return (file_reading_error_message());
	ft_lstclear(&all_map_items, del);
	i++;
	return (1);
	return (0);
}
