/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_smasher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 08:07:36 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/18 12:56:08 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
/*
	if there is parser error
	will fill the first flag with parser error code, 
	check if there is an error if the flag value less than 30
*/

t_list	*parsing_map(int fd)
{
	t_parsing_kit	s;
	char			*line;
	t_list			*head;

	head = NULL;
	line = get_next_line(fd);
	init_parsing_kit(&s, &head, line);
	// s.line_len = (int)ft_strlen(cmd);
	// while (s.i < s.line_len)
	// {
	// 	if (cmd_classifier(&s, cmd) == 'r')
	// 	{
	// 		fill_redirection(&s, cmd, head, s.i);
	// 	}
	// 	else if (cmd_classifier(&s, cmd) == '\'')
	// 		single_qoute_smach(&s, cmd, s.tmp, head);
	// 	else if (cmd_classifier(&s, cmd) == '"')
	// 		double_qoute_smash(&s, cmd, head, exit_status);
	// 	else
	// 		spaces_smash(&s, cmd, head, exit_status);
	// 	if (s.parse_error_code != 0)
	// 		break ;
	// 	s.i++;
	// }
	// stick_error_code_if_it__exists(cmd, *head, &s);
	return (head);
}

// // char	cmd_classifier(t_smash_kit *s, char *cmd)
// // {
// // 	int	i;

// // 	i = s->i;
// // 	if (s->flag != 'i')
// // 		return (s->flag);
// // 	while (cmd[i])
// // 	{
// // 		if (cmd[i] == ' ')
// // 		{
// // 			i++;
// // 			continue ;
// // 		}
// // 		else if (check_new_line(cmd, i))
// // 			s->flag = 'r';
// // 		else if (cmd[i] == '"')
// // 			s->flag = '"';
// // 		else if (cmd[i] == '\'')
// // 			s->flag = '\'';
// // 		else
// // 			s->flag = 's';
// // 		s->start = i;
// // 		return (s->flag);
// // 	}
// // 	return (s->flag);
// // }

// /*
// 	s->flag = i for initial stage
// 			= c for command
// 			= p for pipes
// 			= g give
// 			= t take
// */
void	init_parsing_kit(t_parsing_kit *s, t_list **head, char *line)
{
	s->start = 0;
	s->end = 0;
	s->last_end = 0;
	s->i = 0;
	s->tmp = *head;
	s->flag = 'i';
	s->parse_error_code = 0;
	s->line_len = 0;
	s->line = line;
}

// // t_list	*fill_cmd_node(char *arg, char type)
// // {
// // 	t_list	*new_node;

// // 	new_node = ft_lstnew(NULL);
// // 	new_node->content = (void *)arg;
// // 	new_node->flag = type;
// // 	return (new_node);
// // }
