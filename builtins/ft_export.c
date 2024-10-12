/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:02:51 by olaaroub          #+#    #+#             */
/*   Updated: 2024/10/09 21:38:22 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isset(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_strlen_eq(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != c)
		i++;
	return (i);
}
char	*get_var_name(char *line, int sign)
{
	char	*name;

	name = NULL;
	if (sign == 3)
		name = ft_strdup(line);
	else if (sign == 2)
		name = ft_substr(line, 0, ft_strlen_eq(line, '+'));
	else if (sign == 1)
		name = ft_substr(line, 0, ft_strlen_eq(line, '='));
	return (name);
}
void	env_modify(t_env *env, char *name, char *value)
{
	t_env	*temp;

	temp = env;

	while(temp)
	{
		if (!ft_strcmp(name, temp->name))
		{
			free(temp->value);
			temp->value = value;
			free(temp->line);
			temp->line = ft_strjoin(name, "=");
			temp->line = ft_strjoin(temp->line, value);
			return ;
		}
		temp = temp->next;
	}
}

void	export_modify(t_env *env, char *line, char *name, int sign)
{
	char	*value;
	char	*tmp;

	if (sign == 3)
		return ;
	else
	{
		value = ft_substr(line, ft_strlen_eq(line, '=') + 1, ft_strlen(line));
		if (sign == 2)
		{
			tmp = ft_strjoin(env->value, value);
			env_modify(g_data.env_list, name, tmp);
			free(value);
			free(tmp);
			return ;
		}
		else if (sign == 1)
			env_modify(g_data.env_list, name, value);
		free(value);
	}
	return ;
}

t_env	*env_new_node(char *line, int flag)
{
	t_env	*new_node;
	char	*temp;
	int		len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (printf("ERROR: ENV Node malloc failed!\n"), NULL);
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
t_env *env_newnode(char *line)
{
	t_env	*new_node;
	char	*temp;
	int		len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (printf("ERROR: ENV Node malloc failed!\n"), NULL);
	len = ft_strlen(line);
	new_node->name = ft_substr(line, 0, ft_strlen_eq(line, '='));
	new_node->value = ft_substr(line, ft_strlen_eq(line, '=') + 1, len);
	temp = ft_strjoin(new_node->name, "=");
	new_node->line = ft_strjoin(temp, new_node->value);
	free(temp);
	new_node->next = NULL;
	return (new_node);
}

int	export_to_env(char *line, int sign)
{
	t_env	*temp;
	char	*name;

	temp = g_data.env_list;
	name = get_var_name(line, sign);
	while (temp)
	{
		if (!ft_strcmp(name, temp->name))
		{
			export_modify(temp, line, name, sign);
			free(name);
			return (0);
		}
		temp = temp->next;
	}
	free(name);
	if (sign == 3)
		env_add_back(&g_data.env_list, env_new_node(line, 0));
	else if (sign == 2)
		env_add_back(&g_data.env_list, env_new_node(line, 1));
	else if (sign == 1)
		env_add_back(&g_data.env_list, env_newnode(line));
	return (0);
}

int	check_export(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || (str[i] >= '0' && str[i] <= '9')
		|| str[i] == '=' || str[i] == '+')
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isset(str[i]))
			return (0);
		i++;
	}
	if (str[i] == '\0')
		return (3);
	if (str[i] == '+')
	{
		if (!str[i + 1] || (str[i + 1] && str[i + 1] != '='))
			return (0);
		else
			return (2);
	}
	return (1);
}


int ft_export(char **cmd)
{
	int	status;
    int y;

	status = 0;
    y = 0;
    while(cmd[++y])
    {
        if (!check_export(cmd[y]))
		{
			printf("export: `%s': not a valid identifier\n", cmd[y]);
			status = 1;
		}
        else
        {
			if (status == 1)
				export_to_env(cmd[y], check_export(cmd[y]));
			else
				status = export_to_env(cmd[y], check_export(cmd[y]));
		}
    }
	return (status);
}