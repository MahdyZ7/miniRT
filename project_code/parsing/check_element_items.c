/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element_items.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 23:54:06 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/23 02:14:22 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_coordinate_range(t_list *tmp)
{
	int		i;
	int		items;
	char	*coord;
	char	*check_me;
	float	num;

	items = 0;
	coord = NULL;
	check_me = NULL;
	num = 0.0;
	i = 0;
	if (check_coordinates_error(tmp))
		return (1);
	coord = (char *)tmp->content;
	while (coord[i])
	{
		if (items < 2)
			check_me = ft_substr(coord, 0, ft_strnchr(coord, ','));
		else
			check_me = ft_substr(coord, 0, ft_strlen(coord));
		printf("inside cordinate range %s\n", check_me);
		num = ft_atof(check_me);
		if (num > 255 || num < 0)
		{
			free(check_me);
			printf("Out of range\n");
			return (1);
		}
		else
			printf("%f in correct range\n", num);
		free(check_me);
		if (items < 1)
			coord = &coord[ft_strnchr(coord, ',') + 1];
		items++;
		i++;
	}
	return (0);
}

int	check_coordinates_error(t_list *tmp)
{
	if (!tmp)
		return (1);
	if (!is_cordinate((char *)tmp->content))
	{
		ft_printf("not coordinate :(\n");
		return (1);
	}
	else
		return (0);
	return (1);
}

int	is_cordinate(char *coordinate)
{
	int	i;
	int	items;

	items = 0;
	i = 0;
	if (!coordinate)
		return (0);
	while (coordinate[i] && items < 3)
	{
		if (ft_is_float_and_update_i(coordinate, &i))
		{
			if ((items < 2 && coordinate[i] != ',')
				|| (items == 2 && coordinate[i] != '\0'))
				return (0);
		}
		else
			return (0);
		items++;
		i++;
	}
	return (1);
}

int	ft_is_float_and_update_i(char *check_me, int *i)
{
	ft_printf("checking %s\n",& check_me[*i]);
	if (check_me[*i] == '+' || check_me[*i] == '-')
		*i = *i + 1;
	if (!ft_isdigit(check_me[*i]))
		return (0);
	while (ft_isdigit(check_me[*i]))
	{
		*i = *i + 1;
	}
	if (check_me[*i] == '.')
	{
		*i = *i + 1;
		while (ft_isdigit(check_me[*i]))
			*i = *i +1;
	}
	return (1);
}

t_list	*get_next_occurance(t_list *tmp, char *element)
{
	while (tmp)
	{
		if (!ft_the_strcmp((char *)tmp->content, element))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

//isaad;
//ircserv;