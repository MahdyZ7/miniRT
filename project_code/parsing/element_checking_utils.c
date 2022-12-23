/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_checking_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:12:46 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/22 19:32:47 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_there_is_next_elements(t_list **head, int layers)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = *head;
	if (!tmp)
		return (0);
	while (i < layers)
	{
		tmp = tmp->next;
		if (!tmp)
			return (0);
		i++;
	}
	return (1);
}

int	check_int_range(t_list *tmp, int start, int end)
{
	char	*check_me;
	int		i;
	int		given_value;

	given_value = 0;
	i = 0;
	check_me = NULL;
	if (!tmp)
		return (1);
	check_me = (char *)tmp->content;
	if (!check_me)
		return (1);
	if (!check_me[i])
		return (1);
	while (check_me[i])
	{
		if (!ft_isdigit(check_me[i]))
			return (1);
		i++;
	}
	given_value = ft_atoi(check_me);
	if (!(given_value >= start && given_value <= end))
		return (1);
	ft_printf("%s is in correct range\n", check_me);
	return (0);
}

int	check_float_range(t_list *tmp, float start, float end)
{
	char	*check_me;
	int		i;
	float	given_value;

	given_value = 0.0;
	i = 0;
	check_me = NULL;
	if (!tmp)
		return (1);
	check_me = (char *)tmp->content;
	if (!check_me)
		return (1);
	if (!check_me[i])
		return (1);
	given_value = ft_atof(check_me);
	if (!ft_is_float(check_me)
		|| !(given_value >= start && given_value <= end))
	{
		printf("not float %s, %f\n", check_me, ft_atof(check_me));
		return (1);
	}
	return (0);
}

int	ft_is_float(char *check_me)
{
	int	i;

	i = 0;
	while (check_me[i])
	{
		if (!ft_isdigit(check_me[i]))
		{
			if (check_me[i] == '.')
				break ;
			return (0);
		}
		i++;
	}
	if (check_me[i] == '.')
	{
		i++;
		while (check_me[i])
		{
			if (!ft_isdigit(check_me[i]))
				return (0);
			i++;
		}
	}
	return (1);
}
