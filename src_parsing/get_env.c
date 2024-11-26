/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:10:08 by olaaroub          #+#    #+#             */
/*   Updated: 2024/11/26 15:27:36 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
We will need a function that will free
a single node and relink the linked list that works as a garbage collector
*/

t_env	*env_node(char *env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->line = ft_strdup(env);
	if(!new->line)
		return (NULL);
	new->name = ft_costume_strchr(env, '=');
	if(!new->name)
		return (free(new->line), NULL);
	new->value = ft_strdup(ft_strchr(env, '='));
	if(!new->value)
		return (free(new->line), free(new->name), NULL);
	new->index = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env	*ft_add_env(t_env **head, char *env)
{
	t_env	*new;
	t_env	*temp;

	new = env_node(env);
	if (!new)
		return (free_env_list(), NULL);
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
	int	i;

	*env_list = NULL;
	i = -1;
	while (env && env[++i])
		*env_list = ft_add_env(env_list, env[i]);
}
