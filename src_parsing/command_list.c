/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatalhao <hatalhao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:11:31 by olaaroub          #+#    #+#             */
/*   Updated: 2024/09/27 13:48:59 by hatalhao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_command	*command_node(char **commands, t_redir *redir)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	g_data.trash_list = ft_add_trash(&g_data.trash_list, new);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->cmd = commands;
	new->red = redir;
	return (new);
}

t_command	*ft_add_command(t_command **head, char **commands, t_redir *redir)
{
	t_command	*new;
	t_command	*temp;

	new = command_node(commands, redir);
	if (!new)
		return (NULL);
	if (!*head)
		return (new);
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
	return (*head);
}

t_redir	*redir_node(char *file_name, int type)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	g_data.trash_list = ft_add_trash(&g_data.trash_list, new);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->file_name = file_name;
	new->type = type;
	return (new);
}

t_redir	*ft_add_redir(t_redir **head, char *file_name, int type)
{
	t_redir	*new;
	t_redir	*temp;

	new = redir_node(file_name, type);
	if (!new)
		return (NULL);
	if (!*head)
		return (new);
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
	return (*head);
}
