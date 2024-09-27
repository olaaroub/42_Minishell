/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:10:08 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/26 18:07:31 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
We will need a function that will free
a single node and relink the linked list that works as a garbage collector
*/



t_env	*ft_create_node(char *env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	g_data.trash_list = ft_add_trash(&g_data.trash_list, new);
	if (!new)
		return (NULL);
	new->line = ft_strdup(env);
	g_data.trash_list = ft_add_trash(&g_data.trash_list, new->line);
	new->name = ft_costume_strchr(env, '=');
	g_data.trash_list = ft_add_trash(&g_data.trash_list, new->name);
	new->value = ft_strdup(ft_strchr(env, '='));
	g_data.trash_list = ft_add_trash(&g_data.trash_list, new->value);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*ft_add_env(t_env **head, char *env)
{
	t_env	*new;
	t_env	*temp;

	new = ft_create_node(env);
	if (!new)
		return (NULL);
	if (!*head)
		return (new);
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
	new->next = NULL;
	return (*head);
}

void	get_env(t_env **env_list, char **env)
{
	int i;
	
	*env_list = NULL;
	i = -1;
	while (env && env[++i])
		*env_list = ft_add_env(env_list, env[i]);
}
