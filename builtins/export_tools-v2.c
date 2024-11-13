/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools-v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:28:10 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/12 22:30:52 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sort_env(t_env **env)
{
	int		x;
	int		y;
	t_env	*min;
	t_env	*tmp;

	x = 1;
	y = list_size(*env, 1) + 1;
	tmp = *env;
	while (tmp)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
	while (x < y)
	{
		min = get_min(*env);
		if (min)
			min->index = x++;
	}
}

t_env *env_newnode(char *line)
{
	t_env	*new_node;
	char	*temp;
	int		len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (ft_printf(2,"ERROR: ENV Node malloc failed!\n"), NULL);
	len = ft_strlen(line);
	new_node->name = ft_substr(line, 0, ft_strlen_eq(line, '='));
	new_node->value = ft_substr(line, ft_strlen_eq(line, '=') + 1, len);
	temp = ft_strjoin(new_node->name, "=");
	new_node->line = ft_strjoin(temp, new_node->value);
	free(temp);
	new_node->index = 0;
	new_node->next = NULL;
	return (new_node);
}

void	env_add_back(t_env **head, t_env *new_node)
{
	t_env	*temp;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

t_env	*env_new_node(char *line, int flag)
{
	t_env	*new_node;
	char	*temp;
	int		len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (ft_printf(2, "ERROR: ENV Node malloc failed!\n"), NULL);
	if (flag == 0)
	{
		new_node->line = ft_strdup(line);
		new_node->name = ft_strdup(line);
		new_node->value = NULL;
	}
	else
	{
		len = ft_strlen(line);
		new_node->name = ft_substr(line, 0, ft_strlen_eq(line, '+'));
		new_node->value = ft_substr(line, ft_strlen_eq(line, '=') + 1, len);
		temp = ft_strjoin(new_node->name, "=");
		new_node->line = ft_strjoin(temp, new_node->value);
		free(temp);
	}
	new_node->index = 0;
	new_node->next = NULL;
	return (new_node);
}

t_env	*get_to_print(t_env *env, int index)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (temp->index == index)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}