/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 01:58:04 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/18 12:19:38 by ahsalem          ###   ########.fr       */
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
	if (fill_scene(argv, scene))
		return (1);
	return (0);
}

int	fill_scene(char **argv, t_scene *scene)
{
	int		fd;
	char	*line;
	t_list	*all_map_items;
	int		i;

	(void)scene;
	(void)all_map_items;
	i = 0;
	line = NULL;
	(void)line;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (parse_error_message());
	all_map_items = parsing_map(fd);
	i++;
	return (0);
}